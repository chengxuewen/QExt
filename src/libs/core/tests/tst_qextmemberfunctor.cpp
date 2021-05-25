#include <qextmemberfunctor.h>

#include <QtTest>
#include <QDebug>

class MemberBase
{
public:
    MemberBase() {}

    virtual void voidFunction0() {
        qDebug() << "MemberBase::voidFunction0";
    }
    virtual void voidFunction1(int a1) {
        qDebug() << "MemberBase::voidFunction1:" << a1;
    }
    virtual void voidFunction2(int a1, int a2) {
        qDebug() << "MemberBase::voidFunction2:" << a1 << "," << a2;
    }
    virtual void voidFunction3(int a1, int a2, int a3) {
        qDebug() << "MemberBase::voidFunction3:" << a1 << "," << a2 << "," << a3;
    }
    virtual void voidFunction4(int a1, int a2, int a3, int a4) {
        qDebug() << "MemberBase::voidFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    virtual void voidFunction5(int a1, int a2, int a3, int a4, int a5) {
        qDebug() << "MemberBase::voidFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    virtual void voidFunction6(int a1, int a2, int a3, int a4, int a5, int a6) {
        qDebug() << "MemberBase::voidFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    virtual void voidFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
        qDebug() << "MemberBase::voidFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }
    virtual void voidFunctionB1(bool a1) {
        qDebug() << "MemberBase::voidFunctionB1:" << a1;
    }
    virtual void voidFunctionB2(bool a1, int a2) {
        qDebug() << "MemberBase::voidFunctionB2:" << a1 << "," << a2;
    }
    virtual void voidFunctionB3(bool a1, int a2, int a3) {
        qDebug() << "MemberBase::voidFunctionB3:" << a1 << "," << a2 << "," << a3;
    }
    virtual void voidFunctionB4(bool a1, int a2, int a3, int a4) {
        qDebug() << "MemberBase::voidFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    virtual void voidFunctionB5(bool a1, int a2, int a3, int a4, int a5) {
        qDebug() << "MemberBase::voidFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    virtual void voidFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) {
        qDebug() << "MemberBase::voidFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    virtual void voidFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) {
        qDebug() << "MemberBase::voidFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }

    virtual int intFunction0() {
        return 0;
    }
    virtual int intFunction1(int a1) {
        return a1;
    }
    virtual int intFunction2(int a1, int a2) {
        return a1 + a2;
    }
    virtual int intFunction3(int a1, int a2, int a3) {
        return a1 + a2 + a3;
    }
    virtual int intFunction4(int a1, int a2, int a3, int a4) {
        return a1 + a2 + a3 + a4;
    }
    virtual int intFunction5(int a1, int a2, int a3, int a4, int a5) {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual int intFunction6(int a1, int a2, int a3, int a4, int a5, int a6) {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual int intFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual int intFunctionB1(bool a1) {
        return a1;
    }
    virtual int intFunctionB2(bool a1, int a2) {
        return a1 ? a2 : 0;
    }
    virtual int intFunctionB3(bool a1, int a2, int a3) {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual int intFunctionB4(bool a1, int a2, int a3, int a4) {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual int intFunctionB5(bool a1, int a2, int a3, int a4, int a5) {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual int intFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual int intFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }

    virtual double doubleFunction0() {
        return 0;
    }
    virtual double doubleFunction1(double a1) {
        return a1;
    }
    virtual double doubleFunction2(double a1, double a2) {
        return a1 + a2;
    }
    virtual double doubleFunction3(double a1, double a2, double a3) {
        return a1 + a2 + a3;
    }
    virtual double doubleFunction4(double a1, double a2, double a3, double a4) {
        return a1 + a2 + a3 + a4;
    }
    virtual double doubleFunction5(double a1, double a2, double a3, double a4, double a5) {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual double doubleFunction6(double a1, double a2, double a3, double a4, double a5, double a6) {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual double doubleFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual double doubleFunctionB1(bool a1) {
        return a1;
    }
    virtual double doubleFunctionB2(bool a1, double a2) {
        return a1 ? a2 : 0;
    }
    virtual double doubleFunctionB3(bool a1, double a2, double a3) {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual double doubleFunctionB4(bool a1, double a2, double a3, double a4) {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual double doubleFunctionB5(bool a1, double a2, double a3, double a4, double a5) {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual double doubleFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual double doubleFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }


    // const function
    virtual void voidConstFunction0() const {
        qDebug() << "MemberBase::voidConstFunction0";
    }
    virtual void voidConstFunction1(int a1) const {
        qDebug() << "MemberBase::voidConstFunction1:" << a1;
    }
    virtual void voidConstFunction2(int a1, int a2) const {
        qDebug() << "MemberBase::voidConstFunction2:" << a1 << "," << a2;
    }
    virtual void voidConstFunction3(int a1, int a2, int a3) const {
        qDebug() << "MemberBase::voidConstFunction3:" << a1 << "," << a2 << "," << a3;
    }
    virtual void voidConstFunction4(int a1, int a2, int a3, int a4) const {
        qDebug() << "MemberBase::voidConstFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    virtual void voidConstFunction5(int a1, int a2, int a3, int a4, int a5) const {
        qDebug() << "MemberBase::voidConstFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    virtual void voidConstFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const {
        qDebug() << "MemberBase::voidConstFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    virtual void voidConstFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const {
        qDebug() << "MemberBase::voidConstFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }
    virtual void voidConstFunctionB1(bool a1) const {
        qDebug() << "MemberBase::voidConstFunctionB1:" << a1;
    }
    virtual void voidConstFunctionB2(bool a1, int a2) const {
        qDebug() << "MemberBase::voidConstFunctionB2:" << a1 << "," << a2;
    }
    virtual void voidConstFunctionB3(bool a1, int a2, int a3) const {
        qDebug() << "MemberBase::voidConstFunctionB3:" << a1 << "," << a2 << "," << a3;
    }
    virtual void voidConstFunctionB4(bool a1, int a2, int a3, int a4) const {
        qDebug() << "MemberBase::voidConstFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    virtual void voidConstFunctionB5(bool a1, int a2, int a3, int a4, int a5) const {
        qDebug() << "MemberBase::voidConstFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    virtual void voidConstFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const {
        qDebug() << "MemberBase::voidConstFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    virtual void voidConstFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const {
        qDebug() << "MemberBase::voidConstFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }

    virtual int intConstFunction0() const {
        return 0;
    }
    virtual int intConstFunction1(int a1) const {
        return a1;
    }
    virtual int intConstFunction2(int a1, int a2) const {
        return a1 + a2;
    }
    virtual int intConstFunction3(int a1, int a2, int a3) const {
        return a1 + a2 + a3;
    }
    virtual int intConstFunction4(int a1, int a2, int a3, int a4) const {
        return a1 + a2 + a3 + a4;
    }
    virtual int intConstFunction5(int a1, int a2, int a3, int a4, int a5) const {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual int intConstFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual int intConstFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual int intConstFunctionB1(bool a1) const {
        return a1;
    }
    virtual int intConstFunctionB2(bool a1, int a2) const {
        return a1 ? a2 : 0;
    }
    virtual int intConstFunctionB3(bool a1, int a2, int a3) const {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual int intConstFunctionB4(bool a1, int a2, int a3, int a4) const {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual int intConstFunctionB5(bool a1, int a2, int a3, int a4, int a5) const {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual int intConstFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual int intConstFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }

    virtual double doubleConstFunction0() const {
        return 0;
    }
    virtual double doubleConstFunction1(double a1) const {
        return a1;
    }
    virtual double doubleConstFunction2(double a1, double a2) const {
        return a1 + a2;
    }
    virtual double doubleConstFunction3(double a1, double a2, double a3) const {
        return a1 + a2 + a3;
    }
    virtual double doubleConstFunction4(double a1, double a2, double a3, double a4) const {
        return a1 + a2 + a3 + a4;
    }
    virtual double doubleConstFunction5(double a1, double a2, double a3, double a4, double a5) const {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual double doubleConstFunction6(double a1, double a2, double a3, double a4, double a5, double a6) const {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual double doubleConstFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual double doubleConstFunctionB1(bool a1) const {
        return a1 ? 1 : 0;
    }
    virtual double doubleConstFunctionB2(bool a1, double a2) const {
        return a1 ? a2 : 0;
    }
    virtual double doubleConstFunctionB3(bool a1, double a2, double a3) const {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual double doubleConstFunctionB4(bool a1, double a2, double a3, double a4) const {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual double doubleConstFunctionB5(bool a1, double a2, double a3, double a4, double a5) const {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual double doubleConstFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) const {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual double doubleConstFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }



    // volatile function
    virtual void voidVolatileFunction0() volatile {
        qDebug() << "MemberBase::voidVolatileFunction0";
    }
    virtual void voidVolatileFunction1(int a1) volatile {
        qDebug() << "MemberBase::voidVolatileFunction1:" << a1;
    }
    virtual void voidVolatileFunction2(int a1, int a2) volatile {
        qDebug() << "MemberBase::voidVolatileFunction2:" << a1 << "," << a2;
    }
    virtual void voidVolatileFunction3(int a1, int a2, int a3) volatile {
        qDebug() << "MemberBase::voidVolatileFunction3:" << a1 << "," << a2 << "," << a3;
    }
    virtual void voidVolatileFunction4(int a1, int a2, int a3, int a4) volatile {
        qDebug() << "MemberBase::voidVolatileFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    virtual void voidVolatileFunction5(int a1, int a2, int a3, int a4, int a5) volatile {
        qDebug() << "MemberBase::voidVolatileFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    virtual void voidVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) volatile {
        qDebug() << "MemberBase::voidVolatileFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    virtual void voidVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile {
        qDebug() << "MemberBase::voidVolatileFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }
    virtual void voidVolatileFunctionB1(bool a1) volatile {
        qDebug() << "MemberBase::voidVolatileFunctionB1:" << a1;
    }
    virtual void voidVolatileFunctionB2(bool a1, int a2) volatile {
        qDebug() << "MemberBase::voidVolatileFunctionB2:" << a1 << "," << a2;
    }
    virtual void voidVolatileFunctionB3(bool a1, int a2, int a3) volatile {
        qDebug() << "MemberBase::voidVolatileFunctionB3:" << a1 << "," << a2 << "," << a3;
    }
    virtual void voidVolatileFunctionB4(bool a1, int a2, int a3, int a4) volatile {
        qDebug() << "MemberBase::voidVolatileFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    virtual void voidVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile {
        qDebug() << "MemberBase::voidVolatileFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    virtual void voidVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) volatile {
        qDebug() << "MemberBase::voidVolatileFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    virtual void voidVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile {
        qDebug() << "MemberBase::voidVolatileFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }

    virtual int intVolatileFunction0() volatile {
        return 0;
    }
    virtual int intVolatileFunction1(int a1) volatile {
        return a1;
    }
    virtual int intVolatileFunction2(int a1, int a2) volatile {
        return a1 + a2;
    }
    virtual int intVolatileFunction3(int a1, int a2, int a3) volatile {
        return a1 + a2 + a3;
    }
    virtual int intVolatileFunction4(int a1, int a2, int a3, int a4) volatile {
        return a1 + a2 + a3 + a4;
    }
    virtual int intVolatileFunction5(int a1, int a2, int a3, int a4, int a5) volatile {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual int intVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) volatile {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual int intVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual int intVolatileFunctionB1(bool a1) volatile {
        return a1;
    }
    virtual int intVolatileFunctionB2(bool a1, int a2) volatile {
        return a1 ? a2 : 0;
    }
    virtual int intVolatileFunctionB3(bool a1, int a2, int a3) volatile {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual int intVolatileFunctionB4(bool a1, int a2, int a3, int a4) volatile {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual int intVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual int intVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) volatile {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual int intVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }

    virtual double doubleVolatileFunction0() volatile {
        return 0;
    }
    virtual double doubleVolatileFunction1(double a1) volatile {
        return a1;
    }
    virtual double doubleVolatileFunction2(double a1, double a2) volatile {
        return a1 + a2;
    }
    virtual double doubleVolatileFunction3(double a1, double a2, double a3) volatile {
        return a1 + a2 + a3;
    }
    virtual double doubleVolatileFunction4(double a1, double a2, double a3, double a4) volatile {
        return a1 + a2 + a3 + a4;
    }
    virtual double doubleVolatileFunction5(double a1, double a2, double a3, double a4, double a5) volatile {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual double doubleVolatileFunction6(double a1, double a2, double a3, double a4, double a5, double a6) volatile {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual double doubleVolatileFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual double doubleVolatileFunctionB1(bool a1) volatile {
        return a1 ? 1 : 0;
    }
    virtual double doubleVolatileFunctionB2(bool a1, double a2) volatile {
        return a1 ? a2 : 0;
    }
    virtual double doubleVolatileFunctionB3(bool a1, double a2, double a3) volatile {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual double doubleVolatileFunctionB4(bool a1, double a2, double a3, double a4) volatile {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual double doubleVolatileFunctionB5(bool a1, double a2, double a3, double a4, double a5) volatile {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual double doubleVolatileFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) volatile {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual double doubleVolatileFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }


    // const volatile
    virtual void voidConstVolatileFunction0() const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunction0";
        QVERIFY(true);
    }
    virtual void voidConstVolatileFunction1(int a1) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunction1:" << a1;
    }
    virtual void voidConstVolatileFunction2(int a1, int a2) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunction2:" << a1 << "," << a2;
    }
    virtual void voidConstVolatileFunction3(int a1, int a2, int a3) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunction3:" << a1 << "," << a2 << "," << a3;
    }
    virtual void voidConstVolatileFunction4(int a1, int a2, int a3, int a4) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    virtual void voidConstVolatileFunction5(int a1, int a2, int a3, int a4, int a5) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    virtual void voidConstVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    virtual void voidConstVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }
    virtual void voidConstVolatileFunctionB1(bool a1) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunctionB1:" << a1;
    }
    virtual void voidConstVolatileFunctionB2(bool a1, int a2) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunctionB2:" << a1 << "," << a2;
    }
    virtual void voidConstVolatileFunctionB3(bool a1, int a2, int a3) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunctionB3:" << a1 << "," << a2 << "," << a3;
    }
    virtual void voidConstVolatileFunctionB4(bool a1, int a2, int a3, int a4) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    virtual void voidConstVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    virtual void voidConstVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    virtual void voidConstVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile {
        qDebug() << "MemberBase::voidConstVolatileFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }

    virtual int intConstVolatileFunction0() const volatile {
        return 0;
    }
    virtual int intConstVolatileFunction1(int a1) const volatile {
        return a1;
    }
    virtual int intConstVolatileFunction2(int a1, int a2) const volatile {
        return a1 + a2;
    }
    virtual int intConstVolatileFunction3(int a1, int a2, int a3) const volatile {
        return a1 + a2 + a3;
    }
    virtual int intConstVolatileFunction4(int a1, int a2, int a3, int a4) const volatile {
        return a1 + a2 + a3 + a4;
    }
    virtual int intConstVolatileFunction5(int a1, int a2, int a3, int a4, int a5) const volatile {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual int intConstVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const volatile {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual int intConstVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual int intConstVolatileFunctionB1(bool a1) const volatile {
        return a1;
    }
    virtual int intConstVolatileFunctionB2(bool a1, int a2) const volatile {
        return a1 ? a2 : 0;
    }
    virtual int intConstVolatileFunctionB3(bool a1, int a2, int a3) const volatile {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual int intConstVolatileFunctionB4(bool a1, int a2, int a3, int a4) const volatile {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual int intConstVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) const volatile {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual int intConstVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual int intConstVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }

    virtual double doubleConstVolatileFunction0() const volatile {
        return 0;
    }
    virtual double doubleConstVolatileFunction1(double a1) const volatile {
        return a1;
    }
    virtual double doubleConstVolatileFunction2(double a1, double a2) const volatile {
        return a1 + a2;
    }
    virtual double doubleConstVolatileFunction3(double a1, double a2, double a3) const volatile {
        return a1 + a2 + a3;
    }
    virtual double doubleConstVolatileFunction4(double a1, double a2, double a3, double a4) const volatile {
        return a1 + a2 + a3 + a4;
    }
    virtual double doubleConstVolatileFunction5(double a1, double a2, double a3, double a4, double a5) const volatile {
        return a1 + a2 + a3 + a4 + a5;
    }
    virtual double doubleConstVolatileFunction6(double a1, double a2, double a3, double a4, double a5, double a6) const volatile {
        return a1 + a2 + a3 + a4 + a5 + a6;
    }
    virtual double doubleConstVolatileFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile {
        return a1 + a2 + a3 + a4 + a5 + a6 + a7;
    }
    virtual double doubleConstVolatileFunctionB1(bool a1) const volatile {
        return a1 ? 1 : 0;
    }
    virtual double doubleConstVolatileFunctionB2(bool a1, double a2) const volatile {
        return a1 ? a2 : 0;
    }
    virtual double doubleConstVolatileFunctionB3(bool a1, double a2, double a3) const volatile {
        return a1 ? (a2 + a3) : (a2 * a3);
    }
    virtual double doubleConstVolatileFunctionB4(bool a1, double a2, double a3, double a4) const volatile {
        return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
    }
    virtual double doubleConstVolatileFunctionB5(bool a1, double a2, double a3, double a4, double a5) const volatile {
        return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
    }
    virtual double doubleConstVolatileFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) const volatile {
        return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
    }
    virtual double doubleConstVolatileFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile {
        return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
    }
};


class Member : public MemberBase
{
public:
    Member() {}


    void voidFunction0() {
        qDebug() << "Member::voidFunction0";
        QVERIFY(true);
    }
    void voidFunction1(int a1) {
        qDebug() << "Member::voidFunction1:" << a1;
    }
    void voidFunction2(int a1, int a2) {
        qDebug() << "Member::voidFunction2:" << a1 << "," << a2;
    }
    void voidFunction3(int a1, int a2, int a3) {
        qDebug() << "Member::voidFunction3:" << a1 << "," << a2 << "," << a3;
    }
    void voidFunction4(int a1, int a2, int a3, int a4) {
        qDebug() << "Member::voidFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    void voidFunction5(int a1, int a2, int a3, int a4, int a5) {
        qDebug() << "Member::voidFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    void voidFunction6(int a1, int a2, int a3, int a4, int a5, int a6) {
        qDebug() << "Member::voidFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    void voidFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
        qDebug() << "Member::voidFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }
    void voidFunctionB1(bool a1) {
        qDebug() << "Member::voidFunctionB1:" << a1;
    }
    void voidFunctionB2(bool a1, int a2) {
        qDebug() << "Member::voidFunctionB2:" << a1 << "," << a2;
    }
    void voidFunctionB3(bool a1, int a2, int a3) {
        qDebug() << "Member::voidFunctionB3:" << a1 << "," << a2 << "," << a3;
    }
    void voidFunctionB4(bool a1, int a2, int a3, int a4) {
        qDebug() << "Member::voidFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    void voidFunctionB5(bool a1, int a2, int a3, int a4, int a5) {
        qDebug() << "Member::voidFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    void voidFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) {
        qDebug() << "Member::voidFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    void voidFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) {
        qDebug() << "Member::voidFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }

    int intFunction0() {
        return 0;
    }
    int intFunction1(int a1) {
        Q_UNUSED(a1);
        return 0;
    }
    int intFunction2(int a1, int a2) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        return 0;
    }
    int intFunction3(int a1, int a2, int a3) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return 0;
    }
    int intFunction4(int a1, int a2, int a3, int a4) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return 0;
    }
    int intFunction5(int a1, int a2, int a3, int a4, int a5) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return 0;
    }
    int intFunction6(int a1, int a2, int a3, int a4, int a5, int a6) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return 0;
    }
    int intFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return 0;
    }
    int intFunctionB1(bool a1) {
        return a1 ? 1 : 0;
    }
    int intFunctionB2(bool a1, int a2) {
        Q_UNUSED(a2);
        return a1 ? 1 : 0;
    }
    int intFunctionB3(bool a1, int a2, int a3) {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return a1 ? 1 : 0;
    }
    int intFunctionB4(bool a1, int a2, int a3, int a4) {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return a1 ? 1 : 0;
    }
    int intFunctionB5(bool a1, int a2, int a3, int a4, int a5) {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return a1 ? 1 : 0;
    }
    int intFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return a1 ? 1 : 0;
    }
    int intFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return a1 ? 1 : 0;
    }

    double doubleFunction0() {
        return 0;
    }
    double doubleFunction1(double a1) {
        Q_UNUSED(a1);
        return 0;
    }
    double doubleFunction2(double a1, double a2) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        return 0;
    }
    double doubleFunction3(double a1, double a2, double a3) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return 0;
    }
    double doubleFunction4(double a1, double a2, double a3, double a4) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return 0;
    }
    double doubleFunction5(double a1, double a2, double a3, double a4, double a5) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return 0;
    }
    double doubleFunction6(double a1, double a2, double a3, double a4, double a5, double a6) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return 0;
    }
    double doubleFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return 0;
    }
    double doubleFunctionB1(bool a1) {
        return a1 ? 1 : 0;
    }
    double doubleFunctionB2(bool a1, double a2) {
        Q_UNUSED(a2);
        return a1 ? 1 : 0;
    }
    double doubleFunctionB3(bool a1, double a2, double a3) {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return a1 ? 1 : 0;
    }
    double doubleFunctionB4(bool a1, double a2, double a3, double a4) {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return a1 ? 1 : 0;
    }
    double doubleFunctionB5(bool a1, double a2, double a3, double a4, double a5) {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return a1 ? 1 : 0;
    }
    double doubleFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return a1 ? 1 : 0;
    }
    double doubleFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return a1 ? 1 : 0;
    }



    // const function
    void voidConstFunction0() const {
        qDebug() << "Member::voidConstFunction0";
        QVERIFY(true);
    }
    void voidConstFunction1(int a1) const {
        qDebug() << "Member::voidConstFunction1:" << a1;
    }
    void voidConstFunction2(int a1, int a2) const {
        qDebug() << "Member::voidConstFunction2:" << a1 << "," << a2;
    }
    void voidConstFunction3(int a1, int a2, int a3) const {
        qDebug() << "Member::voidConstFunction3:" << a1 << "," << a2 << "," << a3;
    }
    void voidConstFunction4(int a1, int a2, int a3, int a4) const {
        qDebug() << "Member::voidConstFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    void voidConstFunction5(int a1, int a2, int a3, int a4, int a5) const {
        qDebug() << "Member::voidConstFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    void voidConstFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const {
        qDebug() << "Member::voidConstFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    void voidConstFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const {
        qDebug() << "Member::voidConstFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }
    void voidConstFunctionB1(bool a1) const {
        qDebug() << "Member::voidConstFunctionB1:" << a1;
    }
    void voidConstFunctionB2(bool a1, int a2) const {
        qDebug() << "Member::voidConstFunctionB2:" << a1 << "," << a2;
    }
    void voidConstFunctionB3(bool a1, int a2, int a3) const {
        qDebug() << "Member::voidConstFunctionB3:" << a1 << "," << a2 << "," << a3;
    }
    void voidConstFunctionB4(bool a1, int a2, int a3, int a4) const {
        qDebug() << "Member::voidConstFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    void voidConstFunctionB5(bool a1, int a2, int a3, int a4, int a5) const {
        qDebug() << "Member::voidConstFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    void voidConstFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const {
        qDebug() << "Member::voidConstFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    void voidConstFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const {
        qDebug() << "Member::voidConstFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }

    int intConstFunction0() const {
        return 0;
    }
    int intConstFunction1(int a1) const {
        Q_UNUSED(a1);
        return 0;
    }
    int intConstFunction2(int a1, int a2) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        return 0;
    }
    int intConstFunction3(int a1, int a2, int a3) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return 0;
    }
    int intConstFunction4(int a1, int a2, int a3, int a4) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return 0;
    }
    int intConstFunction5(int a1, int a2, int a3, int a4, int a5) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return 0;
    }
    int intConstFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return 0;
    }
    int intConstFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return 0;
    }
    int intConstFunctionB1(bool a1) const {
        return a1 ? 1 : 0;
    }
    int intConstFunctionB2(bool a1, int a2) const {
        Q_UNUSED(a2);
        return a1 ? 1 : 0;
    }
    int intConstFunctionB3(bool a1, int a2, int a3) const {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return a1 ? 1 : 0;
    }
    int intConstFunctionB4(bool a1, int a2, int a3, int a4) const {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return a1 ? 1 : 0;
    }
    int intConstFunctionB5(bool a1, int a2, int a3, int a4, int a5) const {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return a1 ? 1 : 0;
    }
    int intConstFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return a1 ? 1 : 0;
    }
    int intConstFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return a1 ? 1 : 0;
    }

    double doubleConstFunction0() const {
        return 0;
    }
    double doubleConstFunction1(double a1) const {
        Q_UNUSED(a1);
        return 0;
    }
    double doubleConstFunction2(double a1, double a2) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        return 0;
    }
    double doubleConstFunction3(double a1, double a2, double a3) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return 0;
    }
    double doubleConstFunction4(double a1, double a2, double a3, double a4) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return 0;
    }
    double doubleConstFunction5(double a1, double a2, double a3, double a4, double a5) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return 0;
    }
    double doubleConstFunction6(double a1, double a2, double a3, double a4, double a5, double a6) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return 0;
    }
    double doubleConstFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return 0;
    }
    double doubleConstFunctionB1(bool a1) const {
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB2(bool a1, double a2) const {
        Q_UNUSED(a2);
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB3(bool a1, double a2, double a3) const {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB4(bool a1, double a2, double a3, double a4) const {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB5(bool a1, double a2, double a3, double a4, double a5) const {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) const {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return a1 ? 1 : 0;
    }
    double doubleConstFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return a1 ? 1 : 0;
    }


    // volatile function
    void voidVolatileFunction0() volatile {
        qDebug() << "Member::voidVolatileFunction0";
        QVERIFY(true);
    }
    void voidVolatileFunction1(int a1) volatile {
        qDebug() << "Member::voidVolatileFunction1:" << a1;
    }
    void voidVolatileFunction2(int a1, int a2) volatile {
        qDebug() << "Member::voidVolatileFunction2:" << a1 << "," << a2;
    }
    void voidVolatileFunction3(int a1, int a2, int a3) volatile {
        qDebug() << "Member::voidVolatileFunction3:" << a1 << "," << a2 << "," << a3;
    }
    void voidVolatileFunction4(int a1, int a2, int a3, int a4) volatile {
        qDebug() << "Member::voidVolatileFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    void voidVolatileFunction5(int a1, int a2, int a3, int a4, int a5) volatile {
        qDebug() << "Member::voidVolatileFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    void voidVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) volatile {
        qDebug() << "Member::voidVolatileFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    void voidVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile {
        qDebug() << "Member::voidVolatileFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }
    void voidVolatileFunctionB1(bool a1) volatile {
        qDebug() << "Member::voidVolatileFunctionB1:" << a1;
    }
    void voidVolatileFunctionB2(bool a1, int a2) volatile {
        qDebug() << "Member::voidVolatileFunctionB2:" << a1 << "," << a2;
    }
    void voidVolatileFunctionB3(bool a1, int a2, int a3) volatile {
        qDebug() << "Member::voidVolatileFunctionB3:" << a1 << "," << a2 << "," << a3;
    }
    void voidVolatileFunctionB4(bool a1, int a2, int a3, int a4) volatile {
        qDebug() << "Member::voidVolatileFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    void voidVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile {
        qDebug() << "Member::voidVolatileFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    void voidVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) volatile {
        qDebug() << "Member::voidVolatileFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    void voidVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile {
        qDebug() << "Member::voidVolatileFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }

    int intVolatileFunction0() volatile {
        return 0;
    }
    int intVolatileFunction1(int a1) volatile {
        Q_UNUSED(a1);
        return 0;
    }
    int intVolatileFunction2(int a1, int a2) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        return 0;
    }
    int intVolatileFunction3(int a1, int a2, int a3) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return 0;
    }
    int intVolatileFunction4(int a1, int a2, int a3, int a4) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return 0;
    }
    int intVolatileFunction5(int a1, int a2, int a3, int a4, int a5) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return 0;
    }
    int intVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return 0;
    }
    int intVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return 0;
    }
    int intVolatileFunctionB1(bool a1) volatile {
        return a1;
    }
    int intVolatileFunctionB2(bool a1, int a2) volatile {
        Q_UNUSED(a2);
        return a1 ? 1 : 0;
    }
    int intVolatileFunctionB3(bool a1, int a2, int a3) volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return a1 ? 1 : 0;
    }
    int intVolatileFunctionB4(bool a1, int a2, int a3, int a4) volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return a1 ? 1 : 0;
    }
    int intVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return a1 ? 1 : 0;
    }
    int intVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return a1 ? 1 : 0;
    }
    int intVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return a1 ? 1 : 0;
    }

    double doubleVolatileFunction0() volatile {
        return 0;
    }
    double doubleVolatileFunction1(double a1) volatile {
        Q_UNUSED(a1);
        return 0;
    }
    double doubleVolatileFunction2(double a1, double a2) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        return 0;
    }
    double doubleVolatileFunction3(double a1, double a2, double a3) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return 0;
    }
    double doubleVolatileFunction4(double a1, double a2, double a3, double a4) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return 0;
    }
    double doubleVolatileFunction5(double a1, double a2, double a3, double a4, double a5) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return 0;
    }
    double doubleVolatileFunction6(double a1, double a2, double a3, double a4, double a5, double a6) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return 0;
    }
    double doubleVolatileFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return 0;
    }
    double doubleVolatileFunctionB1(bool a1) volatile {
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB2(bool a1, double a2) volatile {
        Q_UNUSED(a2);
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB3(bool a1, double a2, double a3) volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB4(bool a1, double a2, double a3, double a4) volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB5(bool a1, double a2, double a3, double a4, double a5) volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return a1 ? 1 : 0;
    }
    double doubleVolatileFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return a1 ? 1 : 0;
    }



    // const volatile
    void voidConstVolatileFunction0() const volatile {
        qDebug() << "Member::voidConstVolatileFunction0";
        QVERIFY(true);
    }
    void voidConstVolatileFunction1(int a1) const volatile {
        qDebug() << "Member::voidConstVolatileFunction1:" << a1;
    }
    void voidConstVolatileFunction2(int a1, int a2) const volatile {
        qDebug() << "Member::voidConstVolatileFunction2:" << a1 << "," << a2;
    }
    void voidConstVolatileFunction3(int a1, int a2, int a3) const volatile {
        qDebug() << "Member::voidConstVolatileFunction3:" << a1 << "," << a2 << "," << a3;
    }
    void voidConstVolatileFunction4(int a1, int a2, int a3, int a4) const volatile {
        qDebug() << "Member::voidConstVolatileFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    void voidConstVolatileFunction5(int a1, int a2, int a3, int a4, int a5) const volatile {
        qDebug() << "Member::voidConstVolatileFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    void voidConstVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const volatile {
        qDebug() << "Member::voidConstVolatileFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    void voidConstVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile {
        qDebug() << "Member::voidConstVolatileFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }
    void voidConstVolatileFunctionB1(bool a1) const volatile {
        qDebug() << "Member::voidConstVolatileFunctionB1:" << a1;
    }
    void voidConstVolatileFunctionB2(bool a1, int a2) const volatile {
        qDebug() << "Member::voidConstVolatileFunctionB2:" << a1 << "," << a2;
    }
    void voidConstVolatileFunctionB3(bool a1, int a2, int a3) const volatile {
        qDebug() << "Member::voidConstVolatileFunctionB3:" << a1 << "," << a2 << "," << a3;
    }
    void voidConstVolatileFunctionB4(bool a1, int a2, int a3, int a4) const volatile {
        qDebug() << "Member::voidConstVolatileFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4;
    }
    void voidConstVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) const volatile {
        qDebug() << "Member::voidConstVolatileFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
    }
    void voidConstVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile {
        qDebug() << "Member::voidConstVolatileFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
    }
    void voidConstVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile {
        qDebug() << "Member::voidConstVolatileFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
    }

    int intConstVolatileFunction0() const volatile {
        return 0;
    }
    int intConstVolatileFunction1(int a1) const volatile {
        Q_UNUSED(a1);
        return 0;
    }
    int intConstVolatileFunction2(int a1, int a2) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        return 0;
    }
    int intConstVolatileFunction3(int a1, int a2, int a3) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return 0;
    }
    int intConstVolatileFunction4(int a1, int a2, int a3, int a4) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return 0;
    }
    int intConstVolatileFunction5(int a1, int a2, int a3, int a4, int a5) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return 0;
    }
    int intConstVolatileFunction6(int a1, int a2, int a3, int a4, int a5, int a6) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return 0;
    }
    int intConstVolatileFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return 0;
    }
    int intConstVolatileFunctionB1(bool a1) const volatile {
        return a1;
    }
    int intConstVolatileFunctionB2(bool a1, int a2) const volatile {
        Q_UNUSED(a2);
        return a1 ? 1 : 0;
    }
    int intConstVolatileFunctionB3(bool a1, int a2, int a3) const volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return a1 ? 1 : 0;
    }
    int intConstVolatileFunctionB4(bool a1, int a2, int a3, int a4) const volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return a1 ? 1 : 0;
    }
    int intConstVolatileFunctionB5(bool a1, int a2, int a3, int a4, int a5) const volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return a1 ? 1 : 0;
    }
    int intConstVolatileFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) const volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return a1 ? 1 : 0;
    }
    int intConstVolatileFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) const volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return a1 ? 1 : 0;
    }

    double doubleConstVolatileFunction0() const volatile {
        return 0;
    }
    double doubleConstVolatileFunction1(double a1) const volatile {
        Q_UNUSED(a1);
        return 0;
    }
    double doubleConstVolatileFunction2(double a1, double a2) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        return 0;
    }
    double doubleConstVolatileFunction3(double a1, double a2, double a3) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return 0;
    }
    double doubleConstVolatileFunction4(double a1, double a2, double a3, double a4) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return 0;
    }
    double doubleConstVolatileFunction5(double a1, double a2, double a3, double a4, double a5) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return 0;
    }
    double doubleConstVolatileFunction6(double a1, double a2, double a3, double a4, double a5, double a6) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return 0;
    }
    double doubleConstVolatileFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile {
        Q_UNUSED(a1);
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return 0;
    }
    double doubleConstVolatileFunctionB1(bool a1) const volatile {
        Q_UNUSED(a1);
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB2(bool a1, double a2) const volatile {
        Q_UNUSED(a2);
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB3(bool a1, double a2, double a3) const volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB4(bool a1, double a2, double a3, double a4) const volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB5(bool a1, double a2, double a3, double a4, double a5) const volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) const volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        return a1 ? 1 : 0;
    }
    double doubleConstVolatileFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) const volatile {
        Q_UNUSED(a2);
        Q_UNUSED(a3);
        Q_UNUSED(a4);
        Q_UNUSED(a5);
        Q_UNUSED(a6);
        Q_UNUSED(a7);
        return a1 ? 1 : 0;
    }
};

