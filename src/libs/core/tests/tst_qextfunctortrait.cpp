#include <qextfunctortrait.h>
#include <qextpointerfunctor.h>
#include <qextmemberfunctor.h>

#include <QtTest>
#include <QDebug>




class Member
{
public:
    Member() {}


    void voidFunction0() {
        qDebug() << "Member::voidFunction0";
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



class QEXTFunctorTraitTest : public QObject
{
    Q_OBJECT
private slots:
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


public:
    static QString sm_result;
};

QString QEXTFunctorTraitTest::sm_result = "";


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
    QVERIFY("UnknownCustom" == QEXTFunctorTrait<MCustomBase>().typeName());

    QVERIFY("QEXTFunctorBase" == QEXTFunctorTrait<QEXTFunctorBase>().typeName());
    QVERIFY("QEXTFunctorBase" == QEXTFunctorTrait<MClassBase>().typeName());
    QVERIFY("QEXTFunctorBase" == QEXTFunctorTrait<MClass>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg0Type()
{
    typedef QEXTPointerFunctor<void>::FunctionType FunctionType0_;
    QVERIFY("QEXTPointerFunctor0" == QEXTFunctorTrait<FunctionType0_>().typeName());
    typedef QEXTPointerFunctor0<void>::FunctionType FunctionType0;
    QVERIFY("QEXTPointerFunctor0" == QEXTFunctorTrait<FunctionType0>().typeName());
    typedef void (*T_voidfunctor0)();
    QVERIFY("QEXTPointerFunctor0" == QEXTFunctorTrait<T_voidfunctor0>().typeName());
    typedef int (*T_intfunctor0)();
    QVERIFY("QEXTPointerFunctor0" == QEXTFunctorTrait<T_intfunctor0>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg1Type()
{
    typedef QEXTPointerFunctor<void, int>::FunctionType FunctionType1_;
    QVERIFY("QEXTPointerFunctor1" == QEXTFunctorTrait<FunctionType1_>().typeName());
    typedef QEXTPointerFunctor1<void, int>::FunctionType FunctionType1;
    QVERIFY("QEXTPointerFunctor1" == QEXTFunctorTrait<FunctionType1>().typeName());
    typedef void (*T_voidfunctor1)(int);
    QVERIFY("QEXTPointerFunctor1" == QEXTFunctorTrait<T_voidfunctor1>().typeName());
    typedef int (*T_intfunctor1)(double);
    QVERIFY("QEXTPointerFunctor1" == QEXTFunctorTrait<T_intfunctor1>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg2Type()
{
    typedef QEXTPointerFunctor<void, int, double>::FunctionType FunctionType2_;
    QVERIFY("QEXTPointerFunctor2" == QEXTFunctorTrait<FunctionType2_>().typeName());
    typedef QEXTPointerFunctor2<void, int, double>::FunctionType FunctionType2;
    QVERIFY("QEXTPointerFunctor2" == QEXTFunctorTrait<FunctionType2>().typeName());
    typedef void (*T_voidfunctor2)(int, QString);
    QVERIFY("QEXTPointerFunctor2" == QEXTFunctorTrait<T_voidfunctor2>().typeName());
    typedef int (*T_intfunctor2)(int, long);
    QVERIFY("QEXTPointerFunctor2" == QEXTFunctorTrait<T_intfunctor2>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg3Type()
{
    typedef QEXTPointerFunctor<void, int, double, int>::FunctionType FunctionType3_;
    QVERIFY("QEXTPointerFunctor3" == QEXTFunctorTrait<FunctionType3_>().typeName());
    typedef QEXTPointerFunctor3<void, int, double, int>::FunctionType FunctionType3;
    QVERIFY("QEXTPointerFunctor3" == QEXTFunctorTrait<FunctionType3>().typeName());
    typedef void (*T_voidfunctor3)(int, int, int);
    QVERIFY("QEXTPointerFunctor3" == QEXTFunctorTrait<T_voidfunctor3>().typeName());
    typedef int (*T_intfunctor3)(double, double, int);
    QVERIFY("QEXTPointerFunctor3" == QEXTFunctorTrait<T_intfunctor3>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg4Type()
{
    typedef QEXTPointerFunctor<void, int, double, int, float>::FunctionType FunctionType4_;
    QVERIFY("QEXTPointerFunctor4" == QEXTFunctorTrait<FunctionType4_>().typeName());
    typedef QEXTPointerFunctor4<void, int, double, int, float>::FunctionType FunctionType4;
    QVERIFY("QEXTPointerFunctor4" == QEXTFunctorTrait<FunctionType4>().typeName());
    typedef void (*T_voidfunctor4)(double, int, double, int);
    QVERIFY("QEXTPointerFunctor4" == QEXTFunctorTrait<T_voidfunctor4>().typeName());
    typedef int (*T_intfunctor4)(float, int, double, long);
    QVERIFY("QEXTPointerFunctor4" == QEXTFunctorTrait<T_intfunctor4>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg5Type()
{
    typedef QEXTPointerFunctor<void, int, double, int, float, QString>::FunctionType FunctionType5_;
    QVERIFY("QEXTPointerFunctor5" == QEXTFunctorTrait<FunctionType5_>().typeName());
    typedef QEXTPointerFunctor5<void, int, double, int, float, QString>::FunctionType FunctionType5;
    QVERIFY("QEXTPointerFunctor5" == QEXTFunctorTrait<FunctionType5>().typeName());
    typedef void (*T_voidfunctor5)(int, int, int, int, QString);
    QVERIFY("QEXTPointerFunctor5" == QEXTFunctorTrait<T_voidfunctor5>().typeName());
    typedef int (*T_intfunctor5)(double, double, int, int, long);
    QVERIFY("QEXTPointerFunctor5" == QEXTFunctorTrait<T_intfunctor5>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg6Type()
{
    typedef QEXTPointerFunctor<void, int, double, int, float, QString, int>::FunctionType FunctionType6_;
    QVERIFY("QEXTPointerFunctor6" == QEXTFunctorTrait<FunctionType6_>().typeName());
    typedef QEXTPointerFunctor6<void, int, double, int, float, QString, int>::FunctionType FunctionType6;
    QVERIFY("QEXTPointerFunctor6" == QEXTFunctorTrait<FunctionType6>().typeName());
    typedef void (*T_voidfunctor6)(int, int, int, int, QString, float);
    QVERIFY("QEXTPointerFunctor6" == QEXTFunctorTrait<T_voidfunctor6>().typeName());
    typedef int (*T_intfunctor6)(double, double, int, int, long, float);
    QVERIFY("QEXTPointerFunctor6" == QEXTFunctorTrait<T_intfunctor6>().typeName());
}

void QEXTFunctorTraitTest::testFunctorArg7Type()
{
    typedef QEXTPointerFunctor<void, int, double, int, float, QString, int, double>::FunctionType FunctionType7_;
    QVERIFY("QEXTPointerFunctor7" == QEXTFunctorTrait<FunctionType7_>().typeName());
    typedef QEXTPointerFunctor7<void, int, double, int, float, QString, int, double>::FunctionType FunctionType7;
    QVERIFY("QEXTPointerFunctor7" == QEXTFunctorTrait<FunctionType7>().typeName());
    typedef void (*T_voidfunctor7)(int, int, int, int, QString, float, int);
    QVERIFY("QEXTPointerFunctor7" == QEXTFunctorTrait<T_voidfunctor7>().typeName());
    typedef int (*T_intfunctor7)(double, double, int, int, long, float, int);
    QVERIFY("QEXTPointerFunctor7" == QEXTFunctorTrait<T_intfunctor7>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg0Type()
{
    typedef QEXTMemberFunctor<void, Member>::FunctionType MemFunctionType0_;
    QVERIFY("QEXTMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0_>().typeName());
    typedef QEXTMemberFunctor0<void, Member>::FunctionType MemFunctionType0;
    QVERIFY("QEXTMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg0Type()
{
    typedef QEXTConstMemberFunctor<void, Member>::FunctionType MemFunctionType0_;
    QVERIFY("QEXTConstMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0_>().typeName());
    typedef QEXTConstMemberFunctor0<void, Member>::FunctionType MemFunctionType0;
    QVERIFY("QEXTConstMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg0Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member>::FunctionType MemFunctionType0_;
    QVERIFY("QEXTVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0_>().typeName());
    typedef QEXTVolatileMemberFunctor0<void, Member>::FunctionType MemFunctionType0;
    QVERIFY("QEXTVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg0Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member>::FunctionType MemFunctionType0_;
    QVERIFY("QEXTConstVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0_>().typeName());
    typedef QEXTConstVolatileMemberFunctor0<void, Member>::FunctionType MemFunctionType0;
    QVERIFY("QEXTConstVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg0Type()
{
    typedef QEXTBoundMemberFunctor<void, Member>::FunctionType MemFunctionType0_;
    QVERIFY("QEXTMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0_>().typeName());
    typedef QEXTBoundMemberFunctor0<void, Member>::FunctionType MemFunctionType0;
    QVERIFY("QEXTMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg0Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member>::FunctionType MemFunctionType0_;
    QVERIFY("QEXTConstMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0_>().typeName());
    typedef QEXTBoundConstMemberFunctor0<void, Member>::FunctionType MemFunctionType0;
    QVERIFY("QEXTConstMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg0Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member>::FunctionType MemFunctionType0_;
    QVERIFY("QEXTVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0_>().typeName());
    typedef QEXTBoundVolatileMemberFunctor0<void, Member>::FunctionType MemFunctionType0;
    QVERIFY("QEXTVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg0Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member>::FunctionType MemFunctionType0_;
    QVERIFY("QEXTConstVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0_>().typeName());
    typedef QEXTBoundConstVolatileMemberFunctor0<void, Member>::FunctionType MemFunctionType0;
    QVERIFY("QEXTConstVolatileMemberFunctor0" == QEXTFunctorTrait<MemFunctionType0>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg1Type()
{
    typedef QEXTMemberFunctor<void, Member, int>::FunctionType MemFunctionType1_;
    QVERIFY("QEXTMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1_>().typeName());
    typedef QEXTMemberFunctor1<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY("QEXTMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg1Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int>::FunctionType MemFunctionType1_;
    QVERIFY("QEXTConstMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1_>().typeName());
    typedef QEXTConstMemberFunctor1<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY("QEXTConstMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg1Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int>::FunctionType MemFunctionType1_;
    QVERIFY("QEXTVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1_>().typeName());
    typedef QEXTVolatileMemberFunctor1<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY("QEXTVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg1Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int>::FunctionType MemFunctionType1_;
    QVERIFY("QEXTConstVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1_>().typeName());
    typedef QEXTConstVolatileMemberFunctor1<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY("QEXTConstVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg1Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int>::FunctionType MemFunctionType1_;
    QVERIFY("QEXTMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1_>().typeName());
    typedef QEXTBoundMemberFunctor1<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY("QEXTMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg1Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int>::FunctionType MemFunctionType1_;
    QVERIFY("QEXTConstMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1_>().typeName());
    typedef QEXTBoundConstMemberFunctor1<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY("QEXTConstMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg1Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int>::FunctionType MemFunctionType1_;
    QVERIFY("QEXTVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1_>().typeName());
    typedef QEXTBoundVolatileMemberFunctor1<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY("QEXTVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg1Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int>::FunctionType MemFunctionType1_;
    QVERIFY("QEXTConstVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1_>().typeName());
    typedef QEXTBoundConstVolatileMemberFunctor1<void, Member, int>::FunctionType MemFunctionType1;
    QVERIFY("QEXTConstVolatileMemberFunctor1" == QEXTFunctorTrait<MemFunctionType1>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg2Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2_;
    QVERIFY("QEXTMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2_>().typeName());
    typedef QEXTMemberFunctor2<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY("QEXTMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg2Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2_;
    QVERIFY("QEXTConstMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2_>().typeName());
    typedef QEXTConstMemberFunctor2<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY("QEXTConstMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg2Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2_;
    QVERIFY("QEXTVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2_>().typeName());
    typedef QEXTVolatileMemberFunctor2<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY("QEXTVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg2Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2_;
    QVERIFY("QEXTConstVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2_>().typeName());
    typedef QEXTConstVolatileMemberFunctor2<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY("QEXTConstVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg2Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2_;
    QVERIFY("QEXTMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2_>().typeName());
    typedef QEXTBoundMemberFunctor2<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY("QEXTMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg2Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2_;
    QVERIFY("QEXTConstMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2_>().typeName());
    typedef QEXTBoundConstMemberFunctor2<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY("QEXTConstMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg2Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2_;
    QVERIFY("QEXTVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2_>().typeName());
    typedef QEXTBoundVolatileMemberFunctor2<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY("QEXTVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg2Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int>::FunctionType MemFunctionType2_;
    QVERIFY("QEXTConstVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2_>().typeName());
    typedef QEXTBoundConstVolatileMemberFunctor2<void, Member, int, int>::FunctionType MemFunctionType2;
    QVERIFY("QEXTConstVolatileMemberFunctor2" == QEXTFunctorTrait<MemFunctionType2>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg3Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3_;
    QVERIFY("QEXTMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3_>().typeName());
    typedef QEXTMemberFunctor3<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY("QEXTMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg3Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3_;
    QVERIFY("QEXTConstMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3_>().typeName());
    typedef QEXTConstMemberFunctor3<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY("QEXTConstMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg3Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3_;
    QVERIFY("QEXTVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3_>().typeName());
    typedef QEXTVolatileMemberFunctor3<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY("QEXTVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg3Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3_;
    QVERIFY("QEXTConstVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3_>().typeName());
    typedef QEXTConstVolatileMemberFunctor3<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY("QEXTConstVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg3Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3_;
    QVERIFY("QEXTMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3_>().typeName());
    typedef QEXTBoundMemberFunctor3<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY("QEXTMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg3Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3_;
    QVERIFY("QEXTConstMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3_>().typeName());
    typedef QEXTBoundConstMemberFunctor3<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY("QEXTConstMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg3Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3_;
    QVERIFY("QEXTVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3_>().typeName());
    typedef QEXTBoundVolatileMemberFunctor3<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY("QEXTVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg3Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int>::FunctionType MemFunctionType3_;
    QVERIFY("QEXTConstVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3_>().typeName());
    typedef QEXTBoundConstVolatileMemberFunctor3<void, Member, int, int, int>::FunctionType MemFunctionType3;
    QVERIFY("QEXTConstVolatileMemberFunctor3" == QEXTFunctorTrait<MemFunctionType3>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg4Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4_;
    QVERIFY("QEXTMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4_>().typeName());
    typedef QEXTMemberFunctor4<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY("QEXTMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg4Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4_;
    QVERIFY("QEXTConstMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4_>().typeName());
    typedef QEXTConstMemberFunctor4<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY("QEXTConstMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg4Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4_;
    QVERIFY("QEXTVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4_>().typeName());
    typedef QEXTVolatileMemberFunctor4<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY("QEXTVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg4Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4_;
    QVERIFY("QEXTConstVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4_>().typeName());
    typedef QEXTConstVolatileMemberFunctor4<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY("QEXTConstVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg4Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4_;
    QVERIFY("QEXTMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4_>().typeName());
    typedef QEXTBoundMemberFunctor4<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY("QEXTMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg4Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4_;
    QVERIFY("QEXTConstMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4_>().typeName());
    typedef QEXTBoundConstMemberFunctor4<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY("QEXTConstMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg4ype()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4_;
    QVERIFY("QEXTVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4_>().typeName());
    typedef QEXTBoundVolatileMemberFunctor4<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY("QEXTVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg4Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int>::FunctionType MemFunctionType4_;
    QVERIFY("QEXTConstVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4_>().typeName());
    typedef QEXTBoundConstVolatileMemberFunctor4<void, Member, int, int, int, int>::FunctionType MemFunctionType4;
    QVERIFY("QEXTConstVolatileMemberFunctor4" == QEXTFunctorTrait<MemFunctionType4>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg5Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5_;
    QVERIFY("QEXTMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5_>().typeName());
    typedef QEXTMemberFunctor5<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY("QEXTMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg5Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5_;
    QVERIFY("QEXTConstMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5_>().typeName());
    typedef QEXTConstMemberFunctor5<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY("QEXTConstMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg5Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5_;
    QVERIFY("QEXTVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5_>().typeName());
    typedef QEXTVolatileMemberFunctor5<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY("QEXTVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg5Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5_;
    QVERIFY("QEXTConstVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5_>().typeName());
    typedef QEXTConstVolatileMemberFunctor5<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY("QEXTConstVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg5Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5_;
    QVERIFY("QEXTMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5_>().typeName());
    typedef QEXTBoundMemberFunctor5<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY("QEXTMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg5Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5_;
    QVERIFY("QEXTConstMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5_>().typeName());
    typedef QEXTBoundConstMemberFunctor5<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY("QEXTConstMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg5Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5_;
    QVERIFY("QEXTVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5_>().typeName());
    typedef QEXTBoundVolatileMemberFunctor5<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY("QEXTVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg5Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5_;
    QVERIFY("QEXTConstVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5_>().typeName());
    typedef QEXTBoundConstVolatileMemberFunctor5<void, Member, int, int, int, int, int>::FunctionType MemFunctionType5;
    QVERIFY("QEXTConstVolatileMemberFunctor5" == QEXTFunctorTrait<MemFunctionType5>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg6Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6_;
    QVERIFY("QEXTMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6_>().typeName());
    typedef QEXTMemberFunctor6<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY("QEXTMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg6Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6_;
    QVERIFY("QEXTConstMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6_>().typeName());
    typedef QEXTConstMemberFunctor6<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY("QEXTConstMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg6Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6_;
    QVERIFY("QEXTVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6_>().typeName());
    typedef QEXTVolatileMemberFunctor6<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY("QEXTVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg6Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6_;
    QVERIFY("QEXTConstVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6_>().typeName());
    typedef QEXTConstVolatileMemberFunctor6<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY("QEXTConstVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg6Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6_;
    QVERIFY("QEXTMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6_>().typeName());
    typedef QEXTBoundMemberFunctor6<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY("QEXTMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg6Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6_;
    QVERIFY("QEXTConstMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6_>().typeName());
    typedef QEXTBoundConstMemberFunctor6<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY("QEXTConstMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg6Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6_;
    QVERIFY("QEXTVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6_>().typeName());
    typedef QEXTBoundVolatileMemberFunctor6<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY("QEXTVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg6Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6_;
    QVERIFY("QEXTConstVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6_>().typeName());
    typedef QEXTBoundConstVolatileMemberFunctor6<void, Member, int, int, int, int, int, int>::FunctionType MemFunctionType6;
    QVERIFY("QEXTConstVolatileMemberFunctor6" == QEXTFunctorTrait<MemFunctionType6>().typeName());
}

void QEXTFunctorTraitTest::testMemberFunctorArg7Type()
{
    typedef QEXTMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7_;
    QVERIFY("QEXTMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7_>().typeName());
    typedef QEXTMemberFunctor7<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY("QEXTMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testConstMemberFunctorArg7Type()
{
    typedef QEXTConstMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7_;
    QVERIFY("QEXTConstMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7_>().typeName());
    typedef QEXTConstMemberFunctor7<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY("QEXTConstMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testVolatileMemberFunctorArg7Type()
{
    typedef QEXTVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7_;
    QVERIFY("QEXTVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7_>().typeName());
    typedef QEXTVolatileMemberFunctor7<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY("QEXTVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testConstVolatileMemberFunctorArg7Type()
{
    typedef QEXTConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7_;
    QVERIFY("QEXTConstVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7_>().typeName());
    typedef QEXTConstVolatileMemberFunctor7<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY("QEXTConstVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testBoundMemberFunctorArg7Type()
{
    typedef QEXTBoundMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7_;
    QVERIFY("QEXTMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7_>().typeName());
    typedef QEXTBoundMemberFunctor7<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY("QEXTMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstMemberFunctorArg7Type()
{
    typedef QEXTBoundConstMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7_;
    QVERIFY("QEXTConstMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7_>().typeName());
    typedef QEXTBoundConstMemberFunctor7<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY("QEXTConstMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testBoundVolatileMemberFunctorArg7Type()
{
    typedef QEXTBoundVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7_;
    QVERIFY("QEXTVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7_>().typeName());
    typedef QEXTBoundVolatileMemberFunctor7<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY("QEXTVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

void QEXTFunctorTraitTest::testBoundConstVolatileMemberFunctorArg7Type()
{
    typedef QEXTBoundConstVolatileMemberFunctor<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7_;
    QVERIFY("QEXTConstVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7_>().typeName());
    typedef QEXTBoundConstVolatileMemberFunctor7<void, Member, int, int, int, int, int, int, int>::FunctionType MemFunctionType7;
    QVERIFY("QEXTConstVolatileMemberFunctor7" == QEXTFunctorTrait<MemFunctionType7>().typeName());
}

QTEST_APPLESS_MAIN(QEXTFunctorTraitTest)

#include <tst_qextfunctortrait.moc>
