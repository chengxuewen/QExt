#include <qextmemberfunctor.h>

#include <QtTest>
#include <QDebug>

class MemberBase
{
public:
    MemberBase() {}

    virtual void voidFunction0() {
        qDebug() << "MemberBase::voidFunction0";
        QVERIFY(true);
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
        QVERIFY(true);
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
        return a1;
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
        QVERIFY(true);
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
        return a1;
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
        return a1;
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
        return a1;
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
        return 0;
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
        return a1;
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
        return 0;
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
    int intFunctionB3(bool a1, int a2, int a3) volatile {
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
    int intFunctionB5(bool a1, int a2, int a3, int a4, int a5) volatile {
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
        return 0;
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
        return 0;
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
    //    QEXTFunctor1<void, int> voidFunctor1_ = qextFunctor(&voidFunction1);
    //    voidFunctor1_(1);
    //    QEXTFunctor1<int, int> intFunctor1_ = qextFunctor(&intFunction1);
    //    QVERIFY(1 == intFunctor1_(1));
    //    QEXTFunctor1<double, double> doubleFunctor1_ = qextFunctor(&doubleFunction1);
    //    QVERIFY(1.1 == doubleFunctor1_(1.1));

    //    QEXTFunctor1<void, bool> voidFunctorB1_ = qextFunctor(&voidFunctionB1);
    //    voidFunctorB1_(1);
    //    QEXTFunctor1<int, bool> intFunctorB1_ = qextFunctor(&intFunctionB1);
    //    QVERIFY(1 == intFunctorB1_(true));
    //    QVERIFY(0 == intFunctorB1_(false));
    //    QEXTFunctor1<double, bool> doubleFunctorB1_ = qextFunctor(&doubleFunctionB1);
    //    QVERIFY(1 == doubleFunctorB1_(true));
    //    QVERIFY(0 == doubleFunctorB1_(false));


    //    QEXTFunctor1<void, int> voidFunctor1 = qextFunctor1(&voidFunction1);
    //    voidFunctor1(1);
    //    QEXTFunctor1<int, int> intFunctor1 = qextFunctor1(&intFunction1);
    //    QVERIFY(1 == intFunctor1(1));
    //    QEXTFunctor1<double, double> doubleFunctor1 = qextFunctor1(&doubleFunction1);
    //    QVERIFY(1.1 == doubleFunctor1(1.1));

    //    QEXTFunctor1<void, bool> voidFunctorB1 = qextFunctor1(&voidFunctionB1);
    //    voidFunctorB1(1);
    //    QEXTFunctor1<int, bool> intFunctorB1 = qextFunctor1(&intFunctionB1);
    //    QVERIFY(1 == intFunctorB1(true));
    //    QVERIFY(0 == intFunctorB1(false));
    //    QEXTFunctor1<double, bool> doubleFunctorB1 = qextFunctor1(&doubleFunctionB1);
    //    QVERIFY(1 == doubleFunctorB1(true));
    //    QVERIFY(0 == doubleFunctorB1(false));


    //    QEXTFunctor<void, int> voidFunctor = qextFunctor(&voidFunction1);
    //    voidFunctor(1);
    //    QEXTFunctor<int, int> intFunctor = qextFunctor(&intFunction1);
    //    QVERIFY(1 == intFunctor(1));
    //    QEXTFunctor<double, double> doubleFunctor = qextFunctor(&doubleFunction1);
    //    QVERIFY(1.1 == doubleFunctor(1.1));

    //    QEXTFunctor<void, bool> voidFunctorB = qextFunctor(&voidFunctionB1);
    //    voidFunctorB(1);
    //    QEXTFunctor<int, bool> intFunctorB = qextFunctor(&intFunctionB1);
    //    QVERIFY(1 == intFunctorB(true));
    //    QVERIFY(0 == intFunctorB(false));
    //    QEXTFunctor<double, bool> doubleFunctorB = qextFunctor(&doubleFunctionB1);
    //    QVERIFY(1 == doubleFunctorB(true));
    //    QVERIFY(0 == doubleFunctorB(false));
}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testConstFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testVolatileFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testBoundFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith1Arg()
{

}

void QEXTMemberFunctorTest::testFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testConstFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testVolatileFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testBoundFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith2Arg()
{

}

void QEXTMemberFunctorTest::testFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testVolatileFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testBoundFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith3Arg()
{

}

void QEXTMemberFunctorTest::testFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testVolatileFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testBoundFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith4Arg()
{

}

void QEXTMemberFunctorTest::testFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testVolatileFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testBoundFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith5Arg()
{

}

void QEXTMemberFunctorTest::testFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testVolatileFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testBoundFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith6Arg()
{

}

void QEXTMemberFunctorTest::testFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testVolatileFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismVolatileFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testConstVolatileFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismConstVolatileFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testBoundFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testBoundVolatileFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundVolatileFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testBoundConstVolatileFunctorWith7Arg()
{

}

void QEXTMemberFunctorTest::testPolymorphismBoundConstVolatileFunctorWith7Arg()
{

}

QTEST_APPLESS_MAIN(QEXTMemberFunctorTest)

#include <tst_qextmemberfunctor.moc>