class QEXTMemberFunctorTest : public QObject
{
    Q_OBJECT
private slots:
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

    void testQObjectSignal() {
        connect(this, SIGNAL(testSignal()), this, SLOT(testSlot()));
        QEXTMemberFunctor<void, QEXTMemberFunctorTest> functor = qextMemberFunctor(&QEXTMemberFunctorTest::testSignal);
        functor(this);
    }

signals:
    void testSignal();

protected slots:
    void testSlot() {
        qDebug() << "testSlot";
    }
};



void QEXTMemberFunctorTest::testFunctorWith0Arg()
{
    MemberBase memberBase;

    QEXTMemberFunctor0<void, MemberBase> voidMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::voidFunction0);
    voidMemberBaseFunctor0_(&memberBase);
    QEXTMemberFunctor0<int, MemberBase> intMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::intFunction0);
    intMemberBaseFunctor0_(&memberBase);
    QEXTMemberFunctor0<double, MemberBase> doubleMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::doubleFunction0);
    doubleMemberBaseFunctor0_(&memberBase);

    QEXTMemberFunctor0<void, MemberBase> voidMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction0);
    voidMemberBaseFunctor0_obj(&memberBase);
    QEXTMemberFunctor0<int, MemberBase> intMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction0);
    intMemberBaseFunctor0_obj(&memberBase);
    QEXTMemberFunctor0<double, MemberBase> doubleMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction0);
    doubleMemberBaseFunctor0_obj(&memberBase);

    QEXTMemberFunctor0<void, MemberBase> voidMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::voidFunction0);
    voidMemberBaseFunctor0(&memberBase);
    QEXTMemberFunctor0<int, MemberBase> intMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::intFunction0);
    intMemberBaseFunctor0(&memberBase);
    QEXTMemberFunctor0<double, MemberBase> doubleMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::doubleFunction0);
    doubleMemberBaseFunctor0(&memberBase);

    QEXTMemberFunctor<void, MemberBase> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction0);
    voidMemberBaseFunctor(&memberBase);
    QEXTMemberFunctor<int, MemberBase> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction0);
    intMemberBaseFunctor(&memberBase);
    QEXTMemberFunctor<double, MemberBase> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction0);
    doubleMemberBaseFunctor(&memberBase);
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith0Arg()
{
    Member member;

    QEXTMemberFunctor0<void, MemberBase> voidMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::voidFunction0);
    voidMemberBaseFunctor0_(&member);
    QEXTMemberFunctor0<int, MemberBase> intMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::intFunction0);
    intMemberBaseFunctor0_(&member);
    QEXTMemberFunctor0<double, MemberBase> doubleMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::doubleFunction0);
    doubleMemberBaseFunctor0_(&member);

    QEXTMemberFunctor0<void, MemberBase> voidMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction0);
    voidMemberBaseFunctor0_obj(&member);
    QEXTMemberFunctor0<int, MemberBase> intMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction0);
    intMemberBaseFunctor0_obj(&member);
    QEXTMemberFunctor0<double, MemberBase> doubleMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction0);
    doubleMemberBaseFunctor0_obj(&member);

    QEXTMemberFunctor0<void, MemberBase> voidMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::voidFunction0);
    voidMemberBaseFunctor0(&member);
    QEXTMemberFunctor0<int, MemberBase> intMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::intFunction0);
    intMemberBaseFunctor0(&member);
    QEXTMemberFunctor0<double, MemberBase> doubleMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::doubleFunction0);
    doubleMemberBaseFunctor0(&member);

    QEXTMemberFunctor<void, MemberBase> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction0);
    voidMemberBaseFunctor(&member);
    QEXTMemberFunctor<int, MemberBase> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction0);
    intMemberBaseFunctor(&member);
    QEXTMemberFunctor<double, MemberBase> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction0);
    doubleMemberBaseFunctor(&member);
}

void QEXTMemberFunctorTest::testConstFunctorWith0Arg()
{
    MemberBase memberBase;

    QEXTConstMemberFunctor0<void, MemberBase> voidConstMemberBaseFunctor0_ = qextMemberFunctor0(&MemberBase::voidConstFunction0);
    voidConstMemberBaseFunctor0_(&memberBase);
    QEXTConstMemberFunctor0<int, MemberBase> intConstMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::intConstFunction0);
    intConstMemberBaseFunctor0_(&memberBase);
    QEXTConstMemberFunctor0<double, MemberBase> doubleConstMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::doubleConstFunction0);
    doubleConstMemberBaseFunctor0_(&memberBase);

    QEXTConstMemberFunctor0<void, MemberBase> voidConstMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction0);
    voidConstMemberBaseFunctor0_obj(&memberBase);
    QEXTConstMemberFunctor0<int, MemberBase> intConstMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction0);
    intConstMemberBaseFunctor0_obj(&memberBase);
    QEXTConstMemberFunctor0<double, MemberBase> doubleConstMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction0);
    doubleConstMemberBaseFunctor0_obj(&memberBase);

    QEXTConstMemberFunctor0<void, MemberBase> voidConstMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::voidConstFunction0);
    voidConstMemberBaseFunctor0(&memberBase);
    QEXTConstMemberFunctor0<int, MemberBase> intConstMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::intConstFunction0);
    intConstMemberBaseFunctor0(&memberBase);
    QEXTConstMemberFunctor0<double, MemberBase> doubleConstMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::doubleConstFunction0);
    doubleConstMemberBaseFunctor0(&memberBase);

    QEXTConstMemberFunctor<void, MemberBase> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction0);
    voidConstMemberBaseFunctor(&memberBase);
    QEXTConstMemberFunctor<int, MemberBase> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction0);
    intConstMemberBaseFunctor(&memberBase);
    QEXTConstMemberFunctor<double, MemberBase> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction0);
    doubleConstMemberBaseFunctor(&memberBase);
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith0Arg()
{
    Member member;

    QEXTConstMemberFunctor0<void, MemberBase> voidConstMemberBaseFunctor0_ = qextMemberFunctor0(&MemberBase::voidConstFunction0);
    voidConstMemberBaseFunctor0_(&member);
    QEXTConstMemberFunctor0<int, MemberBase> intConstMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::intConstFunction0);
    intConstMemberBaseFunctor0_(&member);
    QEXTConstMemberFunctor0<double, MemberBase> doubleConstMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::doubleConstFunction0);
    doubleConstMemberBaseFunctor0_(&member);

    QEXTConstMemberFunctor0<void, MemberBase> voidConstMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction0);
    voidConstMemberBaseFunctor0_obj(&member);
    QEXTConstMemberFunctor0<int, MemberBase> intConstMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction0);
    intConstMemberBaseFunctor0_obj(&member);
    QEXTConstMemberFunctor0<double, MemberBase> doubleConstMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction0);
    doubleConstMemberBaseFunctor0_obj(&member);

    QEXTConstMemberFunctor0<void, MemberBase> voidConstMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::voidConstFunction0);
    voidConstMemberBaseFunctor0(&member);
    QEXTConstMemberFunctor0<int, MemberBase> intConstMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::intConstFunction0);
    intConstMemberBaseFunctor0(&member);
    QEXTConstMemberFunctor0<double, MemberBase> doubleConstMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::doubleConstFunction0);
    doubleConstMemberBaseFunctor0(&member);

    QEXTConstMemberFunctor<void, MemberBase> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction0);
    voidConstMemberBaseFunctor(&member);
    QEXTConstMemberFunctor<int, MemberBase> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction0);
    intConstMemberBaseFunctor(&member);
    QEXTConstMemberFunctor<double, MemberBase> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction0);
    doubleConstMemberBaseFunctor(&member);
}

void QEXTMemberFunctorTest::testVolatileFunctorWith0Arg()
{
    MemberBase memberBase;

    QEXTVolatileMemberFunctor0<void, MemberBase> voidVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::voidVolatileFunction0);
    voidVolatileMemberBaseFunctor0_(&memberBase);
    QEXTVolatileMemberFunctor0<int, MemberBase> intVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::intVolatileFunction0);
    intVolatileMemberBaseFunctor0_(&memberBase);
    QEXTVolatileMemberFunctor0<double, MemberBase> doubleVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction0);
    doubleVolatileMemberBaseFunctor0_(&memberBase);

    QEXTVolatileMemberFunctor0<void, MemberBase> voidVolatileMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction0);
    voidVolatileMemberBaseFunctor0_obj(&memberBase);
    QEXTVolatileMemberFunctor0<int, MemberBase> intVolatileMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction0);
    intVolatileMemberBaseFunctor0_obj(&memberBase);
    QEXTVolatileMemberFunctor0<double, MemberBase> doubleVolatileMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction0);
    doubleVolatileMemberBaseFunctor0_obj(&memberBase);

    QEXTVolatileMemberFunctor0<void, MemberBase> voidVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::voidVolatileFunction0);
    voidVolatileMemberBaseFunctor0(&memberBase);
    QEXTVolatileMemberFunctor0<int, MemberBase> intVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::intVolatileFunction0);
    intVolatileMemberBaseFunctor0(&memberBase);
    QEXTVolatileMemberFunctor0<double, MemberBase> doubleVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::doubleVolatileFunction0);
    doubleVolatileMemberBaseFunctor0(&memberBase);

    QEXTVolatileMemberFunctor<void, MemberBase> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction0);
    voidVolatileMemberBaseFunctor(&memberBase);
    QEXTVolatileMemberFunctor<int, MemberBase> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction0);
    intVolatileMemberBaseFunctor(&memberBase);
    QEXTVolatileMemberFunctor<double, MemberBase> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction0);
    doubleVolatileMemberBaseFunctor(&memberBase);
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith0Arg()
{
    Member member;

    QEXTVolatileMemberFunctor0<void, MemberBase> voidVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::voidVolatileFunction0);
    voidVolatileMemberBaseFunctor0_(&member);
    QEXTVolatileMemberFunctor0<int, MemberBase> intVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::intVolatileFunction0);
    intVolatileMemberBaseFunctor0_(&member);
    QEXTVolatileMemberFunctor0<double, MemberBase> doubleVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction0);
    doubleVolatileMemberBaseFunctor0_(&member);

    QEXTVolatileMemberFunctor0<void, MemberBase> voidVolatileMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction0);
    voidVolatileMemberBaseFunctor0_obj(&member);
    QEXTVolatileMemberFunctor0<int, MemberBase> intVolatileMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction0);
    intVolatileMemberBaseFunctor0_obj(&member);
    QEXTVolatileMemberFunctor0<double, MemberBase> doubleVolatileMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction0);
    doubleVolatileMemberBaseFunctor0_obj(&member);

    QEXTVolatileMemberFunctor0<void, MemberBase> voidVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::voidVolatileFunction0);
    voidVolatileMemberBaseFunctor0(&member);
    QEXTVolatileMemberFunctor0<int, MemberBase> intVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::intVolatileFunction0);
    intVolatileMemberBaseFunctor0(&member);
    QEXTVolatileMemberFunctor0<double, MemberBase> doubleVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::doubleVolatileFunction0);
    doubleVolatileMemberBaseFunctor0(&member);

    QEXTVolatileMemberFunctor<void, MemberBase> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction0);
    voidVolatileMemberBaseFunctor(&member);
    QEXTVolatileMemberFunctor<int, MemberBase> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction0);
    intVolatileMemberBaseFunctor(&member);
    QEXTVolatileMemberFunctor<double, MemberBase> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction0);
    doubleVolatileMemberBaseFunctor(&member);
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith0Arg()
{
    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor0<void, MemberBase> voidConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction0);
    voidConstVolatileMemberBaseFunctor0_(&memberBase);
    QEXTConstVolatileMemberFunctor0<int, MemberBase> intConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction0);
    intConstVolatileMemberBaseFunctor0_(&memberBase);
    QEXTConstVolatileMemberFunctor0<double, MemberBase> doubleConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction0);
    doubleConstVolatileMemberBaseFunctor0_(&memberBase);

    QEXTConstVolatileMemberFunctor0<void, MemberBase> voidConstVolatileMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction0);
    voidConstVolatileMemberBaseFunctor0_obj(&memberBase);
    QEXTConstVolatileMemberFunctor0<int, MemberBase> intConstVolatileMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction0);
    intConstVolatileMemberBaseFunctor0_obj(&memberBase);
    QEXTConstVolatileMemberFunctor0<double, MemberBase> doubleConstVolatileMemberBaseFunctor0_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction0);
    doubleConstVolatileMemberBaseFunctor0_obj(&memberBase);

    QEXTConstVolatileMemberFunctor0<void, MemberBase> voidConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::voidConstVolatileFunction0);
    voidConstVolatileMemberBaseFunctor0(&memberBase);
    QEXTConstVolatileMemberFunctor0<int, MemberBase> intConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::intConstVolatileFunction0);
    intConstVolatileMemberBaseFunctor0(&memberBase);
    QEXTConstVolatileMemberFunctor0<double, MemberBase> doubleConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::doubleConstVolatileFunction0);
    doubleConstVolatileMemberBaseFunctor0(&memberBase);

    QEXTConstVolatileMemberFunctor<void, MemberBase> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction0);
    voidConstVolatileMemberBaseFunctor(&memberBase);
    QEXTConstVolatileMemberFunctor<int, MemberBase> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction0);
    intConstVolatileMemberBaseFunctor(&memberBase);
    QEXTConstVolatileMemberFunctor<double, MemberBase> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction0);
    doubleConstVolatileMemberBaseFunctor(&memberBase);
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith0Arg()
{
    Member member;

    QEXTConstVolatileMemberFunctor0<void, MemberBase> voidConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction0);
    voidConstVolatileMemberBaseFunctor0_(&member);
    QEXTConstVolatileMemberFunctor0<int, MemberBase> intConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction0);
    intConstVolatileMemberBaseFunctor0_(&member);
    QEXTConstVolatileMemberFunctor0<double, MemberBase> doubleConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction0);
    doubleConstVolatileMemberBaseFunctor0_(&member);

    QEXTConstVolatileMemberFunctor0<void, MemberBase> voidConstVolatileMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction0);
    voidConstVolatileMemberBaseFunctor0_obj(&member);
    QEXTConstVolatileMemberFunctor0<int, MemberBase> intConstVolatileMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction0);
    intConstVolatileMemberBaseFunctor0_obj(&member);
    QEXTConstVolatileMemberFunctor0<double, MemberBase> doubleConstVolatileMemberBaseFunctor0_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction0);
    doubleConstVolatileMemberBaseFunctor0_obj(&member);

    QEXTConstVolatileMemberFunctor0<void, MemberBase> voidConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::voidConstVolatileFunction0);
    voidConstVolatileMemberBaseFunctor0(&member);
    QEXTConstVolatileMemberFunctor0<int, MemberBase> intConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::intConstVolatileFunction0);
    intConstVolatileMemberBaseFunctor0(&member);
    QEXTConstVolatileMemberFunctor0<double, MemberBase> doubleConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(&MemberBase::doubleConstVolatileFunction0);
    doubleConstVolatileMemberBaseFunctor0(&member);

    QEXTConstVolatileMemberFunctor<void, MemberBase> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction0);
    voidConstVolatileMemberBaseFunctor(&member);
    QEXTConstVolatileMemberFunctor<int, MemberBase> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction0);
    intConstVolatileMemberBaseFunctor(&member);
    QEXTConstVolatileMemberFunctor<double, MemberBase> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction0);
    doubleConstVolatileMemberBaseFunctor(&member);
}

void QEXTMemberFunctorTest::testBoundFunctorWith0Arg()
{
    MemberBase memberBase;

    QEXTBoundMemberFunctor0<void, MemberBase> voidBoundMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctor0_();
    QEXTBoundMemberFunctor0<int, MemberBase> intBoundMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::intFunction0);
    intBoundMemberBaseFunctor0_();
    QEXTBoundMemberFunctor0<double, MemberBase> doubleBoundMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctor0_();

    QEXTBoundMemberFunctor0<void, MemberBase> voidBoundMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctor0();
    QEXTBoundMemberFunctor0<int, MemberBase> intBoundMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::intFunction0);
    intBoundMemberBaseFunctor0();
    QEXTBoundMemberFunctor0<double, MemberBase> doubleBoundMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctor0();

    QEXTBoundMemberFunctor<void, MemberBase> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctor();
    QEXTBoundMemberFunctor<int, MemberBase> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction0);
    intBoundMemberBaseFunctor();
    QEXTBoundMemberFunctor<double, MemberBase> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctor();
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith0Arg()
{
    Member member;

    QEXTBoundMemberFunctor0<void, MemberBase> voidBoundMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctor0_();
    QEXTBoundMemberFunctor0<int, MemberBase> intBoundMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction0);
    intBoundMemberBaseFunctor0_();
    QEXTBoundMemberFunctor0<double, MemberBase> doubleBoundMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctor0_();

    QEXTBoundMemberFunctor0<void, MemberBase> voidBoundMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctor0();
    QEXTBoundMemberFunctor0<int, MemberBase> intBoundMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction0);
    intBoundMemberBaseFunctor0();
    QEXTBoundMemberFunctor0<double, MemberBase> doubleBoundMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctor0();

    QEXTBoundMemberFunctor<void, MemberBase> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction0);
    voidBoundMemberBaseFunctor();
    QEXTBoundMemberFunctor<int, MemberBase> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction0);
    intBoundMemberBaseFunctor();
    QEXTBoundMemberFunctor<double, MemberBase> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction0);
    doubleBoundMemberBaseFunctor();
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith0Arg()
{
    MemberBase memberBase;

    QEXTBoundConstMemberFunctor0<void, MemberBase> voidBoundConstMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction0);
    voidBoundConstMemberBaseFunctor0_();
    QEXTBoundConstMemberFunctor0<int, MemberBase> intBoundConstMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction0);
    intBoundConstMemberBaseFunctor0_();
    QEXTBoundConstMemberFunctor0<double, MemberBase> doubleBoundConstMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction0);
    doubleBoundConstMemberBaseFunctor0_();

    QEXTBoundConstMemberFunctor0<void, MemberBase> voidBoundConstMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::voidConstFunction0);
    voidBoundConstMemberBaseFunctor0();
    QEXTBoundConstMemberFunctor0<int, MemberBase> intBoundConstMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::intConstFunction0);
    intBoundConstMemberBaseFunctor0();
    QEXTBoundConstMemberFunctor0<double, MemberBase> doubleBoundConstMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::doubleConstFunction0);
    doubleBoundConstMemberBaseFunctor0();

    QEXTBoundConstMemberFunctor<void, MemberBase> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction0);
    voidBoundConstMemberBaseFunctor();
    QEXTBoundConstMemberFunctor<int, MemberBase> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction0);
    intBoundConstMemberBaseFunctor();
    QEXTBoundConstMemberFunctor<double, MemberBase> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction0);
    doubleBoundConstMemberBaseFunctor();
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith0Arg()
{
    Member member;

    QEXTBoundConstMemberFunctor0<void, MemberBase> voidBoundConstMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction0);
    voidBoundConstMemberBaseFunctor0_();
    QEXTBoundConstMemberFunctor0<int, MemberBase> intBoundConstMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction0);
    intBoundConstMemberBaseFunctor0_();
    QEXTBoundConstMemberFunctor0<double, MemberBase> doubleBoundConstMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction0);
    doubleBoundConstMemberBaseFunctor0_();

    QEXTBoundConstMemberFunctor0<void, MemberBase> voidBoundConstMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction0);
    voidBoundConstMemberBaseFunctor0();
    QEXTBoundConstMemberFunctor0<int, MemberBase> intBoundConstMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction0);
    intBoundConstMemberBaseFunctor0();
    QEXTBoundConstMemberFunctor0<double, MemberBase> doubleBoundConstMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction0);
    doubleBoundConstMemberBaseFunctor0();

    QEXTBoundConstMemberFunctor<void, MemberBase> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction0);
    voidBoundConstMemberBaseFunctor();
    QEXTBoundConstMemberFunctor<int, MemberBase> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction0);
    intBoundConstMemberBaseFunctor();
    QEXTBoundConstMemberFunctor<double, MemberBase> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction0);
    doubleBoundConstMemberBaseFunctor();
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith0Arg()
{
    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor0<void, MemberBase> voidBoundVolatileMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction0);
    voidBoundVolatileMemberBaseFunctor0_();
    QEXTBoundVolatileMemberFunctor0<int, MemberBase> intBoundVolatileMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction0);
    intBoundVolatileMemberBaseFunctor0_();
    QEXTBoundVolatileMemberFunctor0<double, MemberBase> doubleBoundVolatileMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction0);
    doubleBoundVolatileMemberBaseFunctor0_();

    QEXTBoundVolatileMemberFunctor0<void, MemberBase> voidBoundVolatileMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::voidVolatileFunction0);
    voidBoundVolatileMemberBaseFunctor0();
    QEXTBoundVolatileMemberFunctor0<int, MemberBase> intBoundVolatileMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::intVolatileFunction0);
    intBoundVolatileMemberBaseFunctor0();
    QEXTBoundVolatileMemberFunctor0<double, MemberBase> doubleBoundVolatileMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::doubleVolatileFunction0);
    doubleBoundVolatileMemberBaseFunctor0();

    QEXTBoundVolatileMemberFunctor<void, MemberBase> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction0);
    voidBoundVolatileMemberBaseFunctor();
    QEXTBoundVolatileMemberFunctor<int, MemberBase> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction0);
    intBoundVolatileMemberBaseFunctor();
    QEXTBoundVolatileMemberFunctor<double, MemberBase> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction0);
    doubleBoundVolatileMemberBaseFunctor();
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith0Arg()
{
    Member member;

    QEXTBoundVolatileMemberFunctor0<void, MemberBase> voidBoundVolatileMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction0);
    voidBoundVolatileMemberBaseFunctor0_();
    QEXTBoundVolatileMemberFunctor0<int, MemberBase> intBoundVolatileMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction0);
    intBoundVolatileMemberBaseFunctor0_();
    QEXTBoundVolatileMemberFunctor0<double, MemberBase> doubleBoundVolatileMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction0);
    doubleBoundVolatileMemberBaseFunctor0_();

    QEXTBoundVolatileMemberFunctor0<void, MemberBase> voidBoundVolatileMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction0);
    voidBoundVolatileMemberBaseFunctor0();
    QEXTBoundVolatileMemberFunctor0<int, MemberBase> intBoundVolatileMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction0);
    intBoundVolatileMemberBaseFunctor0();
    QEXTBoundVolatileMemberFunctor0<double, MemberBase> doubleBoundVolatileMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction0);
    doubleBoundVolatileMemberBaseFunctor0();

    QEXTBoundVolatileMemberFunctor<void, MemberBase> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction0);
    voidBoundVolatileMemberBaseFunctor();
    QEXTBoundVolatileMemberFunctor<int, MemberBase> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction0);
    intBoundVolatileMemberBaseFunctor();
    QEXTBoundVolatileMemberFunctor<double, MemberBase> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction0);
    doubleBoundVolatileMemberBaseFunctor();
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith0Arg()
{
    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor0<void, MemberBase> voidBoundConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction0);
    voidBoundConstVolatileMemberBaseFunctor0_();
    QEXTBoundConstVolatileMemberFunctor0<int, MemberBase> intBoundConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction0);
    intBoundConstVolatileMemberBaseFunctor0_();
    QEXTBoundConstVolatileMemberFunctor0<double, MemberBase> doubleBoundConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction0);
    doubleBoundConstVolatileMemberBaseFunctor0_();

    QEXTBoundConstVolatileMemberFunctor0<void, MemberBase> voidBoundConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::voidConstVolatileFunction0);
    voidBoundConstVolatileMemberBaseFunctor0();
    QEXTBoundConstVolatileMemberFunctor0<int, MemberBase> intBoundConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::intConstVolatileFunction0);
    intBoundConstVolatileMemberBaseFunctor0();
    QEXTBoundConstVolatileMemberFunctor0<double, MemberBase> doubleBoundConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(&memberBase, &MemberBase::doubleConstVolatileFunction0);
    doubleBoundConstVolatileMemberBaseFunctor0();

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction0);
    voidBoundConstVolatileMemberBaseFunctor();
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction0);
    intBoundConstVolatileMemberBaseFunctor();
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction0);
    doubleBoundConstVolatileMemberBaseFunctor();
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith0Arg()
{
    Member member;

    QEXTBoundConstVolatileMemberFunctor0<void, MemberBase> voidBoundConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction0);
    voidBoundConstVolatileMemberBaseFunctor0_();
    QEXTBoundConstVolatileMemberFunctor0<int, MemberBase> intBoundConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction0);
    intBoundConstVolatileMemberBaseFunctor0_();
    QEXTBoundConstVolatileMemberFunctor0<double, MemberBase> doubleBoundConstVolatileMemberBaseFunctor0_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction0);
    doubleBoundConstVolatileMemberBaseFunctor0_();

    QEXTBoundConstVolatileMemberFunctor0<void, MemberBase> voidBoundConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction0);
    voidBoundConstVolatileMemberBaseFunctor0();
    QEXTBoundConstVolatileMemberFunctor0<int, MemberBase> intBoundConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction0);
    intBoundConstVolatileMemberBaseFunctor0();
    QEXTBoundConstVolatileMemberFunctor0<double, MemberBase> doubleBoundConstVolatileMemberBaseFunctor0 = qextMemberFunctor0(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction0);
    doubleBoundConstVolatileMemberBaseFunctor0();

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction0);
    voidBoundConstVolatileMemberBaseFunctor();
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction0);
    intBoundConstVolatileMemberBaseFunctor();
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction0);
    doubleBoundConstVolatileMemberBaseFunctor();
}

void QEXTMemberFunctorTest::testFunctorWith1Arg()
{
    MemberBase memberBase;

    QEXTMemberFunctor1<void, MemberBase, int> voidMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::voidFunction1);
    voidMemberBaseFunctor1_(&memberBase, 1);
    QEXTMemberFunctor1<int, MemberBase, int> intMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::intFunction1);
    QVERIFY(1 == intMemberBaseFunctor1_(&memberBase, 1));
    QEXTMemberFunctor1<double, MemberBase, double> doubleMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::doubleFunction1);
    QVERIFY(1.1 == doubleMemberBaseFunctor1_(&memberBase, 1.1));

    QEXTMemberFunctor1<void, MemberBase, bool> voidMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::voidFunctionB1);
    voidMemberBaseFunctorB1_(&memberBase, true);
    QEXTMemberFunctor1<int, MemberBase, bool> intMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::intFunctionB1);
    QVERIFY(1 == intMemberBaseFunctorB1_(&memberBase, true));
    QVERIFY(0 == intMemberBaseFunctorB1_(&memberBase, false));
    QEXTMemberFunctor1<double, MemberBase, bool> doubleMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleMemberBaseFunctorB1_(&memberBase, true));
    QVERIFY(0 == doubleMemberBaseFunctorB1_(&memberBase, false));

    QEXTMemberFunctor1<void, MemberBase, int> voidMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction1);
    voidMemberBaseFunctor1_obj(&memberBase, 1);
    QEXTMemberFunctor1<int, MemberBase, int> intMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction1);
    QVERIFY(1 == intMemberBaseFunctor1_obj(&memberBase, 1));
    QEXTMemberFunctor1<double, MemberBase, double> doubleMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction1);
    QVERIFY(1.1 == doubleMemberBaseFunctor1_obj(&memberBase, 1.1));

    QEXTMemberFunctor1<void, MemberBase, bool> voidMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB1);
    voidMemberBaseFunctorB1_obj(&memberBase, 1);
    QEXTMemberFunctor1<int, MemberBase, bool> intMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB1);
    QVERIFY(1 == intMemberBaseFunctorB1_obj(&memberBase, true));
    QVERIFY(0 == intMemberBaseFunctorB1_obj(&memberBase, false));
    QEXTMemberFunctor1<double, MemberBase, bool> doubleMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleMemberBaseFunctorB1_obj(&memberBase, true));
    QVERIFY(0 == doubleMemberBaseFunctorB1_obj(&memberBase, false));

    QEXTMemberFunctor1<void, MemberBase, int> voidMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::voidFunction1);
    voidMemberBaseFunctor1(&memberBase, 1);
    QEXTMemberFunctor1<int, MemberBase, int> intMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::intFunction1);
    QVERIFY(1 == intMemberBaseFunctor1(&memberBase, 1));
    QEXTMemberFunctor1<double, MemberBase, double> doubleMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::doubleFunction1);
    QVERIFY(1.1 == doubleMemberBaseFunctor1(&memberBase, 1.1));

    QEXTMemberFunctor1<void, MemberBase, bool> voidMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::voidFunctionB1);
    voidMemberBaseFunctorB1(&memberBase, 1);
    QEXTMemberFunctor1<int, MemberBase, bool> intMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::intFunctionB1);
    QVERIFY(1 == intMemberBaseFunctorB1(&memberBase, true));
    QVERIFY(0 == intMemberBaseFunctorB1(&memberBase, false));
    QEXTMemberFunctor1<double, MemberBase, bool> doubleMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleMemberBaseFunctorB1(&memberBase, true));
    QVERIFY(0 == doubleMemberBaseFunctorB1(&memberBase, false));

    QEXTMemberFunctor<void, MemberBase, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction1);
    voidMemberBaseFunctor(&memberBase, 1);
    QEXTMemberFunctor<int, MemberBase, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction1);
    QVERIFY(1 == intMemberBaseFunctor(&memberBase, 1));
    QEXTMemberFunctor<double, MemberBase, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction1);
    QVERIFY(1.1 == doubleMemberBaseFunctor(&memberBase, 1.1));

    QEXTMemberFunctor<void, MemberBase, bool> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB1);
    voidMemberBaseFunctorB(&memberBase, 1);
    QEXTMemberFunctor<int, MemberBase, bool> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB1);
    QVERIFY(1 == intMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == intMemberBaseFunctorB(&memberBase, false));
    QEXTMemberFunctor<double, MemberBase, bool> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == doubleMemberBaseFunctorB(&memberBase, false));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith1Arg()
{
    Member member;

    QEXTMemberFunctor1<void, MemberBase, int> voidMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::voidFunction1);
    voidMemberBaseFunctor1_(&member, 1);
    QEXTMemberFunctor1<int, MemberBase, int> intMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::intFunction1);
    QVERIFY(0 == intMemberBaseFunctor1_(&member, 1));
    QEXTMemberFunctor1<double, MemberBase, double> doubleMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::doubleFunction1);
    QVERIFY(0 == doubleMemberBaseFunctor1_(&member, 1.1));

    QEXTMemberFunctor1<void, MemberBase, bool> voidMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::voidFunctionB1);
    voidMemberBaseFunctorB1_(&member, true);
    QEXTMemberFunctor1<int, MemberBase, bool> intMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::intFunctionB1);
    QVERIFY(1 == intMemberBaseFunctorB1_(&member, true));
    QVERIFY(0 == intMemberBaseFunctorB1_(&member, false));
    QEXTMemberFunctor1<double, MemberBase, bool> doubleMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleMemberBaseFunctorB1_(&member, true));
    QVERIFY(0 == doubleMemberBaseFunctorB1_(&member, false));

    QEXTMemberFunctor1<void, MemberBase, int> voidMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction1);
    voidMemberBaseFunctor1_obj(&member, 1);
    QEXTMemberFunctor1<int, MemberBase, int> intMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction1);
    intMemberBaseFunctor1_obj(&member, 1);
    QVERIFY(0 == intMemberBaseFunctor1_obj(&member, 1));
    QEXTMemberFunctor1<double, MemberBase, double> doubleMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction1);
    QVERIFY(0 == doubleMemberBaseFunctor1_obj(&member, 1.1));

    QEXTMemberFunctor1<void, MemberBase, bool> voidMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB1);
    voidMemberBaseFunctorB1_obj(&member, 1);
    QEXTMemberFunctor1<int, MemberBase, bool> intMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB1);
    QVERIFY(1 == intMemberBaseFunctorB1_obj(&member, true));
    QVERIFY(0 == intMemberBaseFunctorB1_obj(&member, false));
    QEXTMemberFunctor1<double, MemberBase, bool> doubleMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleMemberBaseFunctorB1_obj(&member, true));
    QVERIFY(0 == doubleMemberBaseFunctorB1_obj(&member, false));

    QEXTMemberFunctor1<void, MemberBase, int> voidMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::voidFunction1);
    voidMemberBaseFunctor1(&member, 1);
    QEXTMemberFunctor1<int, MemberBase, int> intMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::intFunction1);
    QVERIFY(0 == intMemberBaseFunctor1(&member, 1));
    QEXTMemberFunctor1<double, MemberBase, double> doubleMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::doubleFunction1);
    QVERIFY(0 == doubleMemberBaseFunctor1(&member, 1.1));

    QEXTMemberFunctor1<void, MemberBase, bool> voidMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::voidFunctionB1);
    voidMemberBaseFunctorB1(&member, 1);
    QEXTMemberFunctor1<int, MemberBase, bool> intMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::intFunctionB1);
    QVERIFY(1 == intMemberBaseFunctorB1(&member, true));
    QVERIFY(0 == intMemberBaseFunctorB1(&member, false));
    QEXTMemberFunctor1<double, MemberBase, bool> doubleMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleMemberBaseFunctorB1(&member, true));
    QVERIFY(0 == doubleMemberBaseFunctorB1(&member, false));

    QEXTMemberFunctor<void, MemberBase, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction1);
    voidMemberBaseFunctor(&member, 1);
    QEXTMemberFunctor<int, MemberBase, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction1);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1));
    QEXTMemberFunctor<double, MemberBase, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction1);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1));

    QEXTMemberFunctor<void, MemberBase, bool> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB1);
    voidMemberBaseFunctorB(&member, 1);
    QEXTMemberFunctor<int, MemberBase, bool> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB1);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false));
    QEXTMemberFunctor<double, MemberBase, bool> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false));
}

void QEXTMemberFunctorTest::testConstFunctorWith1Arg()
{
    MemberBase memberBase;

    QEXTConstMemberFunctor1<void, MemberBase, int> voidConstMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::voidConstFunction1);
    voidConstMemberBaseFunctor1_(&memberBase, 1);
    QEXTConstMemberFunctor1<int, MemberBase, int> intConstMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::intConstFunction1);
    QVERIFY(1 == intConstMemberBaseFunctor1_(&memberBase, 1));
    QEXTConstMemberFunctor1<double, MemberBase, double> doubleConstMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::doubleConstFunction1);
    QVERIFY(1.1 == doubleConstMemberBaseFunctor1_(&memberBase, 1.1));

    QEXTConstMemberFunctor1<void, MemberBase, bool> voidConstMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::voidConstFunctionB1);
    voidConstMemberBaseFunctorB1_(&memberBase, true);
    QEXTConstMemberFunctor1<int, MemberBase, bool> intConstMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::intConstFunctionB1);
    QVERIFY(1 == intConstMemberBaseFunctorB1_(&memberBase, true));
    QVERIFY(0 == intConstMemberBaseFunctorB1_(&memberBase, false));
    QEXTConstMemberFunctor1<double, MemberBase, bool> doubleConstMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleConstMemberBaseFunctorB1_(&memberBase, true));
    QVERIFY(0 == doubleConstMemberBaseFunctorB1_(&memberBase, false));

    QEXTConstMemberFunctor1<void, MemberBase, int> voidConstMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction1);
    voidConstMemberBaseFunctor1_obj(&memberBase, 1);
    QEXTConstMemberFunctor1<int, MemberBase, int> intConstMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction1);
    intConstMemberBaseFunctor1_obj(&memberBase, 1);
    QVERIFY(1 == intConstMemberBaseFunctor1_obj(&memberBase, 1));
    QEXTConstMemberFunctor1<double, MemberBase, double> doubleConstMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction1);
    QVERIFY(1.1 == doubleConstMemberBaseFunctor1_obj(&memberBase, 1.1));

    QEXTConstMemberFunctor1<void, MemberBase, bool> voidConstMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB1);
    voidConstMemberBaseFunctorB1_obj(&memberBase, 1);
    QEXTConstMemberFunctor1<int, MemberBase, bool> intConstMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intConstMemberBaseFunctorB1_obj(&memberBase, true));
    QVERIFY(0 == intConstMemberBaseFunctorB1_obj(&memberBase, false));
    QEXTConstMemberFunctor1<double, MemberBase, bool> doubleConstMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleConstMemberBaseFunctorB1_obj(&memberBase, true));
    QVERIFY(0 == doubleConstMemberBaseFunctorB1_obj(&memberBase, false));

    QEXTConstMemberFunctor1<void, MemberBase, int> voidConstMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::voidConstFunction1);
    voidConstMemberBaseFunctor1(&memberBase, 1);
    QEXTConstMemberFunctor1<int, MemberBase, int> intConstMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::intConstFunction1);
    QVERIFY(1 == intConstMemberBaseFunctor1(&memberBase, 1));
    QEXTConstMemberFunctor1<double, MemberBase, double> doubleConstMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::doubleConstFunction1);
    QVERIFY(1.1 == doubleConstMemberBaseFunctor1(&memberBase, 1.1));

    QEXTConstMemberFunctor1<void, MemberBase, bool> voidConstMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::voidConstFunctionB1);
    voidConstMemberBaseFunctorB1(&memberBase, 1);
    QEXTConstMemberFunctor1<int, MemberBase, bool> intConstMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::intConstFunctionB1);
    QVERIFY(1 == intConstMemberBaseFunctorB1(&memberBase, true));
    QVERIFY(0 == intConstMemberBaseFunctorB1(&memberBase, false));
    QEXTConstMemberFunctor1<double, MemberBase, bool> doubleConstMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleConstMemberBaseFunctorB1(&memberBase, true));
    QVERIFY(0 == doubleConstMemberBaseFunctorB1(&memberBase, false));

    QEXTConstMemberFunctor<void, MemberBase, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction1);
    voidConstMemberBaseFunctor(&memberBase, 1);
    QEXTConstMemberFunctor<int, MemberBase, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction1);
    QVERIFY(1 == intConstMemberBaseFunctor(&memberBase, 1));
    QEXTConstMemberFunctor<double, MemberBase, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction1);
    QVERIFY(1.1 == doubleConstMemberBaseFunctor(&memberBase, 1.1));

    QEXTConstMemberFunctor<void, MemberBase, bool> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB1);
    voidConstMemberBaseFunctorB(&memberBase, 1);
    QEXTConstMemberFunctor<int, MemberBase, bool> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB1);
    QVERIFY(1 == intConstMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == intConstMemberBaseFunctorB(&memberBase, false));
    QEXTConstMemberFunctor<double, MemberBase, bool> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&memberBase, false));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith1Arg()
{
    Member member;

    QEXTConstMemberFunctor1<void, MemberBase, int> voidConstMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::voidConstFunction1);
    voidConstMemberBaseFunctor1_(&member, 1);
    QEXTConstMemberFunctor1<int, MemberBase, int> intConstMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::intConstFunction1);
    QVERIFY(0 == intConstMemberBaseFunctor1_(&member, 1));
    QEXTConstMemberFunctor1<double, MemberBase, double> doubleConstMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::doubleConstFunction1);
    QVERIFY(0 == doubleConstMemberBaseFunctor1_(&member, 1.1));

    QEXTConstMemberFunctor1<void, MemberBase, bool> voidConstMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::voidConstFunctionB1);
    voidConstMemberBaseFunctorB1_(&member, true);
    QEXTConstMemberFunctor1<int, MemberBase, bool> intConstMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::intConstFunctionB1);
    QVERIFY(1 == intConstMemberBaseFunctorB1_(&member, true));
    QVERIFY(0 == intConstMemberBaseFunctorB1_(&member, false));
    QEXTConstMemberFunctor1<double, MemberBase, bool> doubleConstMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleConstMemberBaseFunctorB1_(&member, true));
    QVERIFY(0 == doubleConstMemberBaseFunctorB1_(&member, false));

    QEXTConstMemberFunctor1<void, MemberBase, int> voidConstMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction1);
    voidConstMemberBaseFunctor1_obj(&member, 1);
    QEXTConstMemberFunctor1<int, MemberBase, int> intConstMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction1);
    intConstMemberBaseFunctor1_obj(&member, 1);
    QVERIFY(0 == intConstMemberBaseFunctor1_obj(&member, 1));
    QEXTConstMemberFunctor1<double, MemberBase, double> doubleConstMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction1);
    QVERIFY(0 == doubleConstMemberBaseFunctor1_obj(&member, 1.1));

    QEXTConstMemberFunctor1<void, MemberBase, bool> voidConstMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB1);
    voidConstMemberBaseFunctorB1_obj(&member, 1);
    QEXTConstMemberFunctor1<int, MemberBase, bool> intConstMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intConstMemberBaseFunctorB1_obj(&member, true));
    QVERIFY(0 == intConstMemberBaseFunctorB1_obj(&member, false));
    QEXTConstMemberFunctor1<double, MemberBase, bool> doubleConstMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleConstMemberBaseFunctorB1_obj(&member, true));
    QVERIFY(0 == doubleConstMemberBaseFunctorB1_obj(&member, false));

    QEXTConstMemberFunctor1<void, MemberBase, int> voidConstMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::voidConstFunction1);
    voidConstMemberBaseFunctor1(&member, 1);
    QEXTConstMemberFunctor1<int, MemberBase, int> intConstMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::intConstFunction1);
    QVERIFY(0 == intConstMemberBaseFunctor1(&member, 1));
    QEXTConstMemberFunctor1<double, MemberBase, double> doubleConstMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::doubleConstFunction1);
    QVERIFY(0 == doubleConstMemberBaseFunctor1(&member, 1.1));

    QEXTConstMemberFunctor1<void, MemberBase, bool> voidConstMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::voidConstFunctionB1);
    voidConstMemberBaseFunctorB1(&member, 1);
    QEXTConstMemberFunctor1<int, MemberBase, bool> intConstMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::intConstFunctionB1);
    QVERIFY(1 == intConstMemberBaseFunctorB1(&member, true));
    QVERIFY(0 == intConstMemberBaseFunctorB1(&member, false));
    QEXTConstMemberFunctor1<double, MemberBase, bool> doubleConstMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleConstMemberBaseFunctorB1(&member, true));
    QVERIFY(0 == doubleConstMemberBaseFunctorB1(&member, false));

    QEXTConstMemberFunctor<void, MemberBase, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction1);
    voidConstMemberBaseFunctor(&member, 1);
    QEXTConstMemberFunctor<int, MemberBase, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction1);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1));
    QEXTConstMemberFunctor<double, MemberBase, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction1);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1));

    QEXTConstMemberFunctor<void, MemberBase, bool> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB1);
    voidConstMemberBaseFunctorB(&member, 1);
    QEXTConstMemberFunctor<int, MemberBase, bool> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB1);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false));
    QEXTConstMemberFunctor<double, MemberBase, bool> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith1Arg()
{
    MemberBase memberBase;

    QEXTVolatileMemberFunctor1<void, MemberBase, int> voidVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::voidVolatileFunction1);
    voidVolatileMemberBaseFunctor1_(&memberBase, 1);
    QEXTVolatileMemberFunctor1<int, MemberBase, int> intVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::intVolatileFunction1);
    QVERIFY(1 == intVolatileMemberBaseFunctor1_(&memberBase, 1));
    QEXTVolatileMemberFunctor1<double, MemberBase, double> doubleVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction1);
    QVERIFY(1.1 == doubleVolatileMemberBaseFunctor1_(&memberBase, 1.1));

    QEXTVolatileMemberFunctor1<void, MemberBase, bool> voidVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB1);
    voidVolatileMemberBaseFunctorB1_(&memberBase, true);
    QEXTVolatileMemberFunctor1<int, MemberBase, bool> intVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intVolatileMemberBaseFunctorB1_(&memberBase, true));
    QVERIFY(0 == intVolatileMemberBaseFunctorB1_(&memberBase, false));
    QEXTVolatileMemberFunctor1<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB1_(&memberBase, true));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB1_(&memberBase, false));

    QEXTVolatileMemberFunctor1<void, MemberBase, int> voidVolatileMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction1);
    voidVolatileMemberBaseFunctor1_obj(&memberBase, 1);
    QEXTVolatileMemberFunctor1<int, MemberBase, int> intVolatileMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction1);
    intVolatileMemberBaseFunctor1_obj(&memberBase, 1);
    QVERIFY(1 == intVolatileMemberBaseFunctor1_obj(&memberBase, 1));
    QEXTVolatileMemberFunctor1<double, MemberBase, double> doubleVolatileMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction1);
    QVERIFY(1.1 == doubleVolatileMemberBaseFunctor1_obj(&memberBase, 1.1));

    QEXTVolatileMemberFunctor1<void, MemberBase, bool> voidVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB1);
    voidVolatileMemberBaseFunctorB1_obj(&memberBase, 1);
    QEXTVolatileMemberFunctor1<int, MemberBase, bool> intVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intVolatileMemberBaseFunctorB1_obj(&memberBase, true));
    QVERIFY(0 == intVolatileMemberBaseFunctorB1_obj(&memberBase, false));
    QEXTVolatileMemberFunctor1<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB1_obj(&memberBase, true));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB1_obj(&memberBase, false));

    QEXTVolatileMemberFunctor1<void, MemberBase, int> voidVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::voidVolatileFunction1);
    voidVolatileMemberBaseFunctor1(&memberBase, 1);
    QEXTVolatileMemberFunctor1<int, MemberBase, int> intVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::intVolatileFunction1);
    QVERIFY(1 == intVolatileMemberBaseFunctor1(&memberBase, 1));
    QEXTVolatileMemberFunctor1<double, MemberBase, double> doubleVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::doubleVolatileFunction1);
    QVERIFY(1.1 == doubleVolatileMemberBaseFunctor1(&memberBase, 1.1));

    QEXTVolatileMemberFunctor1<void, MemberBase, bool> voidVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::voidVolatileFunctionB1);
    voidVolatileMemberBaseFunctorB1(&memberBase, 1);
    QEXTVolatileMemberFunctor1<int, MemberBase, bool> intVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intVolatileMemberBaseFunctorB1(&memberBase, true));
    QVERIFY(0 == intVolatileMemberBaseFunctorB1(&memberBase, false));
    QEXTVolatileMemberFunctor1<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB1(&memberBase, true));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB1(&memberBase, false));

    QEXTVolatileMemberFunctor<void, MemberBase, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction1);
    voidVolatileMemberBaseFunctor(&memberBase, 1);
    QEXTVolatileMemberFunctor<int, MemberBase, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction1);
    QVERIFY(1 == intVolatileMemberBaseFunctor(&memberBase, 1));
    QEXTVolatileMemberFunctor<double, MemberBase, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction1);
    QVERIFY(1.1 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1));

    QEXTVolatileMemberFunctor<void, MemberBase, bool> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB1);
    voidVolatileMemberBaseFunctorB(&memberBase, 1);
    QEXTVolatileMemberFunctor<int, MemberBase, bool> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&memberBase, false));
    QEXTVolatileMemberFunctor<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&memberBase, false));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith1Arg()
{
    Member member;

    QEXTVolatileMemberFunctor1<void, MemberBase, int> voidVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::voidVolatileFunction1);
    voidVolatileMemberBaseFunctor1_(&member, 1);
    QEXTVolatileMemberFunctor1<int, MemberBase, int> intVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::intVolatileFunction1);
    QVERIFY(0 == intVolatileMemberBaseFunctor1_(&member, 1));
    QEXTVolatileMemberFunctor1<double, MemberBase, double> doubleVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction1);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor1_(&member, 1.1));

    QEXTVolatileMemberFunctor1<void, MemberBase, bool> voidVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB1);
    voidVolatileMemberBaseFunctorB1_(&member, true);
    QEXTVolatileMemberFunctor1<int, MemberBase, bool> intVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intVolatileMemberBaseFunctorB1_(&member, true));
    QVERIFY(0 == intVolatileMemberBaseFunctorB1_(&member, false));
    QEXTVolatileMemberFunctor1<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB1_(&member, true));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB1_(&member, false));

    QEXTVolatileMemberFunctor1<void, MemberBase, int> voidVolatileMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction1);
    voidVolatileMemberBaseFunctor1_obj(&member, 1);
    QEXTVolatileMemberFunctor1<int, MemberBase, int> intVolatileMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction1);
    intVolatileMemberBaseFunctor1_obj(&member, 1);
    QVERIFY(0 == intVolatileMemberBaseFunctor1_obj(&member, 1));
    QEXTVolatileMemberFunctor1<double, MemberBase, double> doubleVolatileMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction1);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor1_obj(&member, 1.1));

    QEXTVolatileMemberFunctor1<void, MemberBase, bool> voidVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB1);
    voidVolatileMemberBaseFunctorB1_obj(&member, 1);
    QEXTVolatileMemberFunctor1<int, MemberBase, bool> intVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intVolatileMemberBaseFunctorB1_obj(&member, true));
    QVERIFY(0 == intVolatileMemberBaseFunctorB1_obj(&member, false));
    QEXTVolatileMemberFunctor1<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB1_obj(&member, true));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB1_obj(&member, false));

    QEXTVolatileMemberFunctor1<void, MemberBase, int> voidVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::voidVolatileFunction1);
    voidVolatileMemberBaseFunctor1(&member, 1);
    QEXTVolatileMemberFunctor1<int, MemberBase, int> intVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::intVolatileFunction1);
    QVERIFY(0 == intVolatileMemberBaseFunctor1(&member, 1));
    QEXTVolatileMemberFunctor1<double, MemberBase, double> doubleVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::doubleVolatileFunction1);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor1(&member, 1.1));

    QEXTVolatileMemberFunctor1<void, MemberBase, bool> voidVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::voidVolatileFunctionB1);
    voidVolatileMemberBaseFunctorB1(&member, 1);
    QEXTVolatileMemberFunctor1<int, MemberBase, bool> intVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intVolatileMemberBaseFunctorB1(&member, true));
    QVERIFY(0 == intVolatileMemberBaseFunctorB1(&member, false));
    QEXTVolatileMemberFunctor1<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB1(&member, true));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB1(&member, false));

    QEXTVolatileMemberFunctor<void, MemberBase, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction1);
    voidVolatileMemberBaseFunctor(&member, 1);
    QEXTVolatileMemberFunctor<int, MemberBase, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction1);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1));
    QEXTVolatileMemberFunctor<double, MemberBase, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction1);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1));

    QEXTVolatileMemberFunctor<void, MemberBase, bool> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB1);
    voidVolatileMemberBaseFunctorB(&member, 1);
    QEXTVolatileMemberFunctor<int, MemberBase, bool> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false));
    QEXTVolatileMemberFunctor<double, MemberBase, bool> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith1Arg()
{
    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor1<void, MemberBase, int> voidConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction1);
    voidConstVolatileMemberBaseFunctor1_(&memberBase, 1);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, int> intConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctor1_(&memberBase, 1));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction1);
    QVERIFY(1.1 == doubleConstVolatileMemberBaseFunctor1_(&memberBase, 1.1));

    QEXTConstVolatileMemberFunctor1<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB1);
    voidConstVolatileMemberBaseFunctorB1_(&memberBase, true);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB1_(&memberBase, true));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB1_(&memberBase, false));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB1_(&memberBase, true));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB1_(&memberBase, false));

    QEXTConstVolatileMemberFunctor1<void, MemberBase, int> voidConstVolatileMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction1);
    voidConstVolatileMemberBaseFunctor1_obj(&memberBase, 1);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, int> intConstVolatileMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction1);
    intConstVolatileMemberBaseFunctor1_obj(&memberBase, 1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctor1_obj(&memberBase, 1));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor1_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(1.1 == doubleConstVolatileMemberBaseFunctor1_obj(&memberBase, 1.1));

    QEXTConstVolatileMemberFunctor1<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB1);
    voidConstVolatileMemberBaseFunctorB1_obj(&memberBase, 1);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB1_obj(&memberBase, true));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB1_obj(&memberBase, false));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB1_obj(&memberBase, true));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB1_obj(&memberBase, false));

    QEXTConstVolatileMemberFunctor1<void, MemberBase, int> voidConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::voidConstVolatileFunction1);
    voidConstVolatileMemberBaseFunctor1(&memberBase, 1);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, int> intConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::intConstVolatileFunction1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctor1(&memberBase, 1));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::doubleConstVolatileFunction1);
    QVERIFY(1.1 == doubleConstVolatileMemberBaseFunctor1(&memberBase, 1.1));

    QEXTConstVolatileMemberFunctor1<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::voidConstVolatileFunctionB1);
    voidConstVolatileMemberBaseFunctorB1(&memberBase, 1);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB1(&memberBase, true));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB1(&memberBase, false));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB1(&memberBase, true));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB1(&memberBase, false));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction1);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctor(&memberBase, 1));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction1);
    QVERIFY(1.1 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB1);
    voidConstVolatileMemberBaseFunctorB(&memberBase, 1);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&memberBase, false));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith1Arg()
{
    Member member;

    QEXTConstVolatileMemberFunctor1<void, MemberBase, int> voidConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction1);
    voidConstVolatileMemberBaseFunctor1_(&member, 1);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, int> intConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction1);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor1_(&member, 1));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction1);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor1_(&member, 1.1));

    QEXTConstVolatileMemberFunctor1<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB1);
    voidConstVolatileMemberBaseFunctorB1_(&member, true);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB1_(&member, true));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB1_(&member, false));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB1_(&member, true));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB1_(&member, false));

    QEXTConstVolatileMemberFunctor1<void, MemberBase, int> voidConstVolatileMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction1);
    voidConstVolatileMemberBaseFunctor1_obj(&member, 1);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, int> intConstVolatileMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction1);
    intConstVolatileMemberBaseFunctor1_obj(&member, 1);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor1_obj(&member, 1));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor1_obj(&member, 1.1));

    QEXTConstVolatileMemberFunctor1<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB1);
    voidConstVolatileMemberBaseFunctorB1_obj(&member, 1);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB1_obj(&member, true));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB1_obj(&member, false));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB1_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB1_obj(&member, true));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB1_obj(&member, false));

    QEXTConstVolatileMemberFunctor1<void, MemberBase, int> voidConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::voidConstVolatileFunction1);
    voidConstVolatileMemberBaseFunctor1(&member, 1);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, int> intConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::intConstVolatileFunction1);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor1(&member, 1));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(&MemberBase::doubleConstVolatileFunction1);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor1(&member, 1.1));

    QEXTConstVolatileMemberFunctor1<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::voidConstVolatileFunctionB1);
    voidConstVolatileMemberBaseFunctorB1(&member, 1);
    QEXTConstVolatileMemberFunctor1<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB1(&member, true));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB1(&member, false));
    QEXTConstVolatileMemberFunctor1<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB1(&member, true));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB1(&member, false));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction1);
    voidConstVolatileMemberBaseFunctor(&member, 1);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction1);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction1);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB1);
    voidConstVolatileMemberBaseFunctorB(&member, 1);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false));
}

void QEXTMemberFunctorTest::testBoundFunctorWith1Arg()
{
    MemberBase memberBase;

    QEXTBoundMemberFunctor1<void, MemberBase, int> voidBoundMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunction1);
    voidBoundMemberBaseFunctor1_(1);
    QEXTBoundMemberFunctor1<int, MemberBase, int> intBoundMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::intFunction1);
    QVERIFY(1 == intBoundMemberBaseFunctor1_(1));
    QEXTBoundMemberFunctor1<double, MemberBase, double> doubleBoundMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction1);
    QVERIFY(1.1 == doubleBoundMemberBaseFunctor1_(1.1));

    QEXTBoundMemberFunctor1<void, MemberBase, bool> voidBoundMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB1);
    voidBoundMemberBaseFunctorB1_(true);
    QEXTBoundMemberFunctor1<int, MemberBase, bool> intBoundMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB1);
    QVERIFY(1 == intBoundMemberBaseFunctorB1_(true));
    QVERIFY(0 == intBoundMemberBaseFunctorB1_(false));
    QEXTBoundMemberFunctor1<double, MemberBase, bool> doubleBoundMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB1_(true));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB1_(false));

    QEXTBoundMemberFunctor1<void, MemberBase, int> voidBoundMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::voidFunction1);
    voidBoundMemberBaseFunctor1(1);
    QEXTBoundMemberFunctor1<int, MemberBase, int> intBoundMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::intFunction1);
    QVERIFY(1 == intBoundMemberBaseFunctor1(1));
    QEXTBoundMemberFunctor1<double, MemberBase, double> doubleBoundMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::doubleFunction1);
    QVERIFY(1.1 == doubleBoundMemberBaseFunctor1(1.1));

    QEXTBoundMemberFunctor1<void, MemberBase, bool> voidBoundMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::voidFunctionB1);
    voidBoundMemberBaseFunctorB1(1);
    QEXTBoundMemberFunctor1<int, MemberBase, bool> intBoundMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::intFunctionB1);
    QVERIFY(1 == intBoundMemberBaseFunctorB1(true));
    QVERIFY(0 == intBoundMemberBaseFunctorB1(false));
    QEXTBoundMemberFunctor1<double, MemberBase, bool> doubleBoundMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB1(true));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB1(false));

    QEXTBoundMemberFunctor<void, MemberBase, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction1);
    voidBoundMemberBaseFunctor(1);
    QEXTBoundMemberFunctor<int, MemberBase, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction1);
    QVERIFY(1 == intBoundMemberBaseFunctor(1));
    QEXTBoundMemberFunctor<double, MemberBase, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction1);
    QVERIFY(1.1 == doubleBoundMemberBaseFunctor(1.1));

    QEXTBoundMemberFunctor<void, MemberBase, bool> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB1);
    voidBoundMemberBaseFunctorB(1);
    QEXTBoundMemberFunctor<int, MemberBase, bool> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB1);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false));
    QEXTBoundMemberFunctor<double, MemberBase, bool> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith1Arg()
{
    Member member;

    QEXTBoundMemberFunctor1<void, MemberBase, int> voidBoundMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction1);
    voidBoundMemberBaseFunctor1_(1);
    QEXTBoundMemberFunctor1<int, MemberBase, int> intBoundMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction1);
    QVERIFY(0 == intBoundMemberBaseFunctor1_(1));
    QEXTBoundMemberFunctor1<double, MemberBase, double> doubleBoundMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction1);
    QVERIFY(0 == doubleBoundMemberBaseFunctor1_(1.1));

    QEXTBoundMemberFunctor1<void, MemberBase, bool> voidBoundMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB1);
    voidBoundMemberBaseFunctorB1_(true);
    QEXTBoundMemberFunctor1<int, MemberBase, bool> intBoundMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB1);
    QVERIFY(1 == intBoundMemberBaseFunctorB1_(true));
    QVERIFY(0 == intBoundMemberBaseFunctorB1_(false));
    QEXTBoundMemberFunctor1<double, MemberBase, bool> doubleBoundMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB1_(true));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB1_(false));

    QEXTBoundMemberFunctor1<void, MemberBase, int> voidBoundMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction1);
    voidBoundMemberBaseFunctor1(1);
    QEXTBoundMemberFunctor1<int, MemberBase, int> intBoundMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction1);
    QVERIFY(0 == intBoundMemberBaseFunctor1(1));
    QEXTBoundMemberFunctor1<double, MemberBase, double> doubleBoundMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction1);
    QVERIFY(0 == doubleBoundMemberBaseFunctor1(1.1));

    QEXTBoundMemberFunctor1<void, MemberBase, bool> voidBoundMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB1);
    voidBoundMemberBaseFunctorB1(1);
    QEXTBoundMemberFunctor1<int, MemberBase, bool> intBoundMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB1);
    QVERIFY(1 == intBoundMemberBaseFunctorB1(true));
    QVERIFY(0 == intBoundMemberBaseFunctorB1(false));
    QEXTBoundMemberFunctor1<double, MemberBase, bool> doubleBoundMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB1(true));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB1(false));

    QEXTBoundMemberFunctor<void, MemberBase, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction1);
    voidBoundMemberBaseFunctor(1);
    QEXTBoundMemberFunctor<int, MemberBase, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction1);
    QVERIFY(0 == intBoundMemberBaseFunctor(1));
    QEXTBoundMemberFunctor<double, MemberBase, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction1);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1));

    QEXTBoundMemberFunctor<void, MemberBase, bool> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB1);
    voidBoundMemberBaseFunctorB(1);
    QEXTBoundMemberFunctor<int, MemberBase, bool> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB1);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false));
    QEXTBoundMemberFunctor<double, MemberBase, bool> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB1);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith1Arg()
{
    MemberBase memberBase;

    QEXTBoundConstMemberFunctor1<void, MemberBase, int> voidBoundConstMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction1);
    voidBoundConstMemberBaseFunctor1_(1);
    QEXTBoundConstMemberFunctor1<int, MemberBase, int> intBoundConstMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction1);
    QVERIFY(1 == intBoundConstMemberBaseFunctor1_(1));
    QEXTBoundConstMemberFunctor1<double, MemberBase, double> doubleBoundConstMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction1);
    QVERIFY(1.1 == doubleBoundConstMemberBaseFunctor1_(1.1));

    QEXTBoundConstMemberFunctor1<void, MemberBase, bool> voidBoundConstMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB1);
    voidBoundConstMemberBaseFunctorB1_(true);
    QEXTBoundConstMemberFunctor1<int, MemberBase, bool> intBoundConstMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB1_(true));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB1_(false));
    QEXTBoundConstMemberFunctor1<double, MemberBase, bool> doubleBoundConstMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB1_(true));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB1_(false));

    QEXTBoundConstMemberFunctor1<void, MemberBase, int> voidBoundConstMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::voidConstFunction1);
    voidBoundConstMemberBaseFunctor1(1);
    QEXTBoundConstMemberFunctor1<int, MemberBase, int> intBoundConstMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::intConstFunction1);
    QVERIFY(1 == intBoundConstMemberBaseFunctor1(1));
    QEXTBoundConstMemberFunctor1<double, MemberBase, double> doubleBoundConstMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::doubleConstFunction1);
    QVERIFY(1.1 == doubleBoundConstMemberBaseFunctor1(1.1));

    QEXTBoundConstMemberFunctor1<void, MemberBase, bool> voidBoundConstMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::voidConstFunctionB1);
    voidBoundConstMemberBaseFunctorB1(1);
    QEXTBoundConstMemberFunctor1<int, MemberBase, bool> intBoundConstMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB1(true));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB1(false));
    QEXTBoundConstMemberFunctor1<double, MemberBase, bool> doubleBoundConstMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB1(true));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB1(false));

    QEXTBoundConstMemberFunctor<void, MemberBase, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction1);
    voidBoundConstMemberBaseFunctor(1);
    QEXTBoundConstMemberFunctor<int, MemberBase, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction1);
    QVERIFY(1 == intBoundConstMemberBaseFunctor(1));
    QEXTBoundConstMemberFunctor<double, MemberBase, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction1);
    QVERIFY(1.1 == doubleBoundConstMemberBaseFunctor(1.1));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB1);
    voidBoundConstMemberBaseFunctorB(1);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith1Arg()
{
    Member member;

    QEXTBoundConstMemberFunctor1<void, MemberBase, int> voidBoundConstMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction1);
    voidBoundConstMemberBaseFunctor1_(1);
    QEXTBoundConstMemberFunctor1<int, MemberBase, int> intBoundConstMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction1);
    QVERIFY(0 == intBoundConstMemberBaseFunctor1_(1));
    QEXTBoundConstMemberFunctor1<double, MemberBase, double> doubleBoundConstMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction1);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor1_(1.1));

    QEXTBoundConstMemberFunctor1<void, MemberBase, bool> voidBoundConstMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB1);
    voidBoundConstMemberBaseFunctorB1_(true);
    QEXTBoundConstMemberFunctor1<int, MemberBase, bool> intBoundConstMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB1_(true));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB1_(false));
    QEXTBoundConstMemberFunctor1<double, MemberBase, bool> doubleBoundConstMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB1_(true));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB1_(false));

    QEXTBoundConstMemberFunctor1<void, MemberBase, int> voidBoundConstMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction1);
    voidBoundConstMemberBaseFunctor1(1);
    QEXTBoundConstMemberFunctor1<int, MemberBase, int> intBoundConstMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction1);
    QVERIFY(0 == intBoundConstMemberBaseFunctor1(1));
    QEXTBoundConstMemberFunctor1<double, MemberBase, double> doubleBoundConstMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction1);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor1(1.1));

    QEXTBoundConstMemberFunctor1<void, MemberBase, bool> voidBoundConstMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB1);
    voidBoundConstMemberBaseFunctorB1(1);
    QEXTBoundConstMemberFunctor1<int, MemberBase, bool> intBoundConstMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB1(true));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB1(false));
    QEXTBoundConstMemberFunctor1<double, MemberBase, bool> doubleBoundConstMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB1(true));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB1(false));

    QEXTBoundConstMemberFunctor<void, MemberBase, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction1);
    voidBoundConstMemberBaseFunctor(1);
    QEXTBoundConstMemberFunctor<int, MemberBase, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction1);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1));
    QEXTBoundConstMemberFunctor<double, MemberBase, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction1);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB1);
    voidBoundConstMemberBaseFunctorB(1);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB1);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB1);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith1Arg()
{
    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor1<void, MemberBase, int> voidBoundVolatileMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction1);
    voidBoundVolatileMemberBaseFunctor1_(1);
    QEXTBoundVolatileMemberFunctor1<int, MemberBase, int> intBoundVolatileMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctor1_(1));
    QEXTBoundVolatileMemberFunctor1<double, MemberBase, double> doubleBoundVolatileMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction1);
    QVERIFY(1.1 == doubleBoundVolatileMemberBaseFunctor1_(1.1));

    QEXTBoundVolatileMemberFunctor1<void, MemberBase, bool> voidBoundVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB1);
    voidBoundVolatileMemberBaseFunctorB1_(true);
    QEXTBoundVolatileMemberFunctor1<int, MemberBase, bool> intBoundVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB1_(true));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB1_(false));
    QEXTBoundVolatileMemberFunctor1<double, MemberBase, bool> doubleBoundVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB1_(true));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB1_(false));

    QEXTBoundVolatileMemberFunctor1<void, MemberBase, int> voidBoundVolatileMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::voidVolatileFunction1);
    voidBoundVolatileMemberBaseFunctor1(1);
    QEXTBoundVolatileMemberFunctor1<int, MemberBase, int> intBoundVolatileMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::intVolatileFunction1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctor1(1));
    QEXTBoundVolatileMemberFunctor1<double, MemberBase, double> doubleBoundVolatileMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::doubleVolatileFunction1);
    QVERIFY(1.1 == doubleBoundVolatileMemberBaseFunctor1(1.1));

    QEXTBoundVolatileMemberFunctor1<void, MemberBase, bool> voidBoundVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::voidVolatileFunctionB1);
    voidBoundVolatileMemberBaseFunctorB1(1);
    QEXTBoundVolatileMemberFunctor1<int, MemberBase, bool> intBoundVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB1(true));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB1(false));
    QEXTBoundVolatileMemberFunctor1<double, MemberBase, bool> doubleBoundVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB1(true));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB1(false));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction1);
    voidBoundVolatileMemberBaseFunctor(1);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctor(1));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction1);
    QVERIFY(1.1 == doubleBoundVolatileMemberBaseFunctor(1.1));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB1);
    voidBoundVolatileMemberBaseFunctorB(1);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith1Arg()
{
    Member member;

    QEXTBoundVolatileMemberFunctor1<void, MemberBase, int> voidBoundVolatileMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction1);
    voidBoundVolatileMemberBaseFunctor1_(1);
    QEXTBoundVolatileMemberFunctor1<int, MemberBase, int> intBoundVolatileMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction1);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor1_(1));
    QEXTBoundVolatileMemberFunctor1<double, MemberBase, double> doubleBoundVolatileMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction1);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor1_(1.1));

    QEXTBoundVolatileMemberFunctor1<void, MemberBase, bool> voidBoundVolatileMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB1);
    voidBoundVolatileMemberBaseFunctorB1_(true);
    QEXTBoundVolatileMemberFunctor1<int, MemberBase, bool> intBoundVolatileMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB1_(true));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB1_(false));
    QEXTBoundVolatileMemberFunctor1<double, MemberBase, bool> doubleBoundVolatileMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB1_(true));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB1_(false));

    QEXTBoundVolatileMemberFunctor1<void, MemberBase, int> voidBoundVolatileMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction1);
    voidBoundVolatileMemberBaseFunctor1(1);
    QEXTBoundVolatileMemberFunctor1<int, MemberBase, int> intBoundVolatileMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction1);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor1(1));
    QEXTBoundVolatileMemberFunctor1<double, MemberBase, double> doubleBoundVolatileMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction1);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor1(1.1));

    QEXTBoundVolatileMemberFunctor1<void, MemberBase, bool> voidBoundVolatileMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB1);
    voidBoundVolatileMemberBaseFunctorB1(1);
    QEXTBoundVolatileMemberFunctor1<int, MemberBase, bool> intBoundVolatileMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB1(true));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB1(false));
    QEXTBoundVolatileMemberFunctor1<double, MemberBase, bool> doubleBoundVolatileMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB1(true));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB1(false));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction1);
    voidBoundVolatileMemberBaseFunctor(1);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction1);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction1);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB1);
    voidBoundVolatileMemberBaseFunctorB(1);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB1);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB1);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith1Arg()
{
    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor1<void, MemberBase, int> voidBoundConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction1);
    voidBoundConstVolatileMemberBaseFunctor1_(1);
    QEXTBoundConstVolatileMemberFunctor1<int, MemberBase, int> intBoundConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctor1_(1));
    QEXTBoundConstVolatileMemberFunctor1<double, MemberBase, double> doubleBoundConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(1.1 == doubleBoundConstVolatileMemberBaseFunctor1_(1.1));

    QEXTBoundConstVolatileMemberFunctor1<void, MemberBase, bool> voidBoundConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB1);
    voidBoundConstVolatileMemberBaseFunctorB1_(true);
    QEXTBoundConstVolatileMemberFunctor1<int, MemberBase, bool> intBoundConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB1_(true));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB1_(false));
    QEXTBoundConstVolatileMemberFunctor1<double, MemberBase, bool> doubleBoundConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB1_(true));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB1_(false));

    QEXTBoundConstVolatileMemberFunctor1<void, MemberBase, int> voidBoundConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::voidConstVolatileFunction1);
    voidBoundConstVolatileMemberBaseFunctor1(1);
    QEXTBoundConstVolatileMemberFunctor1<int, MemberBase, int> intBoundConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::intConstVolatileFunction1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctor1(1));
    QEXTBoundConstVolatileMemberFunctor1<double, MemberBase, double> doubleBoundConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(&memberBase, &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(1.1 == doubleBoundConstVolatileMemberBaseFunctor1(1.1));

    QEXTBoundConstVolatileMemberFunctor1<void, MemberBase, bool> voidBoundConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::voidConstVolatileFunctionB1);
    voidBoundConstVolatileMemberBaseFunctorB1(1);
    QEXTBoundConstVolatileMemberFunctor1<int, MemberBase, bool> intBoundConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB1(true));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB1(false));
    QEXTBoundConstVolatileMemberFunctor1<double, MemberBase, bool> doubleBoundConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(&memberBase, &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB1(true));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB1(false));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction1);
    voidBoundConstVolatileMemberBaseFunctor(1);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctor(1));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(1.1 == doubleBoundConstVolatileMemberBaseFunctor(1.1));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB1);
    voidBoundConstVolatileMemberBaseFunctorB(1);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith1Arg()
{
    Member member;

    QEXTBoundConstVolatileMemberFunctor1<void, MemberBase, int> voidBoundConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction1);
    voidBoundConstVolatileMemberBaseFunctor1_(1);
    QEXTBoundConstVolatileMemberFunctor1<int, MemberBase, int> intBoundConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction1);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor1_(1));
    QEXTBoundConstVolatileMemberFunctor1<double, MemberBase, double> doubleBoundConstVolatileMemberBaseFunctor1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor1_(1.1));

    QEXTBoundConstVolatileMemberFunctor1<void, MemberBase, bool> voidBoundConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB1);
    voidBoundConstVolatileMemberBaseFunctorB1_(true);
    QEXTBoundConstVolatileMemberFunctor1<int, MemberBase, bool> intBoundConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB1_(true));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB1_(false));
    QEXTBoundConstVolatileMemberFunctor1<double, MemberBase, bool> doubleBoundConstVolatileMemberBaseFunctorB1_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB1_(true));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB1_(false));

    QEXTBoundConstVolatileMemberFunctor1<void, MemberBase, int> voidBoundConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction1);
    voidBoundConstVolatileMemberBaseFunctor1(1);
    QEXTBoundConstVolatileMemberFunctor1<int, MemberBase, int> intBoundConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction1);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor1(1));
    QEXTBoundConstVolatileMemberFunctor1<double, MemberBase, double> doubleBoundConstVolatileMemberBaseFunctor1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor1(1.1));

    QEXTBoundConstVolatileMemberFunctor1<void, MemberBase, bool> voidBoundConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB1);
    voidBoundConstVolatileMemberBaseFunctorB1(1);
    QEXTBoundConstVolatileMemberFunctor1<int, MemberBase, bool> intBoundConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB1(true));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB1(false));
    QEXTBoundConstVolatileMemberFunctor1<double, MemberBase, bool> doubleBoundConstVolatileMemberBaseFunctorB1 = qextMemberFunctor1(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB1(true));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB1(false));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction1);
    voidBoundConstVolatileMemberBaseFunctor(1);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction1);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction1);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB1);
    voidBoundConstVolatileMemberBaseFunctorB(1);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB1);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB1);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false));
}

void QEXTMemberFunctorTest::testFunctorWith2Arg()
{
    MemberBase memberBase;

    QEXTMemberFunctor2<void, MemberBase, int, int> voidMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::voidFunction2);
    voidMemberBaseFunctor2_(&memberBase, 1, 2);
    QEXTMemberFunctor2<int, MemberBase, int, int> intMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::intFunction2);
    QVERIFY(1 + 2 == intMemberBaseFunctor2_(&memberBase, 1, 2));
    QEXTMemberFunctor2<double, MemberBase, double, double> doubleMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleMemberBaseFunctor2_(&memberBase, 1.1, 2.2));

    QEXTMemberFunctor2<void, MemberBase, bool, int> voidMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::voidFunctionB2);
    voidMemberBaseFunctorB2_(&memberBase, true, 2);
    QEXTMemberFunctor2<int, MemberBase, bool, int> intMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::intFunctionB2);
    QVERIFY(2 == intMemberBaseFunctorB2_(&memberBase, true, 2));
    QVERIFY(0 == intMemberBaseFunctorB2_(&memberBase, false, 2));
    QEXTMemberFunctor2<double, MemberBase, bool, double> doubleMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleMemberBaseFunctorB2_(&memberBase, true, 2.2));
    QVERIFY(0 == doubleMemberBaseFunctorB2_(&memberBase, false, 2.2));

    QEXTMemberFunctor2<void, MemberBase, int, int> voidMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction2);
    voidMemberBaseFunctor2_obj(&memberBase, 1, 2);
    QEXTMemberFunctor2<int, MemberBase, int, int> intMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction2);
    QVERIFY(1 + 2 == intMemberBaseFunctor2_obj(&memberBase, 1, 2));
    QEXTMemberFunctor2<double, MemberBase, double, double> doubleMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleMemberBaseFunctor2_obj(&memberBase, 1.1, 2.2));

    QEXTMemberFunctor2<void, MemberBase, bool, int> voidMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB2);
    voidMemberBaseFunctorB2_obj(&memberBase, true, 2);
    QEXTMemberFunctor2<int, MemberBase, bool, int> intMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB2);
    QVERIFY(2 == intMemberBaseFunctorB2_obj(&memberBase, true, 2));
    QVERIFY(0 == intMemberBaseFunctorB2_obj(&memberBase, false, 2));
    QEXTMemberFunctor2<double, MemberBase, bool, double> doubleMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleMemberBaseFunctorB2_obj(&memberBase, true, 2.2));
    QVERIFY(0 == doubleMemberBaseFunctorB2_obj(&memberBase, false, 2.2));

    QEXTMemberFunctor2<void, MemberBase, int, int> voidMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::voidFunction2);
    voidMemberBaseFunctor2(&memberBase, 1, 2);
    QEXTMemberFunctor2<int, MemberBase, int, int> intMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::intFunction2);
    QVERIFY(1 + 2 == intMemberBaseFunctor2(&memberBase, 1, 2));
    QEXTMemberFunctor2<double, MemberBase, double, double> doubleMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleMemberBaseFunctor2(&memberBase, 1.1, 2.2));

    QEXTMemberFunctor2<void, MemberBase, bool, int> voidMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::voidFunctionB2);
    voidMemberBaseFunctorB2(&memberBase, true, 2);
    QEXTMemberFunctor2<int, MemberBase, bool, int> intMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::intFunctionB2);
    QVERIFY(2 == intMemberBaseFunctorB2(&memberBase, true, 2));
    QVERIFY(0 == intMemberBaseFunctorB2(&memberBase, false, 2));
    QEXTMemberFunctor2<double, MemberBase, bool, double> doubleMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleMemberBaseFunctorB2(&memberBase, true, 2.2));
    QVERIFY(0 == doubleMemberBaseFunctorB2(&memberBase, false, 2.2));

    QEXTMemberFunctor<void, MemberBase, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction2);
    voidMemberBaseFunctor(&memberBase, 1, 2);
    QEXTMemberFunctor<int, MemberBase, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction2);
    QVERIFY(1 + 2 == intMemberBaseFunctor(&memberBase, 1, 2));
    QEXTMemberFunctor<double, MemberBase, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2));

    QEXTMemberFunctor<void, MemberBase, bool, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB2);
    voidMemberBaseFunctorB(&memberBase, true, 2);
    QEXTMemberFunctor<int, MemberBase, bool, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB2);
    QVERIFY(2 == intMemberBaseFunctorB(&memberBase, true, 2));
    QVERIFY(0 == intMemberBaseFunctorB(&memberBase, false, 2));
    QEXTMemberFunctor<double, MemberBase, bool, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleMemberBaseFunctorB(&memberBase, true, 2.2));
    QVERIFY(0 == doubleMemberBaseFunctorB(&memberBase, false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith2Arg()
{
    Member member;

    QEXTMemberFunctor2<void, MemberBase, int, int> voidMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::voidFunction2);
    voidMemberBaseFunctor2_(&member, 1, 2);
    QEXTMemberFunctor2<int, MemberBase, int, int> intMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::intFunction2);
    QVERIFY(0 == intMemberBaseFunctor2_(&member, 1, 2));
    QEXTMemberFunctor2<double, MemberBase, double, double> doubleMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::doubleFunction2);
    QVERIFY(0 == doubleMemberBaseFunctor2_(&member, 1.1, 2.2));

    QEXTMemberFunctor2<void, MemberBase, bool, int> voidMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::voidFunctionB2);
    voidMemberBaseFunctorB2_(&member, true, 2);
    QEXTMemberFunctor2<int, MemberBase, bool, int> intMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::intFunctionB2);
    QVERIFY(1 == intMemberBaseFunctorB2_(&member, true, 2));
    QVERIFY(0 == intMemberBaseFunctorB2_(&member, false, 2));
    QEXTMemberFunctor2<double, MemberBase, bool, double> doubleMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleMemberBaseFunctorB2_(&member, true, 2.2));
    QVERIFY(0 == doubleMemberBaseFunctorB2_(&member, false, 2.2));

    QEXTMemberFunctor2<void, MemberBase, int, int> voidMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction2);
    voidMemberBaseFunctor2_obj(&member, 1, 2);
    QEXTMemberFunctor2<int, MemberBase, int, int> intMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction2);
    intMemberBaseFunctor2_obj(&member, 1, 2);
    QVERIFY(0 == intMemberBaseFunctor2_obj(&member, 1, 2));
    QEXTMemberFunctor2<double, MemberBase, double, double> doubleMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction2);
    QVERIFY(0 == doubleMemberBaseFunctor2_obj(&member, 1.1, 2.2));

    QEXTMemberFunctor2<void, MemberBase, bool, int> voidMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB2);
    voidMemberBaseFunctorB2_obj(&member, true, 2);
    QEXTMemberFunctor2<int, MemberBase, bool, int> intMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB2);
    QVERIFY(1 == intMemberBaseFunctorB2_obj(&member, true, 2));
    QVERIFY(0 == intMemberBaseFunctorB2_obj(&member, false, 2));
    QEXTMemberFunctor2<double, MemberBase, bool, double> doubleMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleMemberBaseFunctorB2_obj(&member, true, 2.2));
    QVERIFY(0 == doubleMemberBaseFunctorB2_obj(&member, false, 2.2));

    QEXTMemberFunctor2<void, MemberBase, int, int> voidMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::voidFunction2);
    voidMemberBaseFunctor2(&member, 1, 2);
    QEXTMemberFunctor2<int, MemberBase, int, int> intMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::intFunction2);
    QVERIFY(0 == intMemberBaseFunctor2(&member, 1, 2));
    QEXTMemberFunctor2<double, MemberBase, double, double> doubleMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::doubleFunction2);
    QVERIFY(0 == doubleMemberBaseFunctor2(&member, 1.1, 2.2));

    QEXTMemberFunctor2<void, MemberBase, bool, int> voidMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::voidFunctionB2);
    voidMemberBaseFunctorB2(&member, true, 2);
    QEXTMemberFunctor2<int, MemberBase, bool, int> intMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::intFunctionB2);
    QVERIFY(1 == intMemberBaseFunctorB2(&member, true, 2));
    QVERIFY(0 == intMemberBaseFunctorB2(&member, false, 2));
    QEXTMemberFunctor2<double, MemberBase, bool, double> doubleMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleMemberBaseFunctorB2(&member, true, 2.2));
    QVERIFY(0 == doubleMemberBaseFunctorB2(&member, false, 2.2));

    QEXTMemberFunctor<void, MemberBase, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction2);
    voidMemberBaseFunctor(&member, 1, 2);
    QEXTMemberFunctor<int, MemberBase, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction2);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2));
    QEXTMemberFunctor<double, MemberBase, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction2);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2));

    QEXTMemberFunctor<void, MemberBase, bool, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB2);
    voidMemberBaseFunctorB(&member, true, 2);
    QEXTMemberFunctor<int, MemberBase, bool, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB2);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2));
    QEXTMemberFunctor<double, MemberBase, bool, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2));
}

void QEXTMemberFunctorTest::testConstFunctorWith2Arg()
{
    MemberBase memberBase;

    QEXTConstMemberFunctor2<void, MemberBase, int, int> voidConstMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::voidConstFunction2);
    voidConstMemberBaseFunctor2_(&memberBase, 1, 2);
    QEXTConstMemberFunctor2<int, MemberBase, int, int> intConstMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::intConstFunction2);
    QVERIFY(1 + 2 == intConstMemberBaseFunctor2_(&memberBase, 1, 2));
    QEXTConstMemberFunctor2<double, MemberBase, double, double> doubleConstMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleConstMemberBaseFunctor2_(&memberBase, 1.1, 2.2));

    QEXTConstMemberFunctor2<void, MemberBase, bool, int> voidConstMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::voidConstFunctionB2);
    voidConstMemberBaseFunctorB2_(&memberBase, true, 2);
    QEXTConstMemberFunctor2<int, MemberBase, bool, int> intConstMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::intConstFunctionB2);
    QVERIFY(2 == intConstMemberBaseFunctorB2_(&memberBase, true, 2));
    QVERIFY(0 == intConstMemberBaseFunctorB2_(&memberBase, false, 2));
    QEXTConstMemberFunctor2<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleConstMemberBaseFunctorB2_(&memberBase, true, 2.2));
    QVERIFY(0 == doubleConstMemberBaseFunctorB2_(&memberBase, false, 2.2));

    QEXTConstMemberFunctor2<void, MemberBase, int, int> voidConstMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction2);
    voidConstMemberBaseFunctor2_obj(&memberBase, 1, 2);
    QEXTConstMemberFunctor2<int, MemberBase, int, int> intConstMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction2);
    intConstMemberBaseFunctor2_obj(&memberBase, 1, 2);
    QVERIFY(1 + 2 == intConstMemberBaseFunctor2_obj(&memberBase, 1, 2));
    QEXTConstMemberFunctor2<double, MemberBase, double, double> doubleConstMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleConstMemberBaseFunctor2_obj(&memberBase, 1.1, 2.2));

    QEXTConstMemberFunctor2<void, MemberBase, bool, int> voidConstMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB2);
    voidConstMemberBaseFunctorB2_obj(&memberBase, true, 2);
    QEXTConstMemberFunctor2<int, MemberBase, bool, int> intConstMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB2);
    QVERIFY(2 == intConstMemberBaseFunctorB2_obj(&memberBase, true, 2));
    QVERIFY(0 == intConstMemberBaseFunctorB2_obj(&memberBase, false, 2));
    QEXTConstMemberFunctor2<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleConstMemberBaseFunctorB2_obj(&memberBase, true, 2.2));
    QVERIFY(0 == doubleConstMemberBaseFunctorB2_obj(&memberBase, false, 2.2));

    QEXTConstMemberFunctor2<void, MemberBase, int, int> voidConstMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::voidConstFunction2);
    voidConstMemberBaseFunctor2(&memberBase, 1, 2);
    QEXTConstMemberFunctor2<int, MemberBase, int, int> intConstMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::intConstFunction2);
    QVERIFY(1 + 2 == intConstMemberBaseFunctor2(&memberBase, 1, 2));
    QEXTConstMemberFunctor2<double, MemberBase, double, double> doubleConstMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleConstMemberBaseFunctor2(&memberBase, 1.1, 2.2));

    QEXTConstMemberFunctor2<void, MemberBase, bool, int> voidConstMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::voidConstFunctionB2);
    voidConstMemberBaseFunctorB2(&memberBase, true, 2);
    QEXTConstMemberFunctor2<int, MemberBase, bool, int> intConstMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::intConstFunctionB2);
    QVERIFY(2 == intConstMemberBaseFunctorB2(&memberBase, true, 2));
    QVERIFY(0 == intConstMemberBaseFunctorB2(&memberBase, false, 2));
    QEXTConstMemberFunctor2<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleConstMemberBaseFunctorB2(&memberBase, true, 2.2));
    QVERIFY(0 == doubleConstMemberBaseFunctorB2(&memberBase, false, 2.2));

    QEXTConstMemberFunctor<void, MemberBase, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction2);
    voidConstMemberBaseFunctor(&memberBase, 1, 2);
    QEXTConstMemberFunctor<int, MemberBase, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction2);
    QVERIFY(1 + 2 == intConstMemberBaseFunctor(&memberBase, 1, 2));
    QEXTConstMemberFunctor<double, MemberBase, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2));

    QEXTConstMemberFunctor<void, MemberBase, bool, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB2);
    voidConstMemberBaseFunctorB(&memberBase, true, 2);
    QEXTConstMemberFunctor<int, MemberBase, bool, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB2);
    QVERIFY(2 == intConstMemberBaseFunctorB(&memberBase, true, 2));
    QVERIFY(0 == intConstMemberBaseFunctorB(&memberBase, false, 2));
    QEXTConstMemberFunctor<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith2Arg()
{
    Member member;

    QEXTConstMemberFunctor2<void, MemberBase, int, int> voidConstMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::voidConstFunction2);
    voidConstMemberBaseFunctor2_(&member, 1, 2);
    QEXTConstMemberFunctor2<int, MemberBase, int, int> intConstMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::intConstFunction2);
    QVERIFY(0 == intConstMemberBaseFunctor2_(&member, 1, 2));
    QEXTConstMemberFunctor2<double, MemberBase, double, double> doubleConstMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleConstMemberBaseFunctor2_(&member, 1.1, 2.2));

    QEXTConstMemberFunctor2<void, MemberBase, bool, int> voidConstMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::voidConstFunctionB2);
    voidConstMemberBaseFunctorB2_(&member, true, 2);
    QEXTConstMemberFunctor2<int, MemberBase, bool, int> intConstMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::intConstFunctionB2);
    QVERIFY(1 == intConstMemberBaseFunctorB2_(&member, true, 2));
    QVERIFY(0 == intConstMemberBaseFunctorB2_(&member, false, 2));
    QEXTConstMemberFunctor2<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleConstMemberBaseFunctorB2_(&member, true, 2.2));
    QVERIFY(0 == doubleConstMemberBaseFunctorB2_(&member, false, 2.2));

    QEXTConstMemberFunctor2<void, MemberBase, int, int> voidConstMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction2);
    voidConstMemberBaseFunctor2_obj(&member, 1, 2);
    QEXTConstMemberFunctor2<int, MemberBase, int, int> intConstMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction2);
    intConstMemberBaseFunctor2_obj(&member, 1, 2);
    QVERIFY(0 == intConstMemberBaseFunctor2_obj(&member, 1, 2));
    QEXTConstMemberFunctor2<double, MemberBase, double, double> doubleConstMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleConstMemberBaseFunctor2_obj(&member, 1.1, 2.2));

    QEXTConstMemberFunctor2<void, MemberBase, bool, int> voidConstMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB2);
    voidConstMemberBaseFunctorB2_obj(&member, true, 2);
    QEXTConstMemberFunctor2<int, MemberBase, bool, int> intConstMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB2);
    QVERIFY(1 == intConstMemberBaseFunctorB2_obj(&member, true, 2));
    QVERIFY(0 == intConstMemberBaseFunctorB2_obj(&member, false, 2));
    QEXTConstMemberFunctor2<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleConstMemberBaseFunctorB2_obj(&member, true, 2.2));
    QVERIFY(0 == doubleConstMemberBaseFunctorB2_obj(&member, false, 2.2));

    QEXTConstMemberFunctor2<void, MemberBase, int, int> voidConstMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::voidConstFunction2);
    voidConstMemberBaseFunctor2(&member, 1, 2);
    QEXTConstMemberFunctor2<int, MemberBase, int, int> intConstMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::intConstFunction2);
    QVERIFY(0 == intConstMemberBaseFunctor2(&member, 1, 2));
    QEXTConstMemberFunctor2<double, MemberBase, double, double> doubleConstMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleConstMemberBaseFunctor2(&member, 1.1, 2.2));

    QEXTConstMemberFunctor2<void, MemberBase, bool, int> voidConstMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::voidConstFunctionB2);
    voidConstMemberBaseFunctorB2(&member, true, 2);
    QEXTConstMemberFunctor2<int, MemberBase, bool, int> intConstMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::intConstFunctionB2);
    QVERIFY(1 == intConstMemberBaseFunctorB2(&member, true, 2));
    QVERIFY(0 == intConstMemberBaseFunctorB2(&member, false, 2));
    QEXTConstMemberFunctor2<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleConstMemberBaseFunctorB2(&member, true, 2.2));
    QVERIFY(0 == doubleConstMemberBaseFunctorB2(&member, false, 2.2));

    QEXTConstMemberFunctor<void, MemberBase, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction2);
    voidConstMemberBaseFunctor(&member, 1, 2);
    QEXTConstMemberFunctor<int, MemberBase, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction2);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2));
    QEXTConstMemberFunctor<double, MemberBase, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2));

    QEXTConstMemberFunctor<void, MemberBase, bool, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB2);
    voidConstMemberBaseFunctorB(&member, true, 2);
    QEXTConstMemberFunctor<int, MemberBase, bool, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB2);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2));
    QEXTConstMemberFunctor<double, MemberBase, bool, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith2Arg()
{
    MemberBase memberBase;

    QEXTVolatileMemberFunctor2<void, MemberBase, int, int> voidVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::voidVolatileFunction2);
    voidVolatileMemberBaseFunctor2_(&memberBase, 1, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, int, int> intVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::intVolatileFunction2);
    QVERIFY(1 + 2 == intVolatileMemberBaseFunctor2_(&memberBase, 1, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleVolatileMemberBaseFunctor2_(&memberBase, 1.1, 2.2));

    QEXTVolatileMemberFunctor2<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB2);
    voidVolatileMemberBaseFunctorB2_(&memberBase, true, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intVolatileMemberBaseFunctorB2_(&memberBase, true, 2));
    QVERIFY(0 == intVolatileMemberBaseFunctorB2_(&memberBase, false, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleVolatileMemberBaseFunctorB2_(&memberBase, true, 2.2));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB2_(&memberBase, false, 2.2));

    QEXTVolatileMemberFunctor2<void, MemberBase, int, int> voidVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction2);
    voidVolatileMemberBaseFunctor2_obj(&memberBase, 1, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, int, int> intVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction2);
    intVolatileMemberBaseFunctor2_obj(&memberBase, 1, 2);
    QVERIFY(1 + 2 == intVolatileMemberBaseFunctor2_obj(&memberBase, 1, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleVolatileMemberBaseFunctor2_obj(&memberBase, 1.1, 2.2));

    QEXTVolatileMemberFunctor2<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB2);
    voidVolatileMemberBaseFunctorB2_obj(&memberBase, true, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intVolatileMemberBaseFunctorB2_obj(&memberBase, true, 2));
    QVERIFY(0 == intVolatileMemberBaseFunctorB2_obj(&memberBase, false, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleVolatileMemberBaseFunctorB2_obj(&memberBase, true, 2.2));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB2_obj(&memberBase, false, 2.2));

    QEXTVolatileMemberFunctor2<void, MemberBase, int, int> voidVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::voidVolatileFunction2);
    voidVolatileMemberBaseFunctor2(&memberBase, 1, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, int, int> intVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::intVolatileFunction2);
    QVERIFY(1 + 2 == intVolatileMemberBaseFunctor2(&memberBase, 1, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleVolatileMemberBaseFunctor2(&memberBase, 1.1, 2.2));

    QEXTVolatileMemberFunctor2<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::voidVolatileFunctionB2);
    voidVolatileMemberBaseFunctorB2(&memberBase, true, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intVolatileMemberBaseFunctorB2(&memberBase, true, 2));
    QVERIFY(0 == intVolatileMemberBaseFunctorB2(&memberBase, false, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleVolatileMemberBaseFunctorB2(&memberBase, true, 2.2));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB2(&memberBase, false, 2.2));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction2);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction2);
    QVERIFY(1 + 2 == intVolatileMemberBaseFunctor(&memberBase, 1, 2));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB2);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intVolatileMemberBaseFunctorB(&memberBase, true, 2));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&memberBase, false, 2));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith2Arg()
{
    Member member;

    QEXTVolatileMemberFunctor2<void, MemberBase, int, int> voidVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::voidVolatileFunction2);
    voidVolatileMemberBaseFunctor2_(&member, 1, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, int, int> intVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::intVolatileFunction2);
    QVERIFY(0 == intVolatileMemberBaseFunctor2_(&member, 1, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor2_(&member, 1.1, 2.2));

    QEXTVolatileMemberFunctor2<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB2);
    voidVolatileMemberBaseFunctorB2_(&member, true, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intVolatileMemberBaseFunctorB2_(&member, true, 2));
    QVERIFY(0 == intVolatileMemberBaseFunctorB2_(&member, false, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB2_(&member, true, 2.2));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB2_(&member, false, 2.2));

    QEXTVolatileMemberFunctor2<void, MemberBase, int, int> voidVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction2);
    voidVolatileMemberBaseFunctor2_obj(&member, 1, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, int, int> intVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction2);
    intVolatileMemberBaseFunctor2_obj(&member, 1, 2);
    QVERIFY(0 == intVolatileMemberBaseFunctor2_obj(&member, 1, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor2_obj(&member, 1.1, 2.2));

    QEXTVolatileMemberFunctor2<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB2);
    voidVolatileMemberBaseFunctorB2_obj(&member, true, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intVolatileMemberBaseFunctorB2_obj(&member, true, 2));
    QVERIFY(0 == intVolatileMemberBaseFunctorB2_obj(&member, false, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB2_obj(&member, true, 2.2));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB2_obj(&member, false, 2.2));

    QEXTVolatileMemberFunctor2<void, MemberBase, int, int> voidVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::voidVolatileFunction2);
    voidVolatileMemberBaseFunctor2(&member, 1, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, int, int> intVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::intVolatileFunction2);
    QVERIFY(0 == intVolatileMemberBaseFunctor2(&member, 1, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor2(&member, 1.1, 2.2));

    QEXTVolatileMemberFunctor2<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::voidVolatileFunctionB2);
    voidVolatileMemberBaseFunctorB2(&member, true, 2);
    QEXTVolatileMemberFunctor2<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intVolatileMemberBaseFunctorB2(&member, true, 2));
    QVERIFY(0 == intVolatileMemberBaseFunctorB2(&member, false, 2));
    QEXTVolatileMemberFunctor2<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB2(&member, true, 2.2));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB2(&member, false, 2.2));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction2);
    voidVolatileMemberBaseFunctor(&member, 1, 2);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction2);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB2);
    voidVolatileMemberBaseFunctorB(&member, true, 2);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith2Arg()
{
    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor2<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction2);
    voidConstVolatileMemberBaseFunctor2_(&memberBase, 1, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction2);
    QVERIFY(1 + 2 == intConstVolatileMemberBaseFunctor2_(&memberBase, 1, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleConstVolatileMemberBaseFunctor2_(&memberBase, 1.1, 2.2));

    QEXTConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB2);
    voidConstVolatileMemberBaseFunctorB2_(&memberBase, true, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intConstVolatileMemberBaseFunctorB2_(&memberBase, true, 2));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB2_(&memberBase, false, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleConstVolatileMemberBaseFunctorB2_(&memberBase, true, 2.2));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB2_(&memberBase, false, 2.2));

    QEXTConstVolatileMemberFunctor2<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction2);
    voidConstVolatileMemberBaseFunctor2_obj(&memberBase, 1, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction2);
    intConstVolatileMemberBaseFunctor2_obj(&memberBase, 1, 2);
    QVERIFY(1 + 2 == intConstVolatileMemberBaseFunctor2_obj(&memberBase, 1, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleConstVolatileMemberBaseFunctor2_obj(&memberBase, 1.1, 2.2));

    QEXTConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB2);
    voidConstVolatileMemberBaseFunctorB2_obj(&memberBase, true, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intConstVolatileMemberBaseFunctorB2_obj(&memberBase, true, 2));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB2_obj(&memberBase, false, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleConstVolatileMemberBaseFunctorB2_obj(&memberBase, true, 2.2));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB2_obj(&memberBase, false, 2.2));

    QEXTConstVolatileMemberFunctor2<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::voidConstVolatileFunction2);
    voidConstVolatileMemberBaseFunctor2(&memberBase, 1, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::intConstVolatileFunction2);
    QVERIFY(1 + 2 == intConstVolatileMemberBaseFunctor2(&memberBase, 1, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleConstVolatileMemberBaseFunctor2(&memberBase, 1.1, 2.2));

    QEXTConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::voidConstVolatileFunctionB2);
    voidConstVolatileMemberBaseFunctorB2(&memberBase, true, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intConstVolatileMemberBaseFunctorB2(&memberBase, true, 2));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB2(&memberBase, false, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleConstVolatileMemberBaseFunctorB2(&memberBase, true, 2.2));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB2(&memberBase, false, 2.2));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction2);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction2);
    QVERIFY(1 + 2 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB2);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith2Arg()
{
    Member member;

    QEXTConstVolatileMemberFunctor2<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction2);
    voidConstVolatileMemberBaseFunctor2_(&member, 1, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction2);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor2_(&member, 1, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor2_(&member, 1.1, 2.2));

    QEXTConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB2);
    voidConstVolatileMemberBaseFunctorB2_(&member, true, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB2_(&member, true, 2));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB2_(&member, false, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB2_(&member, true, 2.2));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB2_(&member, false, 2.2));

    QEXTConstVolatileMemberFunctor2<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction2);
    voidConstVolatileMemberBaseFunctor2_obj(&member, 1, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction2);
    intConstVolatileMemberBaseFunctor2_obj(&member, 1, 2);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor2_obj(&member, 1, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor2_obj(&member, 1.1, 2.2));

    QEXTConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB2);
    voidConstVolatileMemberBaseFunctorB2_obj(&member, true, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB2_obj(&member, true, 2));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB2_obj(&member, false, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB2_obj(&member, true, 2.2));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB2_obj(&member, false, 2.2));

    QEXTConstVolatileMemberFunctor2<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::voidConstVolatileFunction2);
    voidConstVolatileMemberBaseFunctor2(&member, 1, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::intConstVolatileFunction2);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor2(&member, 1, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(&MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor2(&member, 1.1, 2.2));

    QEXTConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::voidConstVolatileFunctionB2);
    voidConstVolatileMemberBaseFunctorB2(&member, true, 2);
    QEXTConstVolatileMemberFunctor2<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB2(&member, true, 2));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB2(&member, false, 2));
    QEXTConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB2(&member, true, 2.2));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB2(&member, false, 2.2));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction2);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction2);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB2);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2));
}

void QEXTMemberFunctorTest::testBoundFunctorWith2Arg()
{
    MemberBase memberBase;

    QEXTBoundMemberFunctor2<void, MemberBase, int, int> voidBoundMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor2_(1, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, int, int> intBoundMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::intFunction2);
    QVERIFY(1 + 2 == intBoundMemberBaseFunctor2_(1, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, double, double> doubleBoundMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundMemberBaseFunctor2_(1.1, 2.2));

    QEXTBoundMemberFunctor2<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB2_(true, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, bool, int> intBoundMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB2);
    QVERIFY(2 == intBoundMemberBaseFunctorB2_(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB2_(false, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleBoundMemberBaseFunctorB2_(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB2_(false, 2.2));

    QEXTBoundMemberFunctor2<void, MemberBase, int, int> voidBoundMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor2_obj(1, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, int, int> intBoundMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction2);
    intBoundMemberBaseFunctor2_obj(1, 2);
    QVERIFY(1 + 2 == intBoundMemberBaseFunctor2_obj(1, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, double, double> doubleBoundMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundMemberBaseFunctor2_obj(1.1, 2.2));

    QEXTBoundMemberFunctor2<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB2_obj(true, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, bool, int> intBoundMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB2);
    QVERIFY(2 == intBoundMemberBaseFunctorB2_obj(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB2_obj(false, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleBoundMemberBaseFunctorB2_obj(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB2_obj(false, 2.2));

    QEXTBoundMemberFunctor2<void, MemberBase, int, int> voidBoundMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor2(1, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, int, int> intBoundMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::intFunction2);
    QVERIFY(1 + 2 == intBoundMemberBaseFunctor2(1, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, double, double> doubleBoundMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundMemberBaseFunctor2(1.1, 2.2));

    QEXTBoundMemberFunctor2<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB2(true, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, bool, int> intBoundMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::intFunctionB2);
    QVERIFY(2 == intBoundMemberBaseFunctorB2(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB2(false, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleBoundMemberBaseFunctorB2(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB2(false, 2.2));

    QEXTBoundMemberFunctor<void, MemberBase, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor(1, 2);
    QEXTBoundMemberFunctor<int, MemberBase, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction2);
    QVERIFY(1 + 2 == intBoundMemberBaseFunctor(1, 2));
    QEXTBoundMemberFunctor<double, MemberBase, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundMemberBaseFunctor(1.1, 2.2));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB(true, 2);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB2);
    QVERIFY(2 == intBoundMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB2);
    QVERIFY(2.2 == doubleBoundMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith2Arg()
{
    Member member;

    QEXTBoundMemberFunctor2<void, MemberBase, int, int> voidBoundMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor2_(1, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, int, int> intBoundMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction2);
    QVERIFY(0 == intBoundMemberBaseFunctor2_(1, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, double, double> doubleBoundMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction2);
    QVERIFY(0 == doubleBoundMemberBaseFunctor2_(1.1, 2.2));

    QEXTBoundMemberFunctor2<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB2_(true, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, bool, int> intBoundMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB2);
    QVERIFY(1 == intBoundMemberBaseFunctorB2_(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB2_(false, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB2_(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB2_(false, 2.2));

    QEXTBoundMemberFunctor2<void, MemberBase, int, int> voidBoundMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor2_obj(1, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, int, int> intBoundMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction2);
    intBoundMemberBaseFunctor2_obj(1, 2);
    QVERIFY(0 == intBoundMemberBaseFunctor2_obj(1, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, double, double> doubleBoundMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction2);
    QVERIFY(0 == doubleBoundMemberBaseFunctor2_obj(1.1, 2.2));

    QEXTBoundMemberFunctor2<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB2_obj(true, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, bool, int> intBoundMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB2);
    QVERIFY(1 == intBoundMemberBaseFunctorB2_obj(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB2_obj(false, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB2_obj(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB2_obj(false, 2.2));

    QEXTBoundMemberFunctor2<void, MemberBase, int, int> voidBoundMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor2(1, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, int, int> intBoundMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction2);
    QVERIFY(0 == intBoundMemberBaseFunctor2(1, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, double, double> doubleBoundMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction2);
    QVERIFY(0 == doubleBoundMemberBaseFunctor2(1.1, 2.2));

    QEXTBoundMemberFunctor2<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB2(true, 2);
    QEXTBoundMemberFunctor2<int, MemberBase, bool, int> intBoundMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB2);
    QVERIFY(1 == intBoundMemberBaseFunctorB2(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB2(false, 2));
    QEXTBoundMemberFunctor2<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB2(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB2(false, 2.2));

    QEXTBoundMemberFunctor<void, MemberBase, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction2);
    voidBoundMemberBaseFunctor(1, 2);
    QEXTBoundMemberFunctor<int, MemberBase, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction2);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2));
    QEXTBoundMemberFunctor<double, MemberBase, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction2);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB2);
    voidBoundMemberBaseFunctorB(true, 2);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB2);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB2);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith2Arg()
{
    MemberBase memberBase;

    QEXTBoundConstMemberFunctor2<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor2_(1, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, int, int> intBoundConstMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction2);
    QVERIFY(1 + 2 == intBoundConstMemberBaseFunctor2_(1, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstMemberBaseFunctor2_(1.1, 2.2));

    QEXTBoundConstMemberFunctor2<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB2_(true, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB2);
    QVERIFY(2 == intBoundConstMemberBaseFunctorB2_(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB2_(false, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleBoundConstMemberBaseFunctorB2_(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB2_(false, 2.2));

    QEXTBoundConstMemberFunctor2<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor2_obj(1, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, int, int> intBoundConstMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction2);
    intBoundConstMemberBaseFunctor2_obj(1, 2);
    QVERIFY(1 + 2 == intBoundConstMemberBaseFunctor2_obj(1, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstMemberBaseFunctor2_obj(1.1, 2.2));

    QEXTBoundConstMemberFunctor2<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB2_obj(true, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB2);
    QVERIFY(2 == intBoundConstMemberBaseFunctorB2_obj(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB2_obj(false, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleBoundConstMemberBaseFunctorB2_obj(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB2_obj(false, 2.2));

    QEXTBoundConstMemberFunctor2<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor2(1, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, int, int> intBoundConstMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::intConstFunction2);
    QVERIFY(1 + 2 == intBoundConstMemberBaseFunctor2(1, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstMemberBaseFunctor2(1.1, 2.2));

    QEXTBoundConstMemberFunctor2<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB2(true, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::intConstFunctionB2);
    QVERIFY(2 == intBoundConstMemberBaseFunctorB2(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB2(false, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleBoundConstMemberBaseFunctorB2(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB2(false, 2.2));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor(1, 2);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction2);
    QVERIFY(1 + 2 == intBoundConstMemberBaseFunctor(1, 2));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstMemberBaseFunctor(1.1, 2.2));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB(true, 2);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB2);
    QVERIFY(2 == intBoundConstMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB2);
    QVERIFY(2.2 == doubleBoundConstMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith2Arg()
{
    Member member;

    QEXTBoundConstMemberFunctor2<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor2_(1, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, int, int> intBoundConstMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction2);
    QVERIFY(0 == intBoundConstMemberBaseFunctor2_(1, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor2_(1.1, 2.2));

    QEXTBoundConstMemberFunctor2<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB2_(true, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB2);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB2_(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB2_(false, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB2_(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB2_(false, 2.2));

    QEXTBoundConstMemberFunctor2<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor2_obj(1, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, int, int> intBoundConstMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction2);
    intBoundConstMemberBaseFunctor2_obj(1, 2);
    QVERIFY(0 == intBoundConstMemberBaseFunctor2_obj(1, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor2_obj(1.1, 2.2));

    QEXTBoundConstMemberFunctor2<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB2_obj(true, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB2);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB2_obj(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB2_obj(false, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB2_obj(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB2_obj(false, 2.2));

    QEXTBoundConstMemberFunctor2<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor2(1, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, int, int> intBoundConstMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction2);
    QVERIFY(0 == intBoundConstMemberBaseFunctor2(1, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor2(1.1, 2.2));

    QEXTBoundConstMemberFunctor2<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB2(true, 2);
    QEXTBoundConstMemberFunctor2<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB2);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB2(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB2(false, 2));
    QEXTBoundConstMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB2(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB2(false, 2.2));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction2);
    voidBoundConstMemberBaseFunctor(1, 2);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction2);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction2);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB2);
    voidBoundConstMemberBaseFunctorB(true, 2);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB2);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB2);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith2Arg()
{
    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor2_(1, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction2);
    QVERIFY(1 + 2 == intBoundVolatileMemberBaseFunctor2_(1, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundVolatileMemberBaseFunctor2_(1.1, 2.2));

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB2_(true, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intBoundVolatileMemberBaseFunctorB2_(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB2_(false, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundVolatileMemberBaseFunctorB2_(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB2_(false, 2.2));

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor2_obj(1, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction2);
    intBoundVolatileMemberBaseFunctor2_obj(1, 2);
    QVERIFY(1 + 2 == intBoundVolatileMemberBaseFunctor2_obj(1, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundVolatileMemberBaseFunctor2_obj(1.1, 2.2));

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB2_obj(true, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intBoundVolatileMemberBaseFunctorB2_obj(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB2_obj(false, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundVolatileMemberBaseFunctorB2_obj(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB2_obj(false, 2.2));

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor2(1, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::intVolatileFunction2);
    QVERIFY(1 + 2 == intBoundVolatileMemberBaseFunctor2(1, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundVolatileMemberBaseFunctor2(1.1, 2.2));

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB2(true, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intBoundVolatileMemberBaseFunctorB2(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB2(false, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundVolatileMemberBaseFunctorB2(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB2(false, 2.2));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor(1, 2);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction2);
    QVERIFY(1 + 2 == intBoundVolatileMemberBaseFunctor(1, 2));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB(true, 2);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB2);
    QVERIFY(2 == intBoundVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith2Arg()
{
    Member member;

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor2_(1, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction2);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor2_(1, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor2_(1.1, 2.2));

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB2_(true, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB2_(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB2_(false, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB2_(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB2_(false, 2.2));

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor2_obj(1, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction2);
    intBoundVolatileMemberBaseFunctor2_obj(1, 2);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor2_obj(1, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor2_obj(1.1, 2.2));

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB2_obj(true, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB2_obj(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB2_obj(false, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB2_obj(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB2_obj(false, 2.2));

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor2(1, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction2);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor2(1, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor2(1.1, 2.2));

    QEXTBoundVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB2(true, 2);
    QEXTBoundVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB2(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB2(false, 2));
    QEXTBoundVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB2(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB2(false, 2.2));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction2);
    voidBoundVolatileMemberBaseFunctor(1, 2);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction2);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction2);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB2);
    voidBoundVolatileMemberBaseFunctorB(true, 2);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB2);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB2);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith2Arg()
{
    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor2_(1, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction2);
    QVERIFY(1 + 2 == intBoundConstVolatileMemberBaseFunctor2_(1, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstVolatileMemberBaseFunctor2_(1.1, 2.2));

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB2_(true, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intBoundConstVolatileMemberBaseFunctorB2_(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB2_(false, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundConstVolatileMemberBaseFunctorB2_(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB2_(false, 2.2));

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor2_obj(1, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction2);
    intBoundConstVolatileMemberBaseFunctor2_obj(1, 2);
    QVERIFY(1 + 2 == intBoundConstVolatileMemberBaseFunctor2_obj(1, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstVolatileMemberBaseFunctor2_obj(1.1, 2.2));

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB2_obj(true, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intBoundConstVolatileMemberBaseFunctorB2_obj(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB2_obj(false, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundConstVolatileMemberBaseFunctorB2_obj(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB2_obj(false, 2.2));

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor2(1, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::intConstVolatileFunction2);
    QVERIFY(1 + 2 == intBoundConstVolatileMemberBaseFunctor2(1, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(&memberBase, &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstVolatileMemberBaseFunctor2(1.1, 2.2));

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB2(true, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intBoundConstVolatileMemberBaseFunctorB2(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB2(false, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(&memberBase, &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundConstVolatileMemberBaseFunctorB2(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB2(false, 2.2));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor(1, 2);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction2);
    QVERIFY(1 + 2 == intBoundConstVolatileMemberBaseFunctor(1, 2));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(1.1 + 2.2 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(2 == intBoundConstVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(2.2 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith2Arg()
{
    Member member;

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor2_(1, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction2);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor2_(1, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor2_(1.1, 2.2));

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB2_(true, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB2_(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB2_(false, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB2_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB2_(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB2_(false, 2.2));

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor2_obj(1, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction2);
    intBoundConstVolatileMemberBaseFunctor2_obj(1, 2);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor2_obj(1, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor2_obj(1.1, 2.2));

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB2_obj(true, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB2_obj(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB2_obj(false, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB2_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB2_obj(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB2_obj(false, 2.2));

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor2(1, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction2);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor2(1, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor2(1.1, 2.2));

    QEXTBoundConstVolatileMemberFunctor2<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB2(true, 2);
    QEXTBoundConstVolatileMemberFunctor2<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB2(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB2(false, 2));
    QEXTBoundConstVolatileMemberFunctor2<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB2 = qextMemberFunctor2(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB2(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB2(false, 2.2));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction2);
    voidBoundConstVolatileMemberBaseFunctor(1, 2);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction2);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction2);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB2);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB2);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB2);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2));
}

void QEXTMemberFunctorTest::testFunctorWith3Arg()
{
    MemberBase memberBase;

    QEXTMemberFunctor3<void, MemberBase, int, int, int> voidMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::voidFunction3);
    voidMemberBaseFunctor3_(&memberBase, 1, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, int, int, int> intMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intMemberBaseFunctor3_(&memberBase, 1, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, double, double, double> doubleMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleMemberBaseFunctor3_(&memberBase, 1.1, 2.2, 3.3));

    QEXTMemberFunctor3<void, MemberBase, bool, int, int> voidMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::voidFunctionB3);
    voidMemberBaseFunctorB3_(&memberBase, true, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, bool, int, int> intMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intMemberBaseFunctorB3_(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intMemberBaseFunctorB3_(&memberBase, false, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleMemberBaseFunctorB3_(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleMemberBaseFunctorB3_(&memberBase, false, 2.2, 3.3));

    QEXTMemberFunctor3<void, MemberBase, int, int, int> voidMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction3);
    voidMemberBaseFunctor3_obj(&memberBase, 1, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, int, int, int> intMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intMemberBaseFunctor3_obj(&memberBase, 1, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, double, double, double> doubleMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleMemberBaseFunctor3_obj(&memberBase, 1.1, 2.2, 3.3));

    QEXTMemberFunctor3<void, MemberBase, bool, int, int> voidMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB3);
    voidMemberBaseFunctorB3_obj(&memberBase, true, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, bool, int, int> intMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intMemberBaseFunctorB3_obj(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intMemberBaseFunctorB3_obj(&memberBase, false, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleMemberBaseFunctorB3_obj(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleMemberBaseFunctorB3_obj(&memberBase, false, 2.2, 3.3));

    QEXTMemberFunctor3<void, MemberBase, int, int, int> voidMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::voidFunction3);
    voidMemberBaseFunctor3(&memberBase, 1, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, int, int, int> intMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intMemberBaseFunctor3(&memberBase, 1, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, double, double, double> doubleMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleMemberBaseFunctor3(&memberBase, 1.1, 2.2, 3.3));

    QEXTMemberFunctor3<void, MemberBase, bool, int, int> voidMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::voidFunctionB3);
    voidMemberBaseFunctorB3(&memberBase, true, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, bool, int, int> intMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intMemberBaseFunctorB3(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intMemberBaseFunctorB3(&memberBase, false, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleMemberBaseFunctorB3(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleMemberBaseFunctorB3(&memberBase, false, 2.2, 3.3));

    QEXTMemberFunctor<void, MemberBase, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction3);
    voidMemberBaseFunctor(&memberBase, 1, 2, 3);
    QEXTMemberFunctor<int, MemberBase, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intMemberBaseFunctor(&memberBase, 1, 2, 3));
    QEXTMemberFunctor<double, MemberBase, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

    QEXTMemberFunctor<void, MemberBase, bool, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB3);
    voidMemberBaseFunctorB(&memberBase, true, 2, 3);
    QEXTMemberFunctor<int, MemberBase, bool, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intMemberBaseFunctorB(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intMemberBaseFunctorB(&memberBase, false, 2, 3));
    QEXTMemberFunctor<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith3Arg()
{
    Member member;

    QEXTMemberFunctor3<void, MemberBase, int, int, int> voidMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::voidFunction3);
    voidMemberBaseFunctor3_(&member, 1, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, int, int, int> intMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::intFunction3);
    QVERIFY(0 == intMemberBaseFunctor3_(&member, 1, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, double, double, double> doubleMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::doubleFunction3);
    QVERIFY(0 == doubleMemberBaseFunctor3_(&member, 1.1, 2.2, 3.3));

    QEXTMemberFunctor3<void, MemberBase, bool, int, int> voidMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::voidFunctionB3);
    voidMemberBaseFunctorB3_(&member, true, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, bool, int, int> intMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::intFunctionB3);
    QVERIFY(1 == intMemberBaseFunctorB3_(&member, true, 2, 3));
    QVERIFY(0 == intMemberBaseFunctorB3_(&member, false, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleMemberBaseFunctorB3_(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleMemberBaseFunctorB3_(&member, false, 2.2, 3.3));

    QEXTMemberFunctor3<void, MemberBase, int, int, int> voidMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction3);
    voidMemberBaseFunctor3_obj(&member, 1, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, int, int, int> intMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction3);
    QVERIFY(0 == intMemberBaseFunctor3_obj(&member, 1, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, double, double, double> doubleMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction3);
    QVERIFY(0 == doubleMemberBaseFunctor3_obj(&member, 1.1, 2.2, 3.3));

    QEXTMemberFunctor3<void, MemberBase, bool, int, int> voidMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB3);
    voidMemberBaseFunctorB3_obj(&member, true, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, bool, int, int> intMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB3);
    QVERIFY(1 == intMemberBaseFunctorB3_obj(&member, true, 2, 3));
    QVERIFY(0 == intMemberBaseFunctorB3_obj(&member, false, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleMemberBaseFunctorB3_obj(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleMemberBaseFunctorB3_obj(&member, false, 2.2, 3.3));

    QEXTMemberFunctor3<void, MemberBase, int, int, int> voidMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::voidFunction3);
    voidMemberBaseFunctor3(&member, 1, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, int, int, int> intMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::intFunction3);
    QVERIFY(0 == intMemberBaseFunctor3(&member, 1, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, double, double, double> doubleMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::doubleFunction3);
    QVERIFY(0 == doubleMemberBaseFunctor3(&member, 1.1, 2.2, 3.3));

    QEXTMemberFunctor3<void, MemberBase, bool, int, int> voidMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::voidFunctionB3);
    voidMemberBaseFunctorB3(&member, true, 2, 3);
    QEXTMemberFunctor3<int, MemberBase, bool, int, int> intMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::intFunctionB3);
    QVERIFY(1 == intMemberBaseFunctorB3(&member, true, 2, 3));
    QVERIFY(0 == intMemberBaseFunctorB3(&member, false, 2, 3));
    QEXTMemberFunctor3<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleMemberBaseFunctorB3(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleMemberBaseFunctorB3(&member, false, 2.2, 3.3));

    QEXTMemberFunctor<void, MemberBase, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction3);
    voidMemberBaseFunctor(&member, 1, 2, 3);
    QEXTMemberFunctor<int, MemberBase, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction3);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2, 3));
    QEXTMemberFunctor<double, MemberBase, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction3);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

    QEXTMemberFunctor<void, MemberBase, bool, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB3);
    voidMemberBaseFunctorB(&member, true, 2, 3);
    QEXTMemberFunctor<int, MemberBase, bool, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB3);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2, 3));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2, 3));
    QEXTMemberFunctor<double, MemberBase, bool, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testConstFunctorWith3Arg()
{
    MemberBase memberBase;

    QEXTConstMemberFunctor3<void, MemberBase, int, int, int> voidConstMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::voidConstFunction3);
    voidConstMemberBaseFunctor3_(&memberBase, 1, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, int, int, int> intConstMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intConstMemberBaseFunctor3_(&memberBase, 1, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleConstMemberBaseFunctor3_(&memberBase, 1.1, 2.2, 3.3));

    QEXTConstMemberFunctor3<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::voidConstFunctionB3);
    voidConstMemberBaseFunctorB3_(&memberBase, true, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intConstMemberBaseFunctorB3_(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intConstMemberBaseFunctorB3_(&memberBase, false, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleConstMemberBaseFunctorB3_(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleConstMemberBaseFunctorB3_(&memberBase, false, 2.2, 3.3));

    QEXTConstMemberFunctor3<void, MemberBase, int, int, int> voidConstMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction3);
    voidConstMemberBaseFunctor3_obj(&memberBase, 1, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, int, int, int> intConstMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intConstMemberBaseFunctor3_obj(&memberBase, 1, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleConstMemberBaseFunctor3_obj(&memberBase, 1.1, 2.2, 3.3));

    QEXTConstMemberFunctor3<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB3);
    voidConstMemberBaseFunctorB3_obj(&memberBase, true, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intConstMemberBaseFunctorB3_obj(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intConstMemberBaseFunctorB3_obj(&memberBase, false, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleConstMemberBaseFunctorB3_obj(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleConstMemberBaseFunctorB3_obj(&memberBase, false, 2.2, 3.3));

    QEXTConstMemberFunctor3<void, MemberBase, int, int, int> voidConstMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::voidConstFunction3);
    voidConstMemberBaseFunctor3(&memberBase, 1, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, int, int, int> intConstMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intConstMemberBaseFunctor3(&memberBase, 1, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleConstMemberBaseFunctor3(&memberBase, 1.1, 2.2, 3.3));

    QEXTConstMemberFunctor3<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::voidConstFunctionB3);
    voidConstMemberBaseFunctorB3(&memberBase, true, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intConstMemberBaseFunctorB3(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intConstMemberBaseFunctorB3(&memberBase, false, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleConstMemberBaseFunctorB3(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleConstMemberBaseFunctorB3(&memberBase, false, 2.2, 3.3));

    QEXTConstMemberFunctor<void, MemberBase, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction3);
    voidConstMemberBaseFunctor(&memberBase, 1, 2, 3);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB3);
    voidConstMemberBaseFunctorB(&memberBase, true, 2, 3);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith3Arg()
{
    Member member;

    QEXTConstMemberFunctor3<void, MemberBase, int, int, int> voidConstMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::voidConstFunction3);
    voidConstMemberBaseFunctor3_(&member, 1, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, int, int, int> intConstMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::intConstFunction3);
    QVERIFY(0 == intConstMemberBaseFunctor3_(&member, 1, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleConstMemberBaseFunctor3_(&member, 1.1, 2.2, 3.3));

    QEXTConstMemberFunctor3<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::voidConstFunctionB3);
    voidConstMemberBaseFunctorB3_(&member, true, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::intConstFunctionB3);
    QVERIFY(1 == intConstMemberBaseFunctorB3_(&member, true, 2, 3));
    QVERIFY(0 == intConstMemberBaseFunctorB3_(&member, false, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleConstMemberBaseFunctorB3_(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleConstMemberBaseFunctorB3_(&member, false, 2.2, 3.3));

    QEXTConstMemberFunctor3<void, MemberBase, int, int, int> voidConstMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction3);
    voidConstMemberBaseFunctor3_obj(&member, 1, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, int, int, int> intConstMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction3);
    QVERIFY(0 == intConstMemberBaseFunctor3_obj(&member, 1, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleConstMemberBaseFunctor3_obj(&member, 1.1, 2.2, 3.3));

    QEXTConstMemberFunctor3<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB3);
    voidConstMemberBaseFunctorB3_obj(&member, true, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB3);
    QVERIFY(1 == intConstMemberBaseFunctorB3_obj(&member, true, 2, 3));
    QVERIFY(0 == intConstMemberBaseFunctorB3_obj(&member, false, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleConstMemberBaseFunctorB3_obj(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleConstMemberBaseFunctorB3_obj(&member, false, 2.2, 3.3));

    QEXTConstMemberFunctor3<void, MemberBase, int, int, int> voidConstMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::voidConstFunction3);
    voidConstMemberBaseFunctor3(&member, 1, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, int, int, int> intConstMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::intConstFunction3);
    QVERIFY(0 == intConstMemberBaseFunctor3(&member, 1, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleConstMemberBaseFunctor3(&member, 1.1, 2.2, 3.3));

    QEXTConstMemberFunctor3<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::voidConstFunctionB3);
    voidConstMemberBaseFunctorB3(&member, true, 2, 3);
    QEXTConstMemberFunctor3<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::intConstFunctionB3);
    QVERIFY(1 == intConstMemberBaseFunctorB3(&member, true, 2, 3));
    QVERIFY(0 == intConstMemberBaseFunctorB3(&member, false, 2, 3));
    QEXTConstMemberFunctor3<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleConstMemberBaseFunctorB3(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleConstMemberBaseFunctorB3(&member, false, 2.2, 3.3));

    QEXTConstMemberFunctor<void, MemberBase, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction3);
    voidConstMemberBaseFunctor(&member, 1, 2, 3);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction3);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2, 3));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB3);
    voidConstMemberBaseFunctorB(&member, true, 2, 3);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB3);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2, 3));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2, 3));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith3Arg()
{
    MemberBase memberBase;

    QEXTVolatileMemberFunctor3<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::voidVolatileFunction3);
    voidVolatileMemberBaseFunctor3_(&memberBase, 1, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intVolatileMemberBaseFunctor3_(&memberBase, 1, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleVolatileMemberBaseFunctor3_(&memberBase, 1.1, 2.2, 3.3));

    QEXTVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB3);
    voidVolatileMemberBaseFunctorB3_(&memberBase, true, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intVolatileMemberBaseFunctorB3_(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intVolatileMemberBaseFunctorB3_(&memberBase, false, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleVolatileMemberBaseFunctorB3_(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleVolatileMemberBaseFunctorB3_(&memberBase, false, 2.2, 3.3));

    QEXTVolatileMemberFunctor3<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction3);
    voidVolatileMemberBaseFunctor3_obj(&memberBase, 1, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intVolatileMemberBaseFunctor3_obj(&memberBase, 1, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleVolatileMemberBaseFunctor3_obj(&memberBase, 1.1, 2.2, 3.3));

    QEXTVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB3);
    voidVolatileMemberBaseFunctorB3_obj(&memberBase, true, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intVolatileMemberBaseFunctorB3_obj(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intVolatileMemberBaseFunctorB3_obj(&memberBase, false, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleVolatileMemberBaseFunctorB3_obj(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleVolatileMemberBaseFunctorB3_obj(&memberBase, false, 2.2, 3.3));

    QEXTVolatileMemberFunctor3<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::voidVolatileFunction3);
    voidVolatileMemberBaseFunctor3(&memberBase, 1, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intVolatileMemberBaseFunctor3(&memberBase, 1, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleVolatileMemberBaseFunctor3(&memberBase, 1.1, 2.2, 3.3));

    QEXTVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::voidVolatileFunctionB3);
    voidVolatileMemberBaseFunctorB3(&memberBase, true, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intVolatileMemberBaseFunctorB3(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intVolatileMemberBaseFunctorB3(&memberBase, false, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleVolatileMemberBaseFunctorB3(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleVolatileMemberBaseFunctorB3(&memberBase, false, 2.2, 3.3));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction3);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB3);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith3Arg()
{
    Member member;

    QEXTVolatileMemberFunctor3<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::voidVolatileFunction3);
    voidVolatileMemberBaseFunctor3_(&member, 1, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::intVolatileFunction3);
    QVERIFY(0 == intVolatileMemberBaseFunctor3_(&member, 1, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor3_(&member, 1.1, 2.2, 3.3));

    QEXTVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB3);
    voidVolatileMemberBaseFunctorB3_(&member, true, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intVolatileMemberBaseFunctorB3_(&member, true, 2, 3));
    QVERIFY(0 == intVolatileMemberBaseFunctorB3_(&member, false, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB3_(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB3_(&member, false, 2.2, 3.3));

    QEXTVolatileMemberFunctor3<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction3);
    voidVolatileMemberBaseFunctor3_obj(&member, 1, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction3);
    QVERIFY(0 == intVolatileMemberBaseFunctor3_obj(&member, 1, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor3_obj(&member, 1.1, 2.2, 3.3));

    QEXTVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB3);
    voidVolatileMemberBaseFunctorB3_obj(&member, true, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intVolatileMemberBaseFunctorB3_obj(&member, true, 2, 3));
    QVERIFY(0 == intVolatileMemberBaseFunctorB3_obj(&member, false, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB3_obj(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB3_obj(&member, false, 2.2, 3.3));

    QEXTVolatileMemberFunctor3<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::voidVolatileFunction3);
    voidVolatileMemberBaseFunctor3(&member, 1, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::intVolatileFunction3);
    QVERIFY(0 == intVolatileMemberBaseFunctor3(&member, 1, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor3(&member, 1.1, 2.2, 3.3));

    QEXTVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::voidVolatileFunctionB3);
    voidVolatileMemberBaseFunctorB3(&member, true, 2, 3);
    QEXTVolatileMemberFunctor3<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intVolatileMemberBaseFunctorB3(&member, true, 2, 3));
    QVERIFY(0 == intVolatileMemberBaseFunctorB3(&member, false, 2, 3));
    QEXTVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB3(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB3(&member, false, 2.2, 3.3));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction3);
    voidVolatileMemberBaseFunctor(&member, 1, 2, 3);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction3);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB3);
    voidVolatileMemberBaseFunctorB(&member, true, 2, 3);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith3Arg()
{
    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction3);
    voidConstVolatileMemberBaseFunctor3_(&memberBase, 1, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intConstVolatileMemberBaseFunctor3_(&memberBase, 1, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleConstVolatileMemberBaseFunctor3_(&memberBase, 1.1, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB3);
    voidConstVolatileMemberBaseFunctorB3_(&memberBase, true, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intConstVolatileMemberBaseFunctorB3_(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intConstVolatileMemberBaseFunctorB3_(&memberBase, false, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleConstVolatileMemberBaseFunctorB3_(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleConstVolatileMemberBaseFunctorB3_(&memberBase, false, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction3);
    voidConstVolatileMemberBaseFunctor3_obj(&memberBase, 1, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intConstVolatileMemberBaseFunctor3_obj(&memberBase, 1, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleConstVolatileMemberBaseFunctor3_obj(&memberBase, 1.1, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB3);
    voidConstVolatileMemberBaseFunctorB3_obj(&memberBase, true, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intConstVolatileMemberBaseFunctorB3_obj(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intConstVolatileMemberBaseFunctorB3_obj(&memberBase, false, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleConstVolatileMemberBaseFunctorB3_obj(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleConstVolatileMemberBaseFunctorB3_obj(&memberBase, false, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::voidConstVolatileFunction3);
    voidConstVolatileMemberBaseFunctor3(&memberBase, 1, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intConstVolatileMemberBaseFunctor3(&memberBase, 1, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleConstVolatileMemberBaseFunctor3(&memberBase, 1.1, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::voidConstVolatileFunctionB3);
    voidConstVolatileMemberBaseFunctorB3(&memberBase, true, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intConstVolatileMemberBaseFunctorB3(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intConstVolatileMemberBaseFunctorB3(&memberBase, false, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleConstVolatileMemberBaseFunctorB3(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleConstVolatileMemberBaseFunctorB3(&memberBase, false, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction3);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB3);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3));
    QVERIFY(2 * 3 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith3Arg()
{
    Member member;

    QEXTConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction3);
    voidConstVolatileMemberBaseFunctor3_(&member, 1, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor3_(&member, 1, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor3_(&member, 1.1, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB3);
    voidConstVolatileMemberBaseFunctorB3_(&member, true, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB3_(&member, true, 2, 3));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB3_(&member, false, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB3_(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB3_(&member, false, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction3);
    voidConstVolatileMemberBaseFunctor3_obj(&member, 1, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor3_obj(&member, 1, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor3_obj(&member, 1.1, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB3);
    voidConstVolatileMemberBaseFunctorB3_obj(&member, true, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB3_obj(&member, true, 2, 3));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB3_obj(&member, false, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB3_obj(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB3_obj(&member, false, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::voidConstVolatileFunction3);
    voidConstVolatileMemberBaseFunctor3(&member, 1, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor3(&member, 1, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(&MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor3(&member, 1.1, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::voidConstVolatileFunctionB3);
    voidConstVolatileMemberBaseFunctorB3(&member, true, 2, 3);
    QEXTConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB3(&member, true, 2, 3));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB3(&member, false, 2, 3));
    QEXTConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB3(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB3(&member, false, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction3);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB3);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testBoundFunctorWith3Arg()
{
    MemberBase memberBase;

    QEXTBoundMemberFunctor3<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor3_(1, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, int, int, int> intBoundMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intBoundMemberBaseFunctor3_(1, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundMemberBaseFunctor3_(1.1, 2.2, 3.3));

    QEXTBoundMemberFunctor3<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB3_(true, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intBoundMemberBaseFunctorB3_(true, 2, 3));
    QVERIFY(2 * 3 == intBoundMemberBaseFunctorB3_(false, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundMemberBaseFunctorB3_(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundMemberBaseFunctorB3_(false, 2.2, 3.3));

    QEXTBoundMemberFunctor3<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor3_obj(1, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, int, int, int> intBoundMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intBoundMemberBaseFunctor3_obj(1, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundMemberBaseFunctor3_obj(1.1, 2.2, 3.3));

    QEXTBoundMemberFunctor3<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB3_obj(true, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intBoundMemberBaseFunctorB3_obj(true, 2, 3));
    QVERIFY(2 * 3 == intBoundMemberBaseFunctorB3_obj(false, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundMemberBaseFunctorB3_obj(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundMemberBaseFunctorB3_obj(false, 2.2, 3.3));

    QEXTBoundMemberFunctor3<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor3(1, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, int, int, int> intBoundMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intBoundMemberBaseFunctor3(1, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundMemberBaseFunctor3(1.1, 2.2, 3.3));

    QEXTBoundMemberFunctor3<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB3(true, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intBoundMemberBaseFunctorB3(true, 2, 3));
    QVERIFY(2 * 3 == intBoundMemberBaseFunctorB3(false, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundMemberBaseFunctorB3(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundMemberBaseFunctorB3(false, 2.2, 3.3));

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor(1, 2, 3);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction3);
    QVERIFY(1 + 2 + 3 == intBoundMemberBaseFunctor(1, 2, 3));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB(true, 2, 3);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB3);
    QVERIFY(2 + 3 == intBoundMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundMemberBaseFunctorB(false, 2, 3));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith3Arg()
{
    Member member;

    QEXTBoundMemberFunctor3<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor3_(1, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, int, int, int> intBoundMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction3);
    QVERIFY(0 == intBoundMemberBaseFunctor3_(1, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction3);
    QVERIFY(0 == doubleBoundMemberBaseFunctor3_(1.1, 2.2, 3.3));

    QEXTBoundMemberFunctor3<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB3_(true, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB3);
    QVERIFY(1 == intBoundMemberBaseFunctorB3_(true, 2, 3));
    QVERIFY(0 == intBoundMemberBaseFunctorB3_(false, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB3_(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB3_(false, 2.2, 3.3));

    QEXTBoundMemberFunctor3<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor3_obj(1, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, int, int, int> intBoundMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction3);
    QVERIFY(0 == intBoundMemberBaseFunctor3_obj(1, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction3);
    QVERIFY(0 == doubleBoundMemberBaseFunctor3_obj(1.1, 2.2, 3.3));

    QEXTBoundMemberFunctor3<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB3_obj(true, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB3);
    QVERIFY(1 == intBoundMemberBaseFunctorB3_obj(true, 2, 3));
    QVERIFY(0 == intBoundMemberBaseFunctorB3_obj(false, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB3_obj(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB3_obj(false, 2.2, 3.3));

    QEXTBoundMemberFunctor3<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor3(1, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, int, int, int> intBoundMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction3);
    QVERIFY(0 == intBoundMemberBaseFunctor3(1, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction3);
    QVERIFY(0 == doubleBoundMemberBaseFunctor3(1.1, 2.2, 3.3));

    QEXTBoundMemberFunctor3<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB3(true, 2, 3);
    QEXTBoundMemberFunctor3<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB3);
    QVERIFY(1 == intBoundMemberBaseFunctorB3(true, 2, 3));
    QVERIFY(0 == intBoundMemberBaseFunctorB3(false, 2, 3));
    QEXTBoundMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB3(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB3(false, 2.2, 3.3));

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction3);
    voidBoundMemberBaseFunctor(1, 2, 3);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction3);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction3);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB3);
    voidBoundMemberBaseFunctorB(true, 2, 3);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB3);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB3);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith3Arg()
{
    MemberBase memberBase;

    QEXTBoundConstMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor3_(1, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstMemberBaseFunctor3_(1, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstMemberBaseFunctor3_(1.1, 2.2, 3.3));

    QEXTBoundConstMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB3_(true, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intBoundConstMemberBaseFunctorB3_(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstMemberBaseFunctorB3_(false, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstMemberBaseFunctorB3_(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstMemberBaseFunctorB3_(false, 2.2, 3.3));

    QEXTBoundConstMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor3_obj(1, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstMemberBaseFunctor3_obj(1, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstMemberBaseFunctor3_obj(1.1, 2.2, 3.3));

    QEXTBoundConstMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB3_obj(true, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intBoundConstMemberBaseFunctorB3_obj(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstMemberBaseFunctorB3_obj(false, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstMemberBaseFunctorB3_obj(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstMemberBaseFunctorB3_obj(false, 2.2, 3.3));

    QEXTBoundConstMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor3(1, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstMemberBaseFunctor3(1, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstMemberBaseFunctor3(1.1, 2.2, 3.3));

    QEXTBoundConstMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB3(true, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intBoundConstMemberBaseFunctorB3(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstMemberBaseFunctorB3(false, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstMemberBaseFunctorB3(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstMemberBaseFunctorB3(false, 2.2, 3.3));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor(1, 2, 3);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstMemberBaseFunctor(1, 2, 3));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB(true, 2, 3);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB3);
    QVERIFY(2 + 3 == intBoundConstMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstMemberBaseFunctorB(false, 2, 3));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith3Arg()
{
    Member member;

    QEXTBoundConstMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor3_(1, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction3);
    QVERIFY(0 == intBoundConstMemberBaseFunctor3_(1, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor3_(1.1, 2.2, 3.3));

    QEXTBoundConstMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB3_(true, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB3);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB3_(true, 2, 3));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB3_(false, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB3_(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB3_(false, 2.2, 3.3));

    QEXTBoundConstMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor3_obj(1, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction3);
    QVERIFY(0 == intBoundConstMemberBaseFunctor3_obj(1, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor3_obj(1.1, 2.2, 3.3));

    QEXTBoundConstMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB3_obj(true, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB3);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB3_obj(true, 2, 3));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB3_obj(false, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB3_obj(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB3_obj(false, 2.2, 3.3));

    QEXTBoundConstMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor3(1, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction3);
    QVERIFY(0 == intBoundConstMemberBaseFunctor3(1, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor3(1.1, 2.2, 3.3));

    QEXTBoundConstMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB3(true, 2, 3);
    QEXTBoundConstMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB3);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB3(true, 2, 3));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB3(false, 2, 3));
    QEXTBoundConstMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB3(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB3(false, 2.2, 3.3));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction3);
    voidBoundConstMemberBaseFunctor(1, 2, 3);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction3);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction3);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB3);
    voidBoundConstMemberBaseFunctorB(true, 2, 3);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB3);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB3);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith3Arg()
{
    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor3_(1, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundVolatileMemberBaseFunctor3_(1, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctor3_(1.1, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB3_(true, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundVolatileMemberBaseFunctorB3_(true, 2, 3));
    QVERIFY(2 * 3 == intBoundVolatileMemberBaseFunctorB3_(false, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctorB3_(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundVolatileMemberBaseFunctorB3_(false, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor3_obj(1, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundVolatileMemberBaseFunctor3_obj(1, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctor3_obj(1.1, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB3_obj(true, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundVolatileMemberBaseFunctorB3_obj(true, 2, 3));
    QVERIFY(2 * 3 == intBoundVolatileMemberBaseFunctorB3_obj(false, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctorB3_obj(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundVolatileMemberBaseFunctorB3_obj(false, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor3(1, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundVolatileMemberBaseFunctor3(1, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctor3(1.1, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB3(true, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundVolatileMemberBaseFunctorB3(true, 2, 3));
    QVERIFY(2 * 3 == intBoundVolatileMemberBaseFunctorB3(false, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctorB3(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundVolatileMemberBaseFunctorB3(false, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundVolatileMemberBaseFunctor(1, 2, 3));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundVolatileMemberBaseFunctorB(false, 2, 3));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith3Arg()
{
    Member member;

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor3_(1, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction3);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor3_(1, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor3_(1.1, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB3_(true, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB3_(true, 2, 3));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB3_(false, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB3_(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB3_(false, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor3_obj(1, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction3);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor3_obj(1, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor3_obj(1.1, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB3_obj(true, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB3_obj(true, 2, 3));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB3_obj(false, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB3_obj(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB3_obj(false, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor3(1, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction3);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor3(1, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor3(1.1, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB3(true, 2, 3);
    QEXTBoundVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB3(true, 2, 3));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB3(false, 2, 3));
    QEXTBoundVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB3(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB3(false, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction3);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction3);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction3);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB3);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB3);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB3);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith3Arg()
{
    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor3_(1, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstVolatileMemberBaseFunctor3_(1, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctor3_(1.1, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB3_(true, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundConstVolatileMemberBaseFunctorB3_(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstVolatileMemberBaseFunctorB3_(false, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctorB3_(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstVolatileMemberBaseFunctorB3_(false, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor3_obj(1, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstVolatileMemberBaseFunctor3_obj(1, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctor3_obj(1.1, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB3_obj(true, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundConstVolatileMemberBaseFunctorB3_obj(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstVolatileMemberBaseFunctorB3_obj(false, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctorB3_obj(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstVolatileMemberBaseFunctorB3_obj(false, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor3(1, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstVolatileMemberBaseFunctor3(1, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(&memberBase, &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctor3(1.1, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB3(true, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundConstVolatileMemberBaseFunctorB3(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstVolatileMemberBaseFunctorB3(false, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(&memberBase, &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctorB3(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstVolatileMemberBaseFunctorB3(false, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction3);
    QVERIFY(1 + 2 + 3 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(2 + 3 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith3Arg()
{
    Member member;

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor3_(1, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor3_(1, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor3_(1.1, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB3_(true, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB3_(true, 2, 3));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB3_(false, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB3_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB3_(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB3_(false, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor3_obj(1, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor3_obj(1, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor3_obj(1.1, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB3_obj(true, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB3_obj(true, 2, 3));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB3_obj(false, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB3_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB3_obj(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB3_obj(false, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor3(1, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor3(1, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor3(1.1, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor3<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB3(true, 2, 3);
    QEXTBoundConstVolatileMemberFunctor3<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB3(true, 2, 3));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB3(false, 2, 3));
    QEXTBoundConstVolatileMemberFunctor3<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB3 = qextMemberFunctor3(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB3(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB3(false, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction3);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction3);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction3);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB3);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB3);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB3);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3));
}

void QEXTMemberFunctorTest::testFunctorWith4Arg()
{
    MemberBase memberBase;

    QEXTMemberFunctor4<void, MemberBase, int, int, int, int> voidMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::voidFunction4);
    voidMemberBaseFunctor4_(&memberBase, 1, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, int, int, int, int> intMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intMemberBaseFunctor4_(&memberBase, 1, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleMemberBaseFunctor4_(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTMemberFunctor4<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::voidFunctionB4);
    voidMemberBaseFunctorB4_(&memberBase, true, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intMemberBaseFunctorB4_(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intMemberBaseFunctorB4_(&memberBase, false, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleMemberBaseFunctorB4_(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleMemberBaseFunctorB4_(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTMemberFunctor4<void, MemberBase, int, int, int, int> voidMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction4);
    voidMemberBaseFunctor4_obj(&memberBase, 1, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, int, int, int, int> intMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intMemberBaseFunctor4_obj(&memberBase, 1, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleMemberBaseFunctor4_obj(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTMemberFunctor4<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB4);
    voidMemberBaseFunctorB4_obj(&memberBase, true, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intMemberBaseFunctorB4_obj(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intMemberBaseFunctorB4_obj(&memberBase, false, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleMemberBaseFunctorB4_obj(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleMemberBaseFunctorB4_obj(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTMemberFunctor4<void, MemberBase, int, int, int, int> voidMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::voidFunction4);
    voidMemberBaseFunctor4(&memberBase, 1, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, int, int, int, int> intMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intMemberBaseFunctor4(&memberBase, 1, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleMemberBaseFunctor4(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTMemberFunctor4<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::voidFunctionB4);
    voidMemberBaseFunctorB4(&memberBase, true, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intMemberBaseFunctorB4(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intMemberBaseFunctorB4(&memberBase, false, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleMemberBaseFunctorB4(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleMemberBaseFunctorB4(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTMemberFunctor<void, MemberBase, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction4);
    voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB4);
    voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith4Arg()
{
    Member member;

    QEXTMemberFunctor4<void, MemberBase, int, int, int, int> voidMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::voidFunction4);
    voidMemberBaseFunctor4_(&member, 1, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, int, int, int, int> intMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::intFunction4);
    QVERIFY(0 == intMemberBaseFunctor4_(&member, 1, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::doubleFunction4);
    QVERIFY(0 == doubleMemberBaseFunctor4_(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTMemberFunctor4<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::voidFunctionB4);
    voidMemberBaseFunctorB4_(&member, true, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::intFunctionB4);
    QVERIFY(1 == intMemberBaseFunctorB4_(&member, true, 2, 3, 4));
    QVERIFY(0 == intMemberBaseFunctorB4_(&member, false, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleMemberBaseFunctorB4_(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleMemberBaseFunctorB4_(&member, false, 2.2, 3.3, 4.4));

    QEXTMemberFunctor4<void, MemberBase, int, int, int, int> voidMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction4);
    voidMemberBaseFunctor4_obj(&member, 1, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, int, int, int, int> intMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction4);
    QVERIFY(0 == intMemberBaseFunctor4_obj(&member, 1, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction4);
    QVERIFY(0 == doubleMemberBaseFunctor4_obj(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTMemberFunctor4<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB4);
    voidMemberBaseFunctorB4_obj(&member, true, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB4);
    QVERIFY(1 == intMemberBaseFunctorB4_obj(&member, true, 2, 3, 4));
    QVERIFY(0 == intMemberBaseFunctorB4_obj(&member, false, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleMemberBaseFunctorB4_obj(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleMemberBaseFunctorB4_obj(&member, false, 2.2, 3.3, 4.4));

    QEXTMemberFunctor4<void, MemberBase, int, int, int, int> voidMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::voidFunction4);
    voidMemberBaseFunctor4(&member, 1, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, int, int, int, int> intMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::intFunction4);
    QVERIFY(0 == intMemberBaseFunctor4(&member, 1, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::doubleFunction4);
    QVERIFY(0 == doubleMemberBaseFunctor4(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTMemberFunctor4<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::voidFunctionB4);
    voidMemberBaseFunctorB4(&member, true, 2, 3, 4);
    QEXTMemberFunctor4<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::intFunctionB4);
    QVERIFY(1 == intMemberBaseFunctorB4(&member, true, 2, 3, 4));
    QVERIFY(0 == intMemberBaseFunctorB4(&member, false, 2, 3, 4));
    QEXTMemberFunctor4<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleMemberBaseFunctorB4(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleMemberBaseFunctorB4(&member, false, 2.2, 3.3, 4.4));

    QEXTMemberFunctor<void, MemberBase, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction4);
    voidMemberBaseFunctor(&member, 1, 2, 3, 4);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction4);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction4);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB4);
    voidMemberBaseFunctorB(&member, true, 2, 3, 4);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB4);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testConstFunctorWith4Arg()
{
    MemberBase memberBase;

    QEXTConstMemberFunctor4<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::voidConstFunction4);
    voidConstMemberBaseFunctor4_(&memberBase, 1, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intConstMemberBaseFunctor4_(&memberBase, 1, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctor4_(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::voidConstFunctionB4);
    voidConstMemberBaseFunctorB4_(&memberBase, true, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intConstMemberBaseFunctorB4_(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intConstMemberBaseFunctorB4_(&memberBase, false, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctorB4_(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleConstMemberBaseFunctorB4_(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor4<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction4);
    voidConstMemberBaseFunctor4_obj(&memberBase, 1, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intConstMemberBaseFunctor4_obj(&memberBase, 1, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctor4_obj(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB4);
    voidConstMemberBaseFunctorB4_obj(&memberBase, true, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intConstMemberBaseFunctorB4_obj(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intConstMemberBaseFunctorB4_obj(&memberBase, false, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctorB4_obj(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleConstMemberBaseFunctorB4_obj(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor4<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::voidConstFunction4);
    voidConstMemberBaseFunctor4(&memberBase, 1, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intConstMemberBaseFunctor4(&memberBase, 1, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctor4(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::voidConstFunctionB4);
    voidConstMemberBaseFunctorB4(&memberBase, true, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intConstMemberBaseFunctorB4(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intConstMemberBaseFunctorB4(&memberBase, false, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctorB4(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleConstMemberBaseFunctorB4(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction4);
    voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB4);
    voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith4Arg()
{
    Member member;

    QEXTConstMemberFunctor4<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::voidConstFunction4);
    voidConstMemberBaseFunctor4_(&member, 1, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::intConstFunction4);
    QVERIFY(0 == intConstMemberBaseFunctor4_(&member, 1, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleConstMemberBaseFunctor4_(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::voidConstFunctionB4);
    voidConstMemberBaseFunctorB4_(&member, true, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::intConstFunctionB4);
    QVERIFY(1 == intConstMemberBaseFunctorB4_(&member, true, 2, 3, 4));
    QVERIFY(0 == intConstMemberBaseFunctorB4_(&member, false, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleConstMemberBaseFunctorB4_(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleConstMemberBaseFunctorB4_(&member, false, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor4<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction4);
    voidConstMemberBaseFunctor4_obj(&member, 1, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction4);
    QVERIFY(0 == intConstMemberBaseFunctor4_obj(&member, 1, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleConstMemberBaseFunctor4_obj(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB4);
    voidConstMemberBaseFunctorB4_obj(&member, true, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB4);
    QVERIFY(1 == intConstMemberBaseFunctorB4_obj(&member, true, 2, 3, 4));
    QVERIFY(0 == intConstMemberBaseFunctorB4_obj(&member, false, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleConstMemberBaseFunctorB4_obj(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleConstMemberBaseFunctorB4_obj(&member, false, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor4<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::voidConstFunction4);
    voidConstMemberBaseFunctor4(&member, 1, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::intConstFunction4);
    QVERIFY(0 == intConstMemberBaseFunctor4(&member, 1, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleConstMemberBaseFunctor4(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::voidConstFunctionB4);
    voidConstMemberBaseFunctorB4(&member, true, 2, 3, 4);
    QEXTConstMemberFunctor4<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::intConstFunctionB4);
    QVERIFY(1 == intConstMemberBaseFunctorB4(&member, true, 2, 3, 4));
    QVERIFY(0 == intConstMemberBaseFunctorB4(&member, false, 2, 3, 4));
    QEXTConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleConstMemberBaseFunctorB4(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleConstMemberBaseFunctorB4(&member, false, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction4);
    voidConstMemberBaseFunctor(&member, 1, 2, 3, 4);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction4);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB4);
    voidConstMemberBaseFunctorB(&member, true, 2, 3, 4);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB4);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith4Arg()
{
    MemberBase memberBase;

    QEXTVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::voidVolatileFunction4);
    voidVolatileMemberBaseFunctor4_(&memberBase, 1, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intVolatileMemberBaseFunctor4_(&memberBase, 1, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctor4_(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB4);
    voidVolatileMemberBaseFunctorB4_(&memberBase, true, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intVolatileMemberBaseFunctorB4_(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intVolatileMemberBaseFunctorB4_(&memberBase, false, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctorB4_(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleVolatileMemberBaseFunctorB4_(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction4);
    voidVolatileMemberBaseFunctor4_obj(&memberBase, 1, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intVolatileMemberBaseFunctor4_obj(&memberBase, 1, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctor4_obj(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB4);
    voidVolatileMemberBaseFunctorB4_obj(&memberBase, true, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intVolatileMemberBaseFunctorB4_obj(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intVolatileMemberBaseFunctorB4_obj(&memberBase, false, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctorB4_obj(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleVolatileMemberBaseFunctorB4_obj(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::voidVolatileFunction4);
    voidVolatileMemberBaseFunctor4(&memberBase, 1, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intVolatileMemberBaseFunctor4(&memberBase, 1, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctor4(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::voidVolatileFunctionB4);
    voidVolatileMemberBaseFunctorB4(&memberBase, true, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intVolatileMemberBaseFunctorB4(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intVolatileMemberBaseFunctorB4(&memberBase, false, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctorB4(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleVolatileMemberBaseFunctorB4(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction4);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB4);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith4Arg()
{
    Member member;

    QEXTVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::voidVolatileFunction4);
    voidVolatileMemberBaseFunctor4_(&member, 1, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::intVolatileFunction4);
    QVERIFY(0 == intVolatileMemberBaseFunctor4_(&member, 1, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor4_(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB4);
    voidVolatileMemberBaseFunctorB4_(&member, true, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intVolatileMemberBaseFunctorB4_(&member, true, 2, 3, 4));
    QVERIFY(0 == intVolatileMemberBaseFunctorB4_(&member, false, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB4_(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB4_(&member, false, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction4);
    voidVolatileMemberBaseFunctor4_obj(&member, 1, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction4);
    QVERIFY(0 == intVolatileMemberBaseFunctor4_obj(&member, 1, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor4_obj(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB4);
    voidVolatileMemberBaseFunctorB4_obj(&member, true, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intVolatileMemberBaseFunctorB4_obj(&member, true, 2, 3, 4));
    QVERIFY(0 == intVolatileMemberBaseFunctorB4_obj(&member, false, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB4_obj(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB4_obj(&member, false, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::voidVolatileFunction4);
    voidVolatileMemberBaseFunctor4(&member, 1, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::intVolatileFunction4);
    QVERIFY(0 == intVolatileMemberBaseFunctor4(&member, 1, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor4(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::voidVolatileFunctionB4);
    voidVolatileMemberBaseFunctorB4(&member, true, 2, 3, 4);
    QEXTVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intVolatileMemberBaseFunctorB4(&member, true, 2, 3, 4));
    QVERIFY(0 == intVolatileMemberBaseFunctorB4(&member, false, 2, 3, 4));
    QEXTVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB4(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB4(&member, false, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction4);
    voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction4);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB4);
    voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith4Arg()
{
    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction4);
    voidConstVolatileMemberBaseFunctor4_(&memberBase, 1, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intConstVolatileMemberBaseFunctor4_(&memberBase, 1, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctor4_(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB4);
    voidConstVolatileMemberBaseFunctorB4_(&memberBase, true, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intConstVolatileMemberBaseFunctorB4_(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intConstVolatileMemberBaseFunctorB4_(&memberBase, false, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctorB4_(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleConstVolatileMemberBaseFunctorB4_(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction4);
    voidConstVolatileMemberBaseFunctor4_obj(&memberBase, 1, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intConstVolatileMemberBaseFunctor4_obj(&memberBase, 1, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctor4_obj(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB4);
    voidConstVolatileMemberBaseFunctorB4_obj(&memberBase, true, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intConstVolatileMemberBaseFunctorB4_obj(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intConstVolatileMemberBaseFunctorB4_obj(&memberBase, false, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctorB4_obj(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleConstVolatileMemberBaseFunctorB4_obj(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::voidConstVolatileFunction4);
    voidConstVolatileMemberBaseFunctor4(&memberBase, 1, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intConstVolatileMemberBaseFunctor4(&memberBase, 1, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctor4(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::voidConstVolatileFunctionB4);
    voidConstVolatileMemberBaseFunctorB4(&memberBase, true, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intConstVolatileMemberBaseFunctorB4(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intConstVolatileMemberBaseFunctorB4(&memberBase, false, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctorB4(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleConstVolatileMemberBaseFunctorB4(&memberBase, false, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction4);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB4);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith4Arg()
{
    Member member;

    QEXTConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction4);
    voidConstVolatileMemberBaseFunctor4_(&member, 1, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor4_(&member, 1, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor4_(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB4);
    voidConstVolatileMemberBaseFunctorB4_(&member, true, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB4_(&member, true, 2, 3, 4));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB4_(&member, false, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB4_(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB4_(&member, false, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction4);
    voidConstVolatileMemberBaseFunctor4_obj(&member, 1, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor4_obj(&member, 1, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor4_obj(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB4);
    voidConstVolatileMemberBaseFunctorB4_obj(&member, true, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB4_obj(&member, true, 2, 3, 4));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB4_obj(&member, false, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB4_obj(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB4_obj(&member, false, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::voidConstVolatileFunction4);
    voidConstVolatileMemberBaseFunctor4(&member, 1, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor4(&member, 1, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(&MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor4(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::voidConstVolatileFunctionB4);
    voidConstVolatileMemberBaseFunctorB4(&member, true, 2, 3, 4);
    QEXTConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB4(&member, true, 2, 3, 4));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB4(&member, false, 2, 3, 4));
    QEXTConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB4(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB4(&member, false, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction4);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB4);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testBoundFunctorWith4Arg()
{
    MemberBase memberBase;

    QEXTBoundMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor4_(1, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundMemberBaseFunctor4_(1, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctor4_(1.1, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB4_(true, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundMemberBaseFunctorB4_(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundMemberBaseFunctorB4_(false, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctorB4_(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundMemberBaseFunctorB4_(false, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor4_obj(1, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundMemberBaseFunctor4_obj(1, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctor4_obj(1.1, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB4_obj(true, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundMemberBaseFunctorB4_obj(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundMemberBaseFunctorB4_obj(false, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctorB4_obj(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundMemberBaseFunctorB4_obj(false, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor4(1, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundMemberBaseFunctor4(1, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctor4(1.1, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB4(true, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundMemberBaseFunctorB4(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundMemberBaseFunctorB4(false, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctorB4(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundMemberBaseFunctorB4(false, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor(1, 2, 3, 4);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith4Arg()
{
    Member member;

    QEXTBoundMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor4_(1, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction4);
    QVERIFY(0 == intBoundMemberBaseFunctor4_(1, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction4);
    QVERIFY(0 == doubleBoundMemberBaseFunctor4_(1.1, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB4_(true, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB4);
    QVERIFY(1 == intBoundMemberBaseFunctorB4_(true, 2, 3, 4));
    QVERIFY(0 == intBoundMemberBaseFunctorB4_(false, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB4_(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB4_(false, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor4_obj(1, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction4);
    QVERIFY(0 == intBoundMemberBaseFunctor4_obj(1, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction4);
    QVERIFY(0 == doubleBoundMemberBaseFunctor4_obj(1.1, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB4_obj(true, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB4);
    QVERIFY(1 == intBoundMemberBaseFunctorB4_obj(true, 2, 3, 4));
    QVERIFY(0 == intBoundMemberBaseFunctorB4_obj(false, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB4_obj(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB4_obj(false, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor4(1, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction4);
    QVERIFY(0 == intBoundMemberBaseFunctor4(1, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction4);
    QVERIFY(0 == doubleBoundMemberBaseFunctor4(1.1, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB4(true, 2, 3, 4);
    QEXTBoundMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB4);
    QVERIFY(1 == intBoundMemberBaseFunctorB4(true, 2, 3, 4));
    QVERIFY(0 == intBoundMemberBaseFunctorB4(false, 2, 3, 4));
    QEXTBoundMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB4(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB4(false, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction4);
    voidBoundMemberBaseFunctor(1, 2, 3, 4);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction4);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction4);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB4);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB4);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB4);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith4Arg()
{
    MemberBase memberBase;

    QEXTBoundConstMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor4_(1, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstMemberBaseFunctor4_(1, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctor4_(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB4_(true, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstMemberBaseFunctorB4_(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstMemberBaseFunctorB4_(false, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctorB4_(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstMemberBaseFunctorB4_(false, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor4_obj(1, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstMemberBaseFunctor4_obj(1, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctor4_obj(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB4_obj(true, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstMemberBaseFunctorB4_obj(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstMemberBaseFunctorB4_obj(false, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctorB4_obj(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstMemberBaseFunctorB4_obj(false, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor4(1, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstMemberBaseFunctor4(1, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctor4(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB4(true, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstMemberBaseFunctorB4(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstMemberBaseFunctorB4(false, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctorB4(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstMemberBaseFunctorB4(false, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith4Arg()
{
    Member member;

    QEXTBoundConstMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor4_(1, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction4);
    QVERIFY(0 == intBoundConstMemberBaseFunctor4_(1, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor4_(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB4_(true, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB4);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB4_(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB4_(false, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB4_(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB4_(false, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor4_obj(1, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction4);
    QVERIFY(0 == intBoundConstMemberBaseFunctor4_obj(1, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor4_obj(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB4_obj(true, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB4);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB4_obj(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB4_obj(false, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB4_obj(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB4_obj(false, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor4(1, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction4);
    QVERIFY(0 == intBoundConstMemberBaseFunctor4(1, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor4(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB4(true, 2, 3, 4);
    QEXTBoundConstMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB4);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB4(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB4(false, 2, 3, 4));
    QEXTBoundConstMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB4(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB4(false, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction4);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction4);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction4);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB4);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB4);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB4);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith4Arg()
{
    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor4_(1, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundVolatileMemberBaseFunctor4_(1, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctor4_(1.1, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB4_(true, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundVolatileMemberBaseFunctorB4_(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundVolatileMemberBaseFunctorB4_(false, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctorB4_(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundVolatileMemberBaseFunctorB4_(false, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor4_obj(1, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundVolatileMemberBaseFunctor4_obj(1, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctor4_obj(1.1, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB4_obj(true, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundVolatileMemberBaseFunctorB4_obj(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundVolatileMemberBaseFunctorB4_obj(false, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctorB4_obj(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundVolatileMemberBaseFunctorB4_obj(false, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor4(1, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundVolatileMemberBaseFunctor4(1, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctor4(1.1, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB4(true, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundVolatileMemberBaseFunctorB4(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundVolatileMemberBaseFunctorB4(false, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctorB4(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundVolatileMemberBaseFunctorB4(false, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith4Arg()
{
    Member member;

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor4_(1, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction4);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor4_(1, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor4_(1.1, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB4_(true, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB4_(true, 2, 3, 4));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB4_(false, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB4_(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB4_(false, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor4_obj(1, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction4);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor4_obj(1, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor4_obj(1.1, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB4_obj(true, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB4_obj(true, 2, 3, 4));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB4_obj(false, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB4_obj(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB4_obj(false, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor4(1, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction4);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor4(1, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor4(1.1, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB4(true, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB4(true, 2, 3, 4));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB4(false, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB4(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB4(false, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction4);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction4);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction4);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB4);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB4);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB4);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith4Arg()
{
    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor4_(1, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctor4_(1, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctor4_(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB4_(true, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctorB4_(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstVolatileMemberBaseFunctorB4_(false, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctorB4_(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstVolatileMemberBaseFunctorB4_(false, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor4_obj(1, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctor4_obj(1, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctor4_obj(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB4_obj(true, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctorB4_obj(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstVolatileMemberBaseFunctorB4_obj(false, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctorB4_obj(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstVolatileMemberBaseFunctorB4_obj(false, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor4(1, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctor4(1, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(&memberBase, &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctor4(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB4(true, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctorB4(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstVolatileMemberBaseFunctorB4(false, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(&memberBase, &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctorB4(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstVolatileMemberBaseFunctorB4(false, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(2 + 3 + 4 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith4Arg()
{
    Member member;

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor4_(1, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor4_(1, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor4_(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB4_(true, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB4_(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB4_(false, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB4_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB4_(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB4_(false, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor4_obj(1, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor4_obj(1, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor4_obj(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB4_obj(true, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB4_obj(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB4_obj(false, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB4_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB4_obj(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB4_obj(false, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor4(1, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor4(1, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor4(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor4<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB4(true, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor4<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB4(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB4(false, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor4<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB4 = qextMemberFunctor4(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB4(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB4(false, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction4);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction4);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction4);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB4);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB4);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB4);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4));
}

void QEXTMemberFunctorTest::testFunctorWith5Arg()
{
    MemberBase memberBase;

    QEXTMemberFunctor5<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::voidFunction5);
    voidMemberBaseFunctor5_(&memberBase, 1, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intMemberBaseFunctor5_(&memberBase, 1, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctor5_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::voidFunctionB5);
    voidMemberBaseFunctorB5_(&memberBase, true, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intMemberBaseFunctorB5_(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intMemberBaseFunctorB5_(&memberBase, false, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctorB5_(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleMemberBaseFunctorB5_(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor5<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction5);
    voidMemberBaseFunctor5_obj(&memberBase, 1, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intMemberBaseFunctor5_obj(&memberBase, 1, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctor5_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB5);
    voidMemberBaseFunctorB5_obj(&memberBase, true, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intMemberBaseFunctorB5_obj(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intMemberBaseFunctorB5_obj(&memberBase, false, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctorB5_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleMemberBaseFunctorB5_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor5<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::voidFunction5);
    voidMemberBaseFunctor5(&memberBase, 1, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intMemberBaseFunctor5(&memberBase, 1, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctor5(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::voidFunctionB5);
    voidMemberBaseFunctorB5(&memberBase, true, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intMemberBaseFunctorB5(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intMemberBaseFunctorB5(&memberBase, false, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctorB5(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleMemberBaseFunctorB5(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction5);
    voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB5);
    voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith5Arg()
{
    Member member;

    QEXTMemberFunctor5<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::voidFunction5);
    voidMemberBaseFunctor5_(&member, 1, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::intFunction5);
    QVERIFY(0 == intMemberBaseFunctor5_(&member, 1, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::doubleFunction5);
    QVERIFY(0 == doubleMemberBaseFunctor5_(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::voidFunctionB5);
    voidMemberBaseFunctorB5_(&member, true, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::intFunctionB5);
    QVERIFY(1 == intMemberBaseFunctorB5_(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intMemberBaseFunctorB5_(&member, false, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleMemberBaseFunctorB5_(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleMemberBaseFunctorB5_(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor5<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction5);
    voidMemberBaseFunctor5_obj(&member, 1, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction5);
    QVERIFY(0 == intMemberBaseFunctor5_obj(&member, 1, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction5);
    QVERIFY(0 == doubleMemberBaseFunctor5_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB5);
    voidMemberBaseFunctorB5_obj(&member, true, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB5);
    QVERIFY(1 == intMemberBaseFunctorB5_obj(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intMemberBaseFunctorB5_obj(&member, false, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleMemberBaseFunctorB5_obj(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleMemberBaseFunctorB5_obj(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor5<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::voidFunction5);
    voidMemberBaseFunctor5(&member, 1, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::intFunction5);
    QVERIFY(0 == intMemberBaseFunctor5(&member, 1, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::doubleFunction5);
    QVERIFY(0 == doubleMemberBaseFunctor5(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::voidFunctionB5);
    voidMemberBaseFunctorB5(&member, true, 2, 3, 4, 5);
    QEXTMemberFunctor5<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::intFunctionB5);
    QVERIFY(1 == intMemberBaseFunctorB5(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intMemberBaseFunctorB5(&member, false, 2, 3, 4, 5));
    QEXTMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleMemberBaseFunctorB5(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleMemberBaseFunctorB5(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction5);
    voidMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction5);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction5);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB5);
    voidMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB5);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testConstFunctorWith5Arg()
{
    MemberBase memberBase;

    QEXTConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::voidConstFunction5);
    voidConstMemberBaseFunctor5_(&memberBase, 1, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intConstMemberBaseFunctor5_(&memberBase, 1, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctor5_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::voidConstFunctionB5);
    voidConstMemberBaseFunctorB5_(&memberBase, true, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intConstMemberBaseFunctorB5_(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intConstMemberBaseFunctorB5_(&memberBase, false, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctorB5_(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleConstMemberBaseFunctorB5_(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction5);
    voidConstMemberBaseFunctor5_obj(&memberBase, 1, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intConstMemberBaseFunctor5_obj(&memberBase, 1, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctor5_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB5);
    voidConstMemberBaseFunctorB5_obj(&memberBase, true, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intConstMemberBaseFunctorB5_obj(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intConstMemberBaseFunctorB5_obj(&memberBase, false, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctorB5_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleConstMemberBaseFunctorB5_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::voidConstFunction5);
    voidConstMemberBaseFunctor5(&memberBase, 1, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intConstMemberBaseFunctor5(&memberBase, 1, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctor5(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::voidConstFunctionB5);
    voidConstMemberBaseFunctorB5(&memberBase, true, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intConstMemberBaseFunctorB5(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intConstMemberBaseFunctorB5(&memberBase, false, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctorB5(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleConstMemberBaseFunctorB5(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction5);
    voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB5);
    voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith5Arg()
{
    Member member;

    QEXTConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::voidConstFunction5);
    voidConstMemberBaseFunctor5_(&member, 1, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::intConstFunction5);
    QVERIFY(0 == intConstMemberBaseFunctor5_(&member, 1, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleConstMemberBaseFunctor5_(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::voidConstFunctionB5);
    voidConstMemberBaseFunctorB5_(&member, true, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::intConstFunctionB5);
    QVERIFY(1 == intConstMemberBaseFunctorB5_(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intConstMemberBaseFunctorB5_(&member, false, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleConstMemberBaseFunctorB5_(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleConstMemberBaseFunctorB5_(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction5);
    voidConstMemberBaseFunctor5_obj(&member, 1, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction5);
    QVERIFY(0 == intConstMemberBaseFunctor5_obj(&member, 1, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleConstMemberBaseFunctor5_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB5);
    voidConstMemberBaseFunctorB5_obj(&member, true, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB5);
    QVERIFY(1 == intConstMemberBaseFunctorB5_obj(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intConstMemberBaseFunctorB5_obj(&member, false, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleConstMemberBaseFunctorB5_obj(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleConstMemberBaseFunctorB5_obj(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::voidConstFunction5);
    voidConstMemberBaseFunctor5(&member, 1, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::intConstFunction5);
    QVERIFY(0 == intConstMemberBaseFunctor5(&member, 1, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleConstMemberBaseFunctor5(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::voidConstFunctionB5);
    voidConstMemberBaseFunctorB5(&member, true, 2, 3, 4, 5);
    QEXTConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::intConstFunctionB5);
    QVERIFY(1 == intConstMemberBaseFunctorB5(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intConstMemberBaseFunctorB5(&member, false, 2, 3, 4, 5));
    QEXTConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleConstMemberBaseFunctorB5(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleConstMemberBaseFunctorB5(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction5);
    voidConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction5);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB5);
    voidConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB5);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith5Arg()
{
    MemberBase memberBase;

    QEXTVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::voidVolatileFunction5);
    voidVolatileMemberBaseFunctor5_(&memberBase, 1, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intVolatileMemberBaseFunctor5_(&memberBase, 1, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctor5_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB5);
    voidVolatileMemberBaseFunctorB5_(&memberBase, true, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intVolatileMemberBaseFunctorB5_(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intVolatileMemberBaseFunctorB5_(&memberBase, false, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctorB5_(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleVolatileMemberBaseFunctorB5_(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction5);
    voidVolatileMemberBaseFunctor5_obj(&memberBase, 1, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intVolatileMemberBaseFunctor5_obj(&memberBase, 1, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctor5_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB5);
    voidVolatileMemberBaseFunctorB5_obj(&memberBase, true, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intVolatileMemberBaseFunctorB5_obj(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intVolatileMemberBaseFunctorB5_obj(&memberBase, false, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctorB5_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleVolatileMemberBaseFunctorB5_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::voidVolatileFunction5);
    voidVolatileMemberBaseFunctor5(&memberBase, 1, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intVolatileMemberBaseFunctor5(&memberBase, 1, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctor5(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::voidVolatileFunctionB5);
    voidVolatileMemberBaseFunctorB5(&memberBase, true, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intVolatileMemberBaseFunctorB5(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intVolatileMemberBaseFunctorB5(&memberBase, false, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctorB5(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleVolatileMemberBaseFunctorB5(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction5);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB5);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith5Arg()
{
    Member member;

    QEXTVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::voidVolatileFunction5);
    voidVolatileMemberBaseFunctor5_(&member, 1, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::intVolatileFunction5);
    QVERIFY(0 == intVolatileMemberBaseFunctor5_(&member, 1, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor5_(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB5);
    voidVolatileMemberBaseFunctorB5_(&member, true, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intVolatileMemberBaseFunctorB5_(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intVolatileMemberBaseFunctorB5_(&member, false, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB5_(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB5_(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction5);
    voidVolatileMemberBaseFunctor5_obj(&member, 1, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction5);
    QVERIFY(0 == intVolatileMemberBaseFunctor5_obj(&member, 1, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor5_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB5);
    voidVolatileMemberBaseFunctorB5_obj(&member, true, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intVolatileMemberBaseFunctorB5_obj(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intVolatileMemberBaseFunctorB5_obj(&member, false, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB5_obj(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB5_obj(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::voidVolatileFunction5);
    voidVolatileMemberBaseFunctor5(&member, 1, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::intVolatileFunction5);
    QVERIFY(0 == intVolatileMemberBaseFunctor5(&member, 1, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor5(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::voidVolatileFunctionB5);
    voidVolatileMemberBaseFunctorB5(&member, true, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intVolatileMemberBaseFunctorB5(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intVolatileMemberBaseFunctorB5(&member, false, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB5(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB5(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction5);
    voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction5);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB5);
    voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith5Arg()
{
    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction5);
    voidConstVolatileMemberBaseFunctor5_(&memberBase, 1, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctor5_(&memberBase, 1, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctor5_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB5);
    voidConstVolatileMemberBaseFunctorB5_(&memberBase, true, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctorB5_(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intConstVolatileMemberBaseFunctorB5_(&memberBase, false, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctorB5_(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleConstVolatileMemberBaseFunctorB5_(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction5);
    voidConstVolatileMemberBaseFunctor5_obj(&memberBase, 1, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctor5_obj(&memberBase, 1, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctor5_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB5);
    voidConstVolatileMemberBaseFunctorB5_obj(&memberBase, true, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctorB5_obj(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intConstVolatileMemberBaseFunctorB5_obj(&memberBase, false, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctorB5_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleConstVolatileMemberBaseFunctorB5_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::voidConstVolatileFunction5);
    voidConstVolatileMemberBaseFunctor5(&memberBase, 1, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctor5(&memberBase, 1, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctor5(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::voidConstVolatileFunctionB5);
    voidConstVolatileMemberBaseFunctorB5(&memberBase, true, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctorB5(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intConstVolatileMemberBaseFunctorB5(&memberBase, false, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctorB5(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleConstVolatileMemberBaseFunctorB5(&memberBase, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction5);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB5);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith5Arg()
{
    Member member;

    QEXTConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction5);
    voidConstVolatileMemberBaseFunctor5_(&member, 1, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor5_(&member, 1, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor5_(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB5);
    voidConstVolatileMemberBaseFunctorB5_(&member, true, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB5_(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB5_(&member, false, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB5_(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB5_(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction5);
    voidConstVolatileMemberBaseFunctor5_obj(&member, 1, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor5_obj(&member, 1, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor5_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB5);
    voidConstVolatileMemberBaseFunctorB5_obj(&member, true, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB5_obj(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB5_obj(&member, false, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB5_obj(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB5_obj(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::voidConstVolatileFunction5);
    voidConstVolatileMemberBaseFunctor5(&member, 1, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor5(&member, 1, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(&MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor5(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::voidConstVolatileFunctionB5);
    voidConstVolatileMemberBaseFunctorB5(&member, true, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB5(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB5(&member, false, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB5(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB5(&member, false, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction5);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB5);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testBoundFunctorWith5Arg()
{
    MemberBase memberBase;

    QEXTBoundMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor5_(1, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundMemberBaseFunctor5_(1, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctor5_(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB5_(true, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundMemberBaseFunctorB5_(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundMemberBaseFunctorB5_(false, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctorB5_(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundMemberBaseFunctorB5_(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor5_obj(1, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundMemberBaseFunctor5_obj(1, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctor5_obj(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB5_obj(true, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundMemberBaseFunctorB5_obj(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundMemberBaseFunctorB5_obj(false, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctorB5_obj(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundMemberBaseFunctorB5_obj(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor5(1, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundMemberBaseFunctor5(1, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctor5(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB5(true, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundMemberBaseFunctorB5(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundMemberBaseFunctorB5(false, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctorB5(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundMemberBaseFunctorB5(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith5Arg()
{
    Member member;

    QEXTBoundMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor5_(1, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction5);
    QVERIFY(0 == intBoundMemberBaseFunctor5_(1, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction5);
    QVERIFY(0 == doubleBoundMemberBaseFunctor5_(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB5_(true, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB5);
    QVERIFY(1 == intBoundMemberBaseFunctorB5_(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundMemberBaseFunctorB5_(false, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB5_(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB5_(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor5_obj(1, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction5);
    QVERIFY(0 == intBoundMemberBaseFunctor5_obj(1, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction5);
    QVERIFY(0 == doubleBoundMemberBaseFunctor5_obj(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB5_obj(true, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB5);
    QVERIFY(1 == intBoundMemberBaseFunctorB5_obj(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundMemberBaseFunctorB5_obj(false, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB5_obj(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB5_obj(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor5(1, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction5);
    QVERIFY(0 == intBoundMemberBaseFunctor5(1, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction5);
    QVERIFY(0 == doubleBoundMemberBaseFunctor5(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB5(true, 2, 3, 4, 5);
    QEXTBoundMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB5);
    QVERIFY(1 == intBoundMemberBaseFunctorB5(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundMemberBaseFunctorB5(false, 2, 3, 4, 5));
    QEXTBoundMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB5(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB5(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction5);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction5);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction5);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB5);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB5);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB5);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith5Arg()
{
    MemberBase memberBase;

    QEXTBoundConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor5_(1, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctor5_(1, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctor5_(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB5_(true, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctorB5_(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstMemberBaseFunctorB5_(false, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctorB5_(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstMemberBaseFunctorB5_(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor5_obj(1, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctor5_obj(1, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctor5_obj(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB5_obj(true, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctorB5_obj(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstMemberBaseFunctorB5_obj(false, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctorB5_obj(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstMemberBaseFunctorB5_obj(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor5(1, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctor5(1, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctor5(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB5(true, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctorB5(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstMemberBaseFunctorB5(false, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctorB5(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstMemberBaseFunctorB5(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith5Arg()
{
    Member member;

    QEXTBoundConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor5_(1, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction5);
    QVERIFY(0 == intBoundConstMemberBaseFunctor5_(1, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor5_(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB5_(true, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB5);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB5_(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB5_(false, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB5_(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB5_(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor5_obj(1, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction5);
    QVERIFY(0 == intBoundConstMemberBaseFunctor5_obj(1, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor5_obj(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB5_obj(true, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB5);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB5_obj(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB5_obj(false, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB5_obj(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB5_obj(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor5(1, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction5);
    QVERIFY(0 == intBoundConstMemberBaseFunctor5(1, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor5(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB5(true, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB5);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB5(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB5(false, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB5(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB5(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction5);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction5);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction5);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB5);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB5);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB5);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith5Arg()
{
    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor5_(1, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctor5_(1, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctor5_(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB5_(true, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctorB5_(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundVolatileMemberBaseFunctorB5_(false, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctorB5_(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundVolatileMemberBaseFunctorB5_(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor5_obj(1, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctor5_obj(1, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctor5_obj(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB5_obj(true, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctorB5_obj(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundVolatileMemberBaseFunctorB5_obj(false, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctorB5_obj(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundVolatileMemberBaseFunctorB5_obj(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor5(1, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctor5(1, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctor5(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB5(true, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctorB5(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundVolatileMemberBaseFunctorB5(false, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctorB5(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundVolatileMemberBaseFunctorB5(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith5Arg()
{
    Member member;

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor5_(1, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction5);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor5_(1, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor5_(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB5_(true, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB5_(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB5_(false, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB5_(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB5_(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor5_obj(1, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction5);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor5_obj(1, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor5_obj(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB5_obj(true, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB5_obj(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB5_obj(false, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB5_obj(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB5_obj(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor5(1, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction5);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor5(1, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor5(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB5(true, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB5(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB5(false, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB5(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB5(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction5);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction5);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction5);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB5);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB5);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB5);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith5Arg()
{
    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor5_(1, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctor5_(1, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctor5_(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB5_(true, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctorB5_(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstVolatileMemberBaseFunctorB5_(false, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctorB5_(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstVolatileMemberBaseFunctorB5_(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor5_obj(1, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctor5_obj(1, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctor5_obj(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB5_obj(true, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctorB5_obj(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstVolatileMemberBaseFunctorB5_obj(false, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctorB5_obj(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstVolatileMemberBaseFunctorB5_obj(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor5(1, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctor5(1, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(&memberBase, &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctor5(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB5(true, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctorB5(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstVolatileMemberBaseFunctorB5(false, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(&memberBase, &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctorB5(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstVolatileMemberBaseFunctorB5(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith5Arg()
{
    Member member;

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor5_(1, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor5_(1, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor5_(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB5_(true, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB5_(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB5_(false, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB5_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB5_(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB5_(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor5_obj(1, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor5_obj(1, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor5_obj(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB5_obj(true, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB5_obj(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB5_obj(false, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB5_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB5_obj(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB5_obj(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor5(1, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor5(1, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor5(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor5<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB5(true, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor5<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB5(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB5(false, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor5<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB5 = qextMemberFunctor5(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB5(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB5(false, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction5);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction5);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction5);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB5);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB5);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB5);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTMemberFunctorTest::testFunctorWith6Arg()
{
    MemberBase memberBase;

    QEXTMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::voidFunction6);
    voidMemberBaseFunctor6_(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intMemberBaseFunctor6_(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctor6_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::voidFunctionB6);
    voidMemberBaseFunctorB6_(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intMemberBaseFunctorB6_(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intMemberBaseFunctorB6_(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctorB6_(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleMemberBaseFunctorB6_(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction6);
    voidMemberBaseFunctor6_obj(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intMemberBaseFunctor6_obj(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctor6_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB6);
    voidMemberBaseFunctorB6_obj(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intMemberBaseFunctorB6_obj(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intMemberBaseFunctorB6_obj(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctorB6_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleMemberBaseFunctorB6_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::voidFunction6);
    voidMemberBaseFunctor6(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intMemberBaseFunctor6(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctor6(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::voidFunctionB6);
    voidMemberBaseFunctorB6(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intMemberBaseFunctorB6(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intMemberBaseFunctorB6(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctorB6(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleMemberBaseFunctorB6(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction6);
    voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB6);
    voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith6Arg()
{
    Member member;

    QEXTMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::voidFunction6);
    voidMemberBaseFunctor6_(&member, 1, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::intFunction6);
    QVERIFY(0 == intMemberBaseFunctor6_(&member, 1, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::doubleFunction6);
    QVERIFY(0 == doubleMemberBaseFunctor6_(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::voidFunctionB6);
    voidMemberBaseFunctorB6_(&member, true, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::intFunctionB6);
    QVERIFY(1 == intMemberBaseFunctorB6_(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intMemberBaseFunctorB6_(&member, false, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleMemberBaseFunctorB6_(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleMemberBaseFunctorB6_(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction6);
    voidMemberBaseFunctor6_obj(&member, 1, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction6);
    QVERIFY(0 == intMemberBaseFunctor6_obj(&member, 1, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction6);
    QVERIFY(0 == doubleMemberBaseFunctor6_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB6);
    voidMemberBaseFunctorB6_obj(&member, true, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB6);
    QVERIFY(1 == intMemberBaseFunctorB6_obj(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intMemberBaseFunctorB6_obj(&member, false, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleMemberBaseFunctorB6_obj(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleMemberBaseFunctorB6_obj(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::voidFunction6);
    voidMemberBaseFunctor6(&member, 1, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::intFunction6);
    QVERIFY(0 == intMemberBaseFunctor6(&member, 1, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::doubleFunction6);
    QVERIFY(0 == doubleMemberBaseFunctor6(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::voidFunctionB6);
    voidMemberBaseFunctorB6(&member, true, 2, 3, 4, 5, 6);
    QEXTMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::intFunctionB6);
    QVERIFY(1 == intMemberBaseFunctorB6(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intMemberBaseFunctorB6(&member, false, 2, 3, 4, 5, 6));
    QEXTMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleMemberBaseFunctorB6(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleMemberBaseFunctorB6(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction6);
    voidMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction6);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction6);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB6);
    voidMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB6);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testConstFunctorWith6Arg()
{
    MemberBase memberBase;

    QEXTConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::voidConstFunction6);
    voidConstMemberBaseFunctor6_(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctor6_(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctor6_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::voidConstFunctionB6);
    voidConstMemberBaseFunctorB6_(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctorB6_(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intConstMemberBaseFunctorB6_(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctorB6_(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstMemberBaseFunctorB6_(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction6);
    voidConstMemberBaseFunctor6_obj(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctor6_obj(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctor6_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB6);
    voidConstMemberBaseFunctorB6_obj(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctorB6_obj(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intConstMemberBaseFunctorB6_obj(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctorB6_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstMemberBaseFunctorB6_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::voidConstFunction6);
    voidConstMemberBaseFunctor6(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctor6(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctor6(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::voidConstFunctionB6);
    voidConstMemberBaseFunctorB6(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctorB6(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intConstMemberBaseFunctorB6(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctorB6(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstMemberBaseFunctorB6(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction6);
    voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB6);
    voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith6Arg()
{
    Member member;

    QEXTConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::voidConstFunction6);
    voidConstMemberBaseFunctor6_(&member, 1, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::intConstFunction6);
    QVERIFY(0 == intConstMemberBaseFunctor6_(&member, 1, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleConstMemberBaseFunctor6_(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::voidConstFunctionB6);
    voidConstMemberBaseFunctorB6_(&member, true, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::intConstFunctionB6);
    QVERIFY(1 == intConstMemberBaseFunctorB6_(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intConstMemberBaseFunctorB6_(&member, false, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleConstMemberBaseFunctorB6_(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleConstMemberBaseFunctorB6_(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction6);
    voidConstMemberBaseFunctor6_obj(&member, 1, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction6);
    QVERIFY(0 == intConstMemberBaseFunctor6_obj(&member, 1, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleConstMemberBaseFunctor6_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB6);
    voidConstMemberBaseFunctorB6_obj(&member, true, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB6);
    QVERIFY(1 == intConstMemberBaseFunctorB6_obj(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intConstMemberBaseFunctorB6_obj(&member, false, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleConstMemberBaseFunctorB6_obj(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleConstMemberBaseFunctorB6_obj(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::voidConstFunction6);
    voidConstMemberBaseFunctor6(&member, 1, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::intConstFunction6);
    QVERIFY(0 == intConstMemberBaseFunctor6(&member, 1, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleConstMemberBaseFunctor6(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::voidConstFunctionB6);
    voidConstMemberBaseFunctorB6(&member, true, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::intConstFunctionB6);
    QVERIFY(1 == intConstMemberBaseFunctorB6(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intConstMemberBaseFunctorB6(&member, false, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleConstMemberBaseFunctorB6(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleConstMemberBaseFunctorB6(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction6);
    voidConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction6);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB6);
    voidConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB6);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith6Arg()
{
    MemberBase memberBase;

    QEXTVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::voidVolatileFunction6);
    voidVolatileMemberBaseFunctor6_(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctor6_(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctor6_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB6);
    voidVolatileMemberBaseFunctorB6_(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctorB6_(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intVolatileMemberBaseFunctorB6_(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctorB6_(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleVolatileMemberBaseFunctorB6_(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction6);
    voidVolatileMemberBaseFunctor6_obj(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctor6_obj(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctor6_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB6);
    voidVolatileMemberBaseFunctorB6_obj(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctorB6_obj(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intVolatileMemberBaseFunctorB6_obj(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctorB6_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleVolatileMemberBaseFunctorB6_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::voidVolatileFunction6);
    voidVolatileMemberBaseFunctor6(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctor6(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctor6(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::voidVolatileFunctionB6);
    voidVolatileMemberBaseFunctorB6(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctorB6(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intVolatileMemberBaseFunctorB6(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctorB6(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleVolatileMemberBaseFunctorB6(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction6);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB6);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith6Arg()
{
    Member member;

    QEXTVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::voidVolatileFunction6);
    voidVolatileMemberBaseFunctor6_(&member, 1, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::intVolatileFunction6);
    QVERIFY(0 == intVolatileMemberBaseFunctor6_(&member, 1, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor6_(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB6);
    voidVolatileMemberBaseFunctorB6_(&member, true, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intVolatileMemberBaseFunctorB6_(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intVolatileMemberBaseFunctorB6_(&member, false, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB6_(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB6_(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction6);
    voidVolatileMemberBaseFunctor6_obj(&member, 1, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction6);
    QVERIFY(0 == intVolatileMemberBaseFunctor6_obj(&member, 1, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor6_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB6);
    voidVolatileMemberBaseFunctorB6_obj(&member, true, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intVolatileMemberBaseFunctorB6_obj(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intVolatileMemberBaseFunctorB6_obj(&member, false, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB6_obj(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB6_obj(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::voidVolatileFunction6);
    voidVolatileMemberBaseFunctor6(&member, 1, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::intVolatileFunction6);
    QVERIFY(0 == intVolatileMemberBaseFunctor6(&member, 1, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor6(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::voidVolatileFunctionB6);
    voidVolatileMemberBaseFunctorB6(&member, true, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intVolatileMemberBaseFunctorB6(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intVolatileMemberBaseFunctorB6(&member, false, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB6(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB6(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction6);
    voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction6);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB6);
    voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith6Arg()
{
    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction6);
    voidConstVolatileMemberBaseFunctor6_(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctor6_(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctor6_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB6);
    voidConstVolatileMemberBaseFunctorB6_(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctorB6_(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intConstVolatileMemberBaseFunctorB6_(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctorB6_(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstVolatileMemberBaseFunctorB6_(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction6);
    voidConstVolatileMemberBaseFunctor6_obj(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctor6_obj(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctor6_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB6);
    voidConstVolatileMemberBaseFunctorB6_obj(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctorB6_obj(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intConstVolatileMemberBaseFunctorB6_obj(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctorB6_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstVolatileMemberBaseFunctorB6_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::voidConstVolatileFunction6);
    voidConstVolatileMemberBaseFunctor6(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctor6(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctor6(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::voidConstVolatileFunctionB6);
    voidConstVolatileMemberBaseFunctorB6(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctorB6(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intConstVolatileMemberBaseFunctorB6(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctorB6(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstVolatileMemberBaseFunctorB6(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction6);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB6);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith6Arg()
{
    Member member;

    QEXTConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction6);
    voidConstVolatileMemberBaseFunctor6_(&member, 1, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor6_(&member, 1, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor6_(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB6);
    voidConstVolatileMemberBaseFunctorB6_(&member, true, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB6_(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB6_(&member, false, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB6_(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB6_(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction6);
    voidConstVolatileMemberBaseFunctor6_obj(&member, 1, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor6_obj(&member, 1, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor6_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB6);
    voidConstVolatileMemberBaseFunctorB6_obj(&member, true, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB6_obj(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB6_obj(&member, false, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB6_obj(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB6_obj(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::voidConstVolatileFunction6);
    voidConstVolatileMemberBaseFunctor6(&member, 1, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor6(&member, 1, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(&MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor6(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::voidConstVolatileFunctionB6);
    voidConstVolatileMemberBaseFunctorB6(&member, true, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB6(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB6(&member, false, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB6(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB6(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction6);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB6);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testBoundFunctorWith6Arg()
{
    MemberBase memberBase;

    QEXTBoundMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor6_(1, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctor6_(1, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctor6_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundMemberBaseFunctorB6_(false, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctorB6_(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundMemberBaseFunctorB6_(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctor6_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundMemberBaseFunctorB6_obj(false, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctorB6_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundMemberBaseFunctorB6_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor6(1, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctor6(1, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctor6(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB6(true, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctorB6(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundMemberBaseFunctorB6(false, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctorB6(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundMemberBaseFunctorB6(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith6Arg()
{
    Member member;

    QEXTBoundMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor6_(1, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction6);
    QVERIFY(0 == intBoundMemberBaseFunctor6_(1, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction6);
    QVERIFY(0 == doubleBoundMemberBaseFunctor6_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB6);
    QVERIFY(1 == intBoundMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundMemberBaseFunctorB6_(false, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB6_(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB6_(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction6);
    QVERIFY(0 == intBoundMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction6);
    QVERIFY(0 == doubleBoundMemberBaseFunctor6_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB6);
    QVERIFY(1 == intBoundMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundMemberBaseFunctorB6_obj(false, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB6_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB6_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor6(1, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction6);
    QVERIFY(0 == intBoundMemberBaseFunctor6(1, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction6);
    QVERIFY(0 == doubleBoundMemberBaseFunctor6(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB6(true, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB6);
    QVERIFY(1 == intBoundMemberBaseFunctorB6(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundMemberBaseFunctorB6(false, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB6(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB6(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction6);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction6);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction6);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB6);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB6);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB6);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith6Arg()
{
    MemberBase memberBase;

    QEXTBoundConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor6_(1, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctor6_(1, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctor6_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstMemberBaseFunctorB6_(false, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctorB6_(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstMemberBaseFunctorB6_(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctor6_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstMemberBaseFunctorB6_obj(false, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctorB6_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstMemberBaseFunctorB6_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor6(1, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctor6(1, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctor6(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB6(true, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctorB6(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstMemberBaseFunctorB6(false, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctorB6(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstMemberBaseFunctorB6(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith6Arg()
{
    Member member;

    QEXTBoundConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor6_(1, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction6);
    QVERIFY(0 == intBoundConstMemberBaseFunctor6_(1, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor6_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB6);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB6_(false, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB6_(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB6_(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction6);
    QVERIFY(0== intBoundConstMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor6_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB6);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB6_obj(false, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB6_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB6_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor6(1, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction6);
    QVERIFY(0 == intBoundConstMemberBaseFunctor6(1, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor6(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB6(true, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB6);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB6(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB6(false, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB6(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB6(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction6);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction6);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction6);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB6);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB6);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB6);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith6Arg()
{
    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor6_(1, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctor6_(1, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctor6_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundVolatileMemberBaseFunctorB6_(false, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctorB6_(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundVolatileMemberBaseFunctorB6_(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctor6_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundVolatileMemberBaseFunctorB6_obj(false, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctorB6_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundVolatileMemberBaseFunctorB6_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor6(1, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctor6(1, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctor6(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB6(true, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctorB6(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundVolatileMemberBaseFunctorB6(false, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctorB6(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundVolatileMemberBaseFunctorB6(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith6Arg()
{
    Member member;

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor6_(1, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction6);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor6_(1, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor6_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB6_(false, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB6_(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB6_(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction6);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor6_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB6_obj(false, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB6_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB6_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor6(1, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction6);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor6(1, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor6(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB6(true, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB6(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB6(false, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB6(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB6(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction6);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction6);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction6);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB6);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB6);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB6);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith6Arg()
{
    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor6_(1, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctor6_(1, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctor6_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstVolatileMemberBaseFunctorB6_(false, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctorB6_(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstVolatileMemberBaseFunctorB6_(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctor6_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstVolatileMemberBaseFunctorB6_obj(false, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctorB6_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstVolatileMemberBaseFunctorB6_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor6(1, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctor6(1, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(&memberBase, &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctor6(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB6(true, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctorB6(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstVolatileMemberBaseFunctorB6(false, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(&memberBase, &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctorB6(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstVolatileMemberBaseFunctorB6(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith6Arg()
{
    Member member;

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor6_(1, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor6_(1, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor6_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB6_(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB6_(false, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB6_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB6_(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB6_(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor6_obj(1, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor6_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB6_obj(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB6_obj(false, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB6_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB6_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB6_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor6(1, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor6(1, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor6(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor6<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB6(true, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor6<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB6(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB6(false, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor6<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB6 = qextMemberFunctor6(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB6(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB6(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction6);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction6);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction6);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB6);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB6);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB6);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTMemberFunctorTest::testFunctorWith7Arg()
{
    MemberBase memberBase;

    QEXTMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::voidFunction7);
    voidMemberBaseFunctor7_(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctor7_(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctor7_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::voidFunctionB7);
    voidMemberBaseFunctorB7_(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctorB7_(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intMemberBaseFunctorB7_(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctorB7_(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleMemberBaseFunctorB7_(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction7);
    voidMemberBaseFunctor7_obj(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctor7_obj(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctor7_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB7);
    voidMemberBaseFunctorB7_obj(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctorB7_obj(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intMemberBaseFunctorB7_obj(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctorB7_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleMemberBaseFunctorB7_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::voidFunction7);
    voidMemberBaseFunctor7(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctor7(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctor7(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::voidFunctionB7);
    voidMemberBaseFunctorB7(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctorB7(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intMemberBaseFunctorB7(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctorB7(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleMemberBaseFunctorB7(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction7);
    voidMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB7);
    voidMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith7Arg()
{
    Member member;

    QEXTMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::voidFunction7);
    voidMemberBaseFunctor7_(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::intFunction7);
    QVERIFY(0 == intMemberBaseFunctor7_(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::doubleFunction7);
    QVERIFY(0 == doubleMemberBaseFunctor7_(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::voidFunctionB7);
    voidMemberBaseFunctorB7_(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::intFunctionB7);
    QVERIFY(1 == intMemberBaseFunctorB7_(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intMemberBaseFunctorB7_(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleMemberBaseFunctorB7_(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleMemberBaseFunctorB7_(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction7);
    voidMemberBaseFunctor7_obj(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction7);
    QVERIFY(0 == intMemberBaseFunctor7_obj(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction7);
    QVERIFY(0 == doubleMemberBaseFunctor7_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB7);
    voidMemberBaseFunctorB7_obj(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB7);
    QVERIFY(1 == intMemberBaseFunctorB7_obj(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intMemberBaseFunctorB7_obj(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleMemberBaseFunctorB7_obj(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleMemberBaseFunctorB7_obj(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::voidFunction7);
    voidMemberBaseFunctor7(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::intFunction7);
    QVERIFY(0 == intMemberBaseFunctor7(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::doubleFunction7);
    QVERIFY(0 == doubleMemberBaseFunctor7(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::voidFunctionB7);
    voidMemberBaseFunctorB7(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::intFunctionB7);
    QVERIFY(1 == intMemberBaseFunctorB7(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intMemberBaseFunctorB7(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleMemberBaseFunctorB7(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleMemberBaseFunctorB7(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidFunction7);
    voidMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intMemberBaseFunctor = qextMemberFunctor(&MemberBase::intFunction7);
    QVERIFY(0 == intMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleFunction7);
    QVERIFY(0 == doubleMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidFunctionB7);
    voidMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intFunctionB7);
    QVERIFY(1 == intMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testConstFunctorWith7Arg()
{
    MemberBase memberBase;

    QEXTConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::voidConstFunction7);
    voidConstMemberBaseFunctor7_(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctor7_(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctor7_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::voidConstFunctionB7);
    voidConstMemberBaseFunctorB7_(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctorB7_(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intConstMemberBaseFunctorB7_(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctorB7_(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstMemberBaseFunctorB7_(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction7);
    voidConstMemberBaseFunctor7_obj(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctor7_obj(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctor7_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB7);
    voidConstMemberBaseFunctorB7_obj(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctorB7_obj(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intConstMemberBaseFunctorB7_obj(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctorB7_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstMemberBaseFunctorB7_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::voidConstFunction7);
    voidConstMemberBaseFunctor7(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctor7(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctor7(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::voidConstFunctionB7);
    voidConstMemberBaseFunctorB7(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctorB7(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intConstMemberBaseFunctorB7(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctorB7(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstMemberBaseFunctorB7(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction7);
    voidConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB7);
    voidConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intConstMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intConstMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith7Arg()
{
    Member member;

    QEXTConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::voidConstFunction7);
    voidConstMemberBaseFunctor7_(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::intConstFunction7);
    QVERIFY(0 == intConstMemberBaseFunctor7_(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleConstMemberBaseFunctor7_(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::voidConstFunctionB7);
    voidConstMemberBaseFunctorB7_(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::intConstFunctionB7);
    QVERIFY(1 == intConstMemberBaseFunctorB7_(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intConstMemberBaseFunctorB7_(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleConstMemberBaseFunctorB7_(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleConstMemberBaseFunctorB7_(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction7);
    voidConstMemberBaseFunctor7_obj(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction7);
    QVERIFY(0 == intConstMemberBaseFunctor7_obj(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleConstMemberBaseFunctor7_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB7);
    voidConstMemberBaseFunctorB7_obj(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB7);
    QVERIFY(1 == intConstMemberBaseFunctorB7_obj(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intConstMemberBaseFunctorB7_obj(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleConstMemberBaseFunctorB7_obj(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleConstMemberBaseFunctorB7_obj(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::voidConstFunction7);
    voidConstMemberBaseFunctor7(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::intConstFunction7);
    QVERIFY(0 == intConstMemberBaseFunctor7(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleConstMemberBaseFunctor7(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::voidConstFunctionB7);
    voidConstMemberBaseFunctorB7(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::intConstFunctionB7);
    QVERIFY(1 == intConstMemberBaseFunctorB7(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intConstMemberBaseFunctorB7(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleConstMemberBaseFunctorB7(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleConstMemberBaseFunctorB7(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstFunction7);
    voidConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstFunction7);
    QVERIFY(0 == intConstMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleConstMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstFunctionB7);
    voidConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstFunctionB7);
    QVERIFY(1 == intConstMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intConstMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleConstMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleConstMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testVolatileFunctorWith7Arg()
{
    MemberBase memberBase;

    QEXTVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::voidVolatileFunction7);
    voidVolatileMemberBaseFunctor7_(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctor7_(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctor7_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB7);
    voidVolatileMemberBaseFunctorB7_(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctorB7_(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intVolatileMemberBaseFunctorB7_(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctorB7_(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleVolatileMemberBaseFunctorB7_(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction7);
    voidVolatileMemberBaseFunctor7_obj(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctor7_obj(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctor7_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB7);
    voidVolatileMemberBaseFunctorB7_obj(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctorB7_obj(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intVolatileMemberBaseFunctorB7_obj(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctorB7_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleVolatileMemberBaseFunctorB7_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::voidVolatileFunction7);
    voidVolatileMemberBaseFunctor7(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctor7(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctor7(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::voidVolatileFunctionB7);
    voidVolatileMemberBaseFunctorB7(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctorB7(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intVolatileMemberBaseFunctorB7(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctorB7(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleVolatileMemberBaseFunctorB7(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction7);
    voidVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB7);
    voidVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith7Arg()
{
    Member member;

    QEXTVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::voidVolatileFunction7);
    voidVolatileMemberBaseFunctor7_(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::intVolatileFunction7);
    QVERIFY(0 == intVolatileMemberBaseFunctor7_(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor7_(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::voidVolatileFunctionB7);
    voidVolatileMemberBaseFunctorB7_(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intVolatileMemberBaseFunctorB7_(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intVolatileMemberBaseFunctorB7_(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB7_(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB7_(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction7);
    voidVolatileMemberBaseFunctor7_obj(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction7);
    QVERIFY(0 == intVolatileMemberBaseFunctor7_obj(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor7_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB7);
    voidVolatileMemberBaseFunctorB7_obj(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intVolatileMemberBaseFunctorB7_obj(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intVolatileMemberBaseFunctorB7_obj(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB7_obj(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB7_obj(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::voidVolatileFunction7);
    voidVolatileMemberBaseFunctor7(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::intVolatileFunction7);
    QVERIFY(0 == intVolatileMemberBaseFunctor7(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor7(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::voidVolatileFunctionB7);
    voidVolatileMemberBaseFunctorB7(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intVolatileMemberBaseFunctorB7(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intVolatileMemberBaseFunctorB7(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1 == doubleVolatileMemberBaseFunctorB7(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB7(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidVolatileFunction7);
    voidVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intVolatileFunction7);
    QVERIFY(0 == intVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidVolatileFunctionB7);
    voidVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1== doubleVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith7Arg()
{
    MemberBase memberBase;

    QEXTConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction7);
    voidConstVolatileMemberBaseFunctor7_(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctor7_(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctor7_(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB7);
    voidConstVolatileMemberBaseFunctorB7_(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctorB7_(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intConstVolatileMemberBaseFunctorB7_(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctorB7_(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstVolatileMemberBaseFunctorB7_(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction7);
    voidConstVolatileMemberBaseFunctor7_obj(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctor7_obj(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctor7_obj(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB7);
    voidConstVolatileMemberBaseFunctorB7_obj(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctorB7_obj(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intConstVolatileMemberBaseFunctorB7_obj(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctorB7_obj(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstVolatileMemberBaseFunctorB7_obj(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::voidConstVolatileFunction7);
    voidConstVolatileMemberBaseFunctor7(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctor7(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctor7(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::voidConstVolatileFunctionB7);
    voidConstVolatileMemberBaseFunctorB7(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctorB7(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intConstVolatileMemberBaseFunctorB7(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctorB7(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstVolatileMemberBaseFunctorB7(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction7);
    voidConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctor(&memberBase, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctor(&memberBase, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB7);
    voidConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intConstVolatileMemberBaseFunctorB(&memberBase, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intConstVolatileMemberBaseFunctorB(&memberBase, false, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleConstVolatileMemberBaseFunctorB(&memberBase, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleConstVolatileMemberBaseFunctorB(&memberBase, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith7Arg()
{
    Member member;

    QEXTConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunction7);
    voidConstVolatileMemberBaseFunctor7_(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor7_(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor7_(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB7);
    voidConstVolatileMemberBaseFunctorB7_(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB7_(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB7_(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB7_(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB7_(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction7);
    voidConstVolatileMemberBaseFunctor7_obj(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor7_obj(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor7_obj(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB7);
    voidConstVolatileMemberBaseFunctorB7_obj(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB7_obj(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB7_obj(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB7_obj(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB7_obj(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::voidConstVolatileFunction7);
    voidConstVolatileMemberBaseFunctor7(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor7(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(&MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor7(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::voidConstVolatileFunctionB7);
    voidConstVolatileMemberBaseFunctorB7(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB7(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB7(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB7(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB7(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::voidConstVolatileFunction7);
    voidConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intConstVolatileMemberBaseFunctor(&member, 1, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctor = qextMemberFunctor(&MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctor(&member, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::voidConstVolatileFunctionB7);
    voidConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7);
    QEXTConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intConstVolatileMemberBaseFunctorB(&member, true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intConstVolatileMemberBaseFunctorB(&member, false, 2, 3, 4, 5, 6, 7));
    QEXTConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleConstVolatileMemberBaseFunctorB = qextMemberFunctor(&MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleConstVolatileMemberBaseFunctorB(&member, true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleConstVolatileMemberBaseFunctorB(&member, false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testBoundFunctorWith7Arg()
{
    MemberBase memberBase;

    QEXTBoundMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctor7_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundMemberBaseFunctorB7_(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctorB7_(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundMemberBaseFunctorB7_(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctor7_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundMemberBaseFunctorB7_obj(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctorB7_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundMemberBaseFunctorB7_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor7(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctor7( 1, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctor7(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundMemberBaseFunctorB7(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctorB7(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundMemberBaseFunctorB7(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith7Arg()
{
    Member member;

    QEXTBoundMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction7);
    QVERIFY(0 == intBoundMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction7);
    QVERIFY(0 == doubleBoundMemberBaseFunctor7_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB7);
    QVERIFY(1 == intBoundMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundMemberBaseFunctorB7_(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB7_(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB7_(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction7);
    QVERIFY(0 == intBoundMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction7);
    QVERIFY(0 == doubleBoundMemberBaseFunctor7_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB7);
    QVERIFY(1 == intBoundMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundMemberBaseFunctorB7_obj(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB7_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB7_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor7(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction7);
    QVERIFY(0 == intBoundMemberBaseFunctor7( 1, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction7);
    QVERIFY(0 == doubleBoundMemberBaseFunctor7(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB7);
    QVERIFY(1 == intBoundMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundMemberBaseFunctorB7(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB7(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB7(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunction7);
    voidBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunction7);
    QVERIFY(0 == intBoundMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunction7);
    QVERIFY(0 == doubleBoundMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidFunctionB7);
    voidBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intFunctionB7);
    QVERIFY(1 == intBoundMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleFunctionB7);
    QVERIFY(1 == doubleBoundMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testBoundConstFunctorWith7Arg()
{
    MemberBase memberBase;

    QEXTBoundConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctor7_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstMemberBaseFunctorB7_(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctorB7_(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstMemberBaseFunctorB7_(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctor7_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstMemberBaseFunctorB7_obj(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctorB7_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstMemberBaseFunctorB7_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor7(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctor7( 1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctor7(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstMemberBaseFunctorB7(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctorB7(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstMemberBaseFunctorB7(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith7Arg()
{
    Member member;

    QEXTBoundConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction7);
    QVERIFY(0 == intBoundConstMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor7_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB7);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB7_(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB7_(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB7_(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction7);
    QVERIFY(0 == intBoundConstMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor7_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB7);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB7_obj(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB7_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB7_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor7(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction7);
    QVERIFY(0 == intBoundConstMemberBaseFunctor7( 1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor7(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB7);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB7(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB7(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB7(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunction7);
    voidBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunction7);
    QVERIFY(0 == intBoundConstMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunction7);
    QVERIFY(0 == doubleBoundConstMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstFunctionB7);
    voidBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstFunctionB7);
    QVERIFY(1 == intBoundConstMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstFunctionB7);
    QVERIFY(1 == doubleBoundConstMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith7Arg()
{
    MemberBase memberBase;

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctor7_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundVolatileMemberBaseFunctorB7_(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctorB7_(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundVolatileMemberBaseFunctorB7_(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctor7_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundVolatileMemberBaseFunctorB7_obj(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctorB7_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundVolatileMemberBaseFunctorB7_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor7(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctor7( 1, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctor7(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundVolatileMemberBaseFunctorB7(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctorB7(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundVolatileMemberBaseFunctorB7(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith7Arg()
{
    Member member;

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction7);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor7_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB7_(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB7_(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB7_(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction7);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor7_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB7_obj(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB7_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB7_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor7(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction7);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor7( 1, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor7(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB7(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB7(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB7(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunction7);
    voidBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunction7);
    QVERIFY(0 == intBoundVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunction7);
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidVolatileFunctionB7);
    voidBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intVolatileFunctionB7);
    QVERIFY(1 == intBoundVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleVolatileFunctionB7);
    QVERIFY(1 == doubleBoundVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith7Arg()
{
    MemberBase memberBase;

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctor7_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstVolatileMemberBaseFunctorB7_(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctorB7_(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstVolatileMemberBaseFunctorB7_(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctor7_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstVolatileMemberBaseFunctorB7_obj(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctorB7_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstVolatileMemberBaseFunctorB7_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor7(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctor7( 1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(&memberBase, &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctor7(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstVolatileMemberBaseFunctorB7(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(&memberBase, &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctorB7(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstVolatileMemberBaseFunctorB7(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(&memberBase, &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith7Arg()
{
    Member member;

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor7_(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor7_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB7_(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB7_(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB7_ = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB7_(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB7_(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor7_obj(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor7_obj(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB7_obj(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB7_obj(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB7_obj = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB7_obj(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB7_obj(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor7(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor7( 1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor7(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor7<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor7<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB7(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor7<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB7 = qextMemberFunctor7(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB7(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB7(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, int, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunction7);
    voidBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, int, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunction7);
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, double, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctor = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunction7);
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTBoundConstVolatileMemberFunctor<void, MemberBase, bool, int, int, int, int, int, int> voidBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::voidConstVolatileFunctionB7);
    voidBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7);
    QEXTBoundConstVolatileMemberFunctor<int, MemberBase, bool, int, int, int, int, int, int> intBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::intConstVolatileFunctionB7);
    QVERIFY(1 == intBoundConstVolatileMemberBaseFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(0 == intBoundConstVolatileMemberBaseFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTBoundConstVolatileMemberFunctor<double, MemberBase, bool, double, double, double, double, double, double> doubleBoundConstVolatileMemberBaseFunctorB = qextMemberFunctor(dynamic_cast<MemberBase *>(&member), &MemberBase::doubleConstVolatileFunctionB7);
    QVERIFY(1 == doubleBoundConstVolatileMemberBaseFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(0 == doubleBoundConstVolatileMemberBaseFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}


QTEST_APPLESS_MAIN(QEXTMemberFunctorTest)

#include <tst_qextmemberfunctor.moc>
