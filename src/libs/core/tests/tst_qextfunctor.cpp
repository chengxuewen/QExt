#include <qextfunctor.h>

#include <QtTest>
#include <QDebug>

void voidFunction0() {
    qDebug() << "voidFunction0";
    QVERIFY(true);
}
void voidFunction1(int a1) {
    qDebug() << "voidFunction1:" << a1;
}
void voidFunction2(int a1, int a2) {
    qDebug() << "voidFunction2:" << a1 << "," << a2;
}
void voidFunction3(int a1, int a2, int a3) {
    qDebug() << "voidFunction3:" << a1 << "," << a2 << "," << a3;
}
void voidFunction4(int a1, int a2, int a3, int a4) {
    qDebug() << "voidFunction4:" << a1 << "," << a2 << "," << a3 << "," << a4;
}
void voidFunction5(int a1, int a2, int a3, int a4, int a5) {
    qDebug() << "voidFunction5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
}
void voidFunction6(int a1, int a2, int a3, int a4, int a5, int a6) {
    qDebug() << "voidFunction6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
}
void voidFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
    qDebug() << "voidFunction7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
}
void voidFunctionB1(bool a1) {
    qDebug() << "voidFunctionB1:" << a1;
}
void voidFunctionB2(bool a1, int a2) {
    qDebug() << "voidFunctionB2:" << a1 << "," << a2;
}
void voidFunctionB3(bool a1, int a2, int a3) {
    qDebug() << "voidFunctionB3:" << a1 << "," << a2 << "," << a3;
}
void voidFunctionB4(bool a1, int a2, int a3, int a4) {
    qDebug() << "voidFunctionB4:" << a1 << "," << a2 << "," << a3 << "," << a4;
}
void voidFunctionB5(bool a1, int a2, int a3, int a4, int a5) {
    qDebug() << "voidFunctionB5:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5;
}
void voidFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) {
    qDebug() << "voidFunctionB6:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6;
}
void voidFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) {
    qDebug() << "voidFunctionB7:" << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7;
}

int intFunction0() {
    return 0;
}
int intFunction1(int a1) {
    return a1;
}
int intFunction2(int a1, int a2) {
    return a1 + a2;
}
int intFunction3(int a1, int a2, int a3) {
    return a1 + a2 + a3;
}
int intFunction4(int a1, int a2, int a3, int a4) {
    return a1 + a2 + a3 + a4;
}
int intFunction5(int a1, int a2, int a3, int a4, int a5) {
    return a1 + a2 + a3 + a4 + a5;
}
int intFunction6(int a1, int a2, int a3, int a4, int a5, int a6) {
    return a1 + a2 + a3 + a4 + a5 + a6;
}
int intFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
    return a1 + a2 + a3 + a4 + a5 + a6 + a7;
}
int intFunctionB1(bool a1) {
    return a1;
}
int intFunctionB2(bool a1, int a2) {
    return a1 ? a2 : 0;
}
int intFunctionB3(bool a1, int a2, int a3) {
    return a1 ? (a2 + a3) : (a2 * a3);
}
int intFunctionB4(bool a1, int a2, int a3, int a4) {
    return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
}
int intFunctionB5(bool a1, int a2, int a3, int a4, int a5) {
    return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
}
int intFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6) {
    return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
}
int intFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7) {
    return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
}

double doubleFunction0() {
    return 0;
}
double doubleFunction1(double a1) {
    return a1;
}
double doubleFunction2(double a1, double a2) {
    return a1 + a2;
}
double doubleFunction3(double a1, double a2, double a3) {
    return a1 + a2 + a3;
}
double doubleFunction4(double a1, double a2, double a3, double a4) {
    return a1 + a2 + a3 + a4;
}
double doubleFunction5(double a1, double a2, double a3, double a4, double a5) {
    return a1 + a2 + a3 + a4 + a5;
}
double doubleFunction6(double a1, double a2, double a3, double a4, double a5, double a6) {
    return a1 + a2 + a3 + a4 + a5 + a6;
}
double doubleFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7) {
    return a1 + a2 + a3 + a4 + a5 + a6 + a7;
}
double doubleFunctionB1(bool a1) {
    return a1;
}
double doubleFunctionB2(bool a1, double a2) {
    return a1 ? a2 : 0;
}
double doubleFunctionB3(bool a1, double a2, double a3) {
    return a1 ? (a2 + a3) : (a2 * a3);
}
double doubleFunctionB4(bool a1, double a2, double a3, double a4) {
    return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
}
double doubleFunctionB5(bool a1, double a2, double a3, double a4, double a5) {
    return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
}
double doubleFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6) {
    return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
}
double doubleFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7) {
    return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
}


class QEXTFunctorTest : public QObject
{
    Q_OBJECT
private slots:
    void testFunctorWith0Arg();
    void testFunctorWith1Arg();
    void testFunctorWith2Arg();
    void testFunctorWith3Arg();
    void testFunctorWith4Arg();
    void testFunctorWith5Arg();
    void testFunctorWith6Arg();
    void testFunctorWith7Arg();
};



void QEXTFunctorTest::testFunctorWith0Arg()
{
    QEXTFunctor0<void> voidFunctor0_ = qextFunctor(&voidFunction0);
    voidFunctor0_();
    QEXTFunctor0<int> intFunctor0_ = qextFunctor(&intFunction0);
    QVERIFY(0 == intFunctor0_());
    QEXTFunctor0<double> doubleFunctor0_ = qextFunctor(&doubleFunction0);
    QVERIFY(0 == doubleFunctor0_());

    QEXTFunctor0<void> voidFunctor0 = qextFunctor0(&voidFunction0);
    voidFunctor0();
    QEXTFunctor0<int> intFunctor0 = qextFunctor0(&intFunction0);
    QVERIFY(0 == intFunctor0());
    QEXTFunctor0<double> doubleFunctor0 = qextFunctor0(&doubleFunction0);
    QVERIFY(0 == doubleFunctor0());

    QEXTFunctor<void> voidFunctor = qextFunctor(&voidFunction0);
    voidFunctor();
    QEXTFunctor<int> intFunctor = qextFunctor(&intFunction0);
    QVERIFY(0 == intFunctor());
    QEXTFunctor<double> doubleFunctor = qextFunctor(&doubleFunction0);
    QVERIFY(0 == doubleFunctor());
}

void QEXTFunctorTest::testFunctorWith1Arg()
{
    QEXTFunctor1<void, int> voidFunctor1_ = qextFunctor(&voidFunction1);
    voidFunctor1_(1);
    QEXTFunctor1<int, int> intFunctor1_ = qextFunctor(&intFunction1);
    QVERIFY(1 == intFunctor1_(1));
    QEXTFunctor1<double, double> doubleFunctor1_ = qextFunctor(&doubleFunction1);
    QVERIFY(1.1 == doubleFunctor1_(1.1));

    QEXTFunctor1<void, bool> voidFunctorB1_ = qextFunctor(&voidFunctionB1);
    voidFunctorB1_(1);
    QEXTFunctor1<int, bool> intFunctorB1_ = qextFunctor(&intFunctionB1);
    QVERIFY(1 == intFunctorB1_(true));
    QVERIFY(0 == intFunctorB1_(false));
    QEXTFunctor1<double, bool> doubleFunctorB1_ = qextFunctor(&doubleFunctionB1);
    QVERIFY(1 == doubleFunctorB1_(true));
    QVERIFY(0 == doubleFunctorB1_(false));


    QEXTFunctor1<void, int> voidFunctor1 = qextFunctor1(&voidFunction1);
    voidFunctor1(1);
    QEXTFunctor1<int, int> intFunctor1 = qextFunctor1(&intFunction1);
    QVERIFY(1 == intFunctor1(1));
    QEXTFunctor1<double, double> doubleFunctor1 = qextFunctor1(&doubleFunction1);
    QVERIFY(1.1 == doubleFunctor1(1.1));

    QEXTFunctor1<void, bool> voidFunctorB1 = qextFunctor1(&voidFunctionB1);
    voidFunctorB1(1);
    QEXTFunctor1<int, bool> intFunctorB1 = qextFunctor1(&intFunctionB1);
    QVERIFY(1 == intFunctorB1(true));
    QVERIFY(0 == intFunctorB1(false));
    QEXTFunctor1<double, bool> doubleFunctorB1 = qextFunctor1(&doubleFunctionB1);
    QVERIFY(1 == doubleFunctorB1(true));
    QVERIFY(0 == doubleFunctorB1(false));


    QEXTFunctor<void, int> voidFunctor = qextFunctor(&voidFunction1);
    voidFunctor(1);
    QEXTFunctor<int, int> intFunctor = qextFunctor(&intFunction1);
    QVERIFY(1 == intFunctor(1));
    QEXTFunctor<double, double> doubleFunctor = qextFunctor(&doubleFunction1);
    QVERIFY(1.1 == doubleFunctor(1.1));

    QEXTFunctor<void, bool> voidFunctorB = qextFunctor(&voidFunctionB1);
    voidFunctorB(1);
    QEXTFunctor<int, bool> intFunctorB = qextFunctor(&intFunctionB1);
    QVERIFY(1 == intFunctorB(true));
    QVERIFY(0 == intFunctorB(false));
    QEXTFunctor<double, bool> doubleFunctorB = qextFunctor(&doubleFunctionB1);
    QVERIFY(1 == doubleFunctorB(true));
    QVERIFY(0 == doubleFunctorB(false));
}

void QEXTFunctorTest::testFunctorWith2Arg()
{
    QEXTFunctor2<void, int, int> voidFunctor2_ = qextFunctor(&voidFunction2);
    voidFunctor2_(1, 2);
    QEXTFunctor2<int, int, int> intFunctor2_ = qextFunctor(&intFunction2);
    QVERIFY(1 + 2 == intFunctor2_(1, 2));
    QEXTFunctor2<double, double, double> doubleFunctor2_ = qextFunctor(&doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleFunctor2_(1.1, 2.2));

    QEXTFunctor2<void, bool, int> voidFunctorB2_ = qextFunctor(&voidFunctionB2);
    voidFunctorB2_(true, 2);
    QEXTFunctor2<int, bool, int> intFunctorB2_ = qextFunctor(&intFunctionB2);
    QVERIFY(2 == intFunctorB2_(true, 2));
    QVERIFY(0 == intFunctorB2_(false, 2));
    QEXTFunctor2<double, bool, double> doubleFunctorB2_ = qextFunctor(&doubleFunctionB2);
    QVERIFY(2.2 == doubleFunctorB2_(true, 2.2));
    QVERIFY(0 == doubleFunctorB2_(false, 2.2));


    QEXTFunctor2<void, int, int> voidFunctor2 = qextFunctor2(&voidFunction2);
    voidFunctor2(1, 2);
    QEXTFunctor2<int, int, int> intFunctor2 = qextFunctor2(&intFunction2);
    QVERIFY(1 + 2 == intFunctor2(1, 2));
    QEXTFunctor2<double, double, double> doubleFunctor2 = qextFunctor2(&doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleFunctor2(1.1, 2.2));

    QEXTFunctor2<void, bool, int> voidFunctorB2 = qextFunctor2(&voidFunctionB2);
    voidFunctorB2(true, 2);
    QEXTFunctor2<int, bool, int> intFunctorB2 = qextFunctor2(&intFunctionB2);
    QVERIFY(2 == intFunctorB2(true, 2));
    QVERIFY(0 == intFunctorB2(false, 2));
    QEXTFunctor2<double, bool, double> doubleFunctorB2 = qextFunctor2(&doubleFunctionB2);
    QVERIFY(2.2 == doubleFunctorB2(true, 2.2));
    QVERIFY(0 == doubleFunctorB2(false, 2.2));


    QEXTFunctor<void, int, int> voidFunctor = qextFunctor(&voidFunction2);
    voidFunctor(1, 2);
    QEXTFunctor<int, int, int> intFunctor = qextFunctor(&intFunction2);
    QVERIFY(1 + 2 == intFunctor(1, 2));
    QEXTFunctor<double, double, double> doubleFunctor = qextFunctor(&doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleFunctor(1.1, 2.2));

    QEXTFunctor<void, bool, int> voidFunctorB = qextFunctor(&voidFunctionB2);
    voidFunctorB(true, 2);
    QEXTFunctor<int, bool, int> intFunctorB = qextFunctor(&intFunctionB2);
    QVERIFY(2 == intFunctorB(true, 2));
    QVERIFY(0 == intFunctorB(false, 2));
    QEXTFunctor<double, bool, double> doubleFunctorB = qextFunctor(&doubleFunctionB2);
    QVERIFY(2.2 == doubleFunctorB(true, 2.2));
    QVERIFY(0 == doubleFunctorB(false, 2.2));
}

void QEXTFunctorTest::testFunctorWith3Arg()
{
    QEXTFunctor3<void, int, int, int> voidFunctor3_ = qextFunctor(&voidFunction3);
    voidFunctor3_(1, 2, 3);
    QEXTFunctor3<int, int, int, int> intFunctor3_ = qextFunctor(&intFunction3);
    QVERIFY(1 + 2 + 3 == intFunctor3_(1, 2, 3));
    QEXTFunctor3<double, double, double, double> doubleFunctor3_ = qextFunctor(&doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleFunctor3_(1.1, 2.2, 3.3));

    QEXTFunctor3<void, bool, int, int> voidFunctorB3_ = qextFunctor(&voidFunctionB3);
    voidFunctorB3_(true, 2, 3);
    QEXTFunctor3<int, bool, int, int> intFunctorB3_ = qextFunctor(&intFunctionB3);
    QVERIFY(2 + 3 == intFunctorB3_(true, 2, 3));
    QVERIFY(2 * 3 == intFunctorB3_(false, 2, 3));
    QEXTFunctor3<double, bool, double, double> doubleFunctorB3_ = qextFunctor(&doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleFunctorB3_(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleFunctorB3_(false, 2.2, 3.3));


    QEXTFunctor3<void, int, int, int> voidFunctor3 = qextFunctor3(&voidFunction3);
    voidFunctor3(1, 2, 3);
    QEXTFunctor3<int, int, int, int> intFunctor3 = qextFunctor3(&intFunction3);
    QVERIFY(1 + 2 + 3 == intFunctor3(1, 2, 3));
    QEXTFunctor3<double, double, double, double> doubleFunctor3 = qextFunctor3(&doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleFunctor3(1.1, 2.2, 3.3));

    QEXTFunctor3<void, bool, int, int> voidFunctorB3 = qextFunctor3(&voidFunctionB3);
    voidFunctorB3(true, 2, 3);
    QEXTFunctor3<int, bool, int, int> intFunctorB3 = qextFunctor3(&intFunctionB3);
    QVERIFY(2 + 3 == intFunctorB3(true, 2, 3));
    QVERIFY(2 * 3 == intFunctorB3(false, 2, 3));
    QEXTFunctor3<double, bool, double, double> doubleFunctorB3 = qextFunctor3(&doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleFunctorB3(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleFunctorB3(false, 2.2, 3.3));


    QEXTFunctor<void, int, int, int> voidFunctor = qextFunctor(&voidFunction3);
    voidFunctor(1, 2, 3);
    QEXTFunctor<int, int, int, int> intFunctor = qextFunctor(&intFunction3);
    QVERIFY(1 + 2 + 3 == intFunctor(1, 2, 3));
    QEXTFunctor<double, double, double, double> doubleFunctor = qextFunctor(&doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleFunctor(1.1, 2.2, 3.3));

    QEXTFunctor<void, bool, int, int> voidFunctorB = qextFunctor(&voidFunctionB3);
    voidFunctorB3(true, 2, 3);
    QEXTFunctor<int, bool, int, int> intFunctorB = qextFunctor(&intFunctionB3);
    QVERIFY(2 + 3 == intFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intFunctorB(false, 2, 3));
    QEXTFunctor<double, bool, double, double> doubleFunctorB = qextFunctor(&doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleFunctorB(false, 2.2, 3.3));
}

void QEXTFunctorTest::testFunctorWith4Arg()
{
    QEXTFunctor4<void, int, int, int, int> voidFunctor4_ = qextFunctor(&voidFunction4);
    voidFunctor4_(1, 2, 3, 4);
    QEXTFunctor4<int, int, int, int, int> intFunctor4_ = qextFunctor(&intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intFunctor4_(1, 2, 3, 4));
    QEXTFunctor4<double, double, double, double, double> doubleFunctor4_ = qextFunctor(&doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleFunctor4_(1.1, 2.2, 3.3, 4.4));

    QEXTFunctor4<void, bool, int, int, int> voidFunctorB4_ = qextFunctor(&voidFunctionB4);
    voidFunctorB4_(1, 2, 3, 4);
    QEXTFunctor4<int, bool, int, int, int> intFunctorB4_ = qextFunctor(&intFunctionB4);
    QVERIFY(2 + 3 + 4 == intFunctorB4_(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intFunctorB4_(false, 2, 3, 4));
    QEXTFunctor4<double, bool, double, double, double> doubleFunctorB4_ = qextFunctor(&doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleFunctorB4_(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleFunctorB4_(false, 2.2, 3.3, 4.4));


    QEXTFunctor4<void, int, int, int, int> voidFunctor4 = qextFunctor4(&voidFunction4);
    voidFunctor4(1, 2, 3, 4);
    QEXTFunctor4<int, int, int, int, int> intFunctor4 = qextFunctor4(&intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intFunctor4(1, 2, 3, 4));
    QEXTFunctor4<double, double, double, double, double> doubleFunctor4 = qextFunctor4(&doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleFunctor4(1.1, 2.2, 3.3, 4.4));

    QEXTFunctor4<void, bool, int, int, int> voidFunctorB4 = qextFunctor4(&voidFunctionB4);
    voidFunctorB4(1, 2, 3, 4);
    QEXTFunctor4<int, bool, int, int, int> intFunctorB4 = qextFunctor4(&intFunctionB4);
    QVERIFY(2 + 3 + 4 == intFunctorB4(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intFunctorB4(false, 2, 3, 4));
    QEXTFunctor4<double, bool, double, double, double> doubleFunctorB4 = qextFunctor4(&doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleFunctorB4(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleFunctorB4(false, 2.2, 3.3, 4.4));


    QEXTFunctor<void, bool, int, int, int> voidFunctorB = qextFunctor(&voidFunctionB4);
    voidFunctorB(1, 2, 3, 4);
    QEXTFunctor<int, bool, int, int, int> intFunctorB = qextFunctor(&intFunctionB4);
    QVERIFY(2 + 3 + 4 == intFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intFunctorB(false, 2, 3, 4));
    QEXTFunctor<double, bool, double, double, double> doubleFunctorB = qextFunctor(&doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleFunctorB(false, 2.2, 3.3, 4.4));


    QEXTFunctor<void, int, int, int, int> voidFunctor = qextFunctor(&voidFunction4);
    voidFunctor(1, 2, 3, 4);
    QEXTFunctor<int, int, int, int, int> intFunctor = qextFunctor(&intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intFunctor(1, 2, 3, 4));
    QEXTFunctor<double, double, double, double, double> doubleFunctor = qextFunctor(&doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleFunctor(1.1, 2.2, 3.3, 4.4));
}

void QEXTFunctorTest::testFunctorWith5Arg()
{
    QEXTFunctor5<void, int, int, int, int, int> voidFunctor5_ = qextFunctor(&voidFunction5);
    voidFunctor5_(1, 2, 3, 4, 5);
    QEXTFunctor5<int, int, int, int, int, int> intFunctor5_ = qextFunctor(&intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intFunctor5_(1, 2, 3, 4, 5));
    QEXTFunctor5<double, double, double, double, double, double> doubleFunctor5_ = qextFunctor(&doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleFunctor5_(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTFunctor5<void, bool, int, int, int, int> voidFunctorB5_ = qextFunctor(&voidFunctionB5);
    voidFunctorB5_(true, 2, 3, 4, 5);
    QEXTFunctor5<int, bool, int, int, int, int> intFunctorB5_ = qextFunctor(&intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intFunctorB5_(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intFunctorB5_(false, 2, 3, 4, 5));
    QEXTFunctor5<double, bool, double, double, double, double> doubleFunctorB5_ = qextFunctor(&doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleFunctorB5_(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleFunctorB5_(false, 2.2, 3.3, 4.4, 5.5));


    QEXTFunctor5<void, int, int, int, int, int> voidFunctor5 = qextFunctor5(&voidFunction5);
    voidFunctor5(1, 2, 3, 4, 5);
    QEXTFunctor5<int, int, int, int, int, int> intFunctor5 = qextFunctor5(&intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intFunctor5(1, 2, 3, 4, 5));
    QEXTFunctor5<double, double, double, double, double, double> doubleFunctor5 = qextFunctor5(&doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleFunctor5(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTFunctor5<void, bool, int, int, int, int> voidFunctorB5 = qextFunctor5(&voidFunctionB5);
    voidFunctorB5(true, 2, 3, 4, 5);
    QEXTFunctor5<int, bool, int, int, int, int> intFunctorB5 = qextFunctor5(&intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intFunctorB5(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intFunctorB5(false, 2, 3, 4, 5));
    QEXTFunctor5<double, bool, double, double, double, double> doubleFunctorB5 = qextFunctor5(&doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleFunctorB5(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleFunctorB5(false, 2.2, 3.3, 4.4, 5.5));


    QEXTFunctor<void, int, int, int, int, int> voidFunctor = qextFunctor(&voidFunction5);
    voidFunctor(1, 2, 3, 4, 5);
    QEXTFunctor<int, int, int, int, int, int> intFunctor = qextFunctor(&intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intFunctor(1, 2, 3, 4, 5));
    QEXTFunctor<double, double, double, double, double, double> doubleFunctor = qextFunctor(&doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTFunctor<void, bool, int, int, int, int> voidFunctorB = qextFunctor(&voidFunctionB5);
    voidFunctorB(true, 2, 3, 4, 5);
    QEXTFunctor<int, bool, int, int, int, int> intFunctorB = qextFunctor(&intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intFunctorB(false, 2, 3, 4, 5));
    QEXTFunctor<double, bool, double, double, double, double> doubleFunctorB = qextFunctor(&doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5));
}

void QEXTFunctorTest::testFunctorWith6Arg()
{
    QEXTFunctor6<void, int, int, int, int, int, int> voidFunctor6_ = qextFunctor(&voidFunction6);
    voidFunctor6_(1, 2, 3, 4, 5, 6);
    QEXTFunctor6<int, int, int, int, int, int, int> intFunctor6_ = qextFunctor(&intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intFunctor6_(1, 2, 3, 4, 5, 6));
    QEXTFunctor6<double, double, double, double, double, double, double> doubleFunctor6_ = qextFunctor(&doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctor6_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTFunctor6<void, bool, int, int, int, int, int> voidFunctorB6_ = qextFunctor(&voidFunctionB6);
    voidFunctorB6_(true, 2, 3, 4, 5, 6);
    QEXTFunctor6<int, bool, int, int, int, int, int> intFunctorB6_ = qextFunctor(&intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intFunctorB6_(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intFunctorB6_(false, 2, 3, 4, 5, 6));
    QEXTFunctor6<double, bool, double, double, double, double, double> doubleFunctorB6_ = qextFunctor(&doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctorB6_(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleFunctorB6_(false, 2.2, 3.3, 4.4, 5.5, 6.6));


    QEXTFunctor6<void, int, int, int, int, int, int> voidFunctor6 = qextFunctor6(&voidFunction6);
    voidFunctor6(1, 2, 3, 4, 5, 6);
    QEXTFunctor6<int, int, int, int, int, int, int> intFunctor6 = qextFunctor6(&intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intFunctor6(1, 2, 3, 4, 5, 6));
    QEXTFunctor6<double, double, double, double, double, double, double> doubleFunctor6 = qextFunctor6(&doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctor6(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTFunctor6<void, bool, int, int, int, int, int> voidFunctorB6 = qextFunctor6(&voidFunctionB6);
    voidFunctorB6(true, 2, 3, 4, 5, 6);
    QEXTFunctor6<int, bool, int, int, int, int, int> intFunctorB6 = qextFunctor6(&intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intFunctorB6(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intFunctorB6(false, 2, 3, 4, 5, 6));
    QEXTFunctor6<double, bool, double, double, double, double, double> doubleFunctorB6 = qextFunctor6(&doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctorB6(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleFunctorB6(false, 2.2, 3.3, 4.4, 5.5, 6.6));


    QEXTFunctor<void, int, int, int, int, int, int> voidFunctor = qextFunctor(&voidFunction6);
    voidFunctor(1, 2, 3, 4, 5, 6);
    QEXTFunctor<int, int, int, int, int, int, int> intFunctor = qextFunctor(&intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intFunctor(1, 2, 3, 4, 5, 6));
    QEXTFunctor<double, double, double, double, double, double, double> doubleFunctor = qextFunctor(&doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTFunctor<void, bool, int, int, int, int, int> voidFunctorB = qextFunctor(&voidFunctionB6);
    voidFunctorB(true, 2, 3, 4, 5, 6);
    QEXTFunctor<int, bool, int, int, int, int, int> intFunctorB = qextFunctor(&intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intFunctorB(false, 2, 3, 4, 5, 6));
    QEXTFunctor<double, bool, double, double, double, double, double> doubleFunctorB = qextFunctor(&doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));
}

void QEXTFunctorTest::testFunctorWith7Arg()
{
    QEXTFunctor7<void, int, int, int, int, int, int, int> voidFunctor7_ = qextFunctor(&voidFunction7);
    voidFunctor7_(1, 2, 3, 4, 5, 6, 7);
    QEXTFunctor7<int, int, int, int, int, int, int, int> intFunctor7_ = qextFunctor(&intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intFunctor7_(1, 2, 3, 4, 5, 6, 7));
    QEXTFunctor7<double, double, double, double, double, double, double, double> doubleFunctor7_ = qextFunctor(&doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctor7_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTFunctor7<void, bool, int, int, int, int, int, int> voidFunctorB7_ = qextFunctor(&voidFunctionB7);
    voidFunctorB7_(1, 2, 3, 4, 5, 6, 7);
    QEXTFunctor7<int, bool, int, int, int, int, int, int> intFunctorB7_ = qextFunctor(&intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intFunctorB7_(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intFunctorB7_(false, 2, 3, 4, 5, 6, 7));
    QEXTFunctor7<double, bool, double, double, double, double, double, double> doubleFunctorB7_ = qextFunctor(&doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctorB7_(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleFunctorB7_(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));


    QEXTFunctor7<void, int, int, int, int, int, int, int> voidFunctor7 = qextFunctor7(&voidFunction7);
    voidFunctor7(1, 2, 3, 4, 5, 6, 7);
    QEXTFunctor7<int, int, int, int, int, int, int, int> intFunctor7 = qextFunctor7(&intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intFunctor7(1, 2, 3, 4, 5, 6, 7));
    QEXTFunctor7<double, double, double, double, double, double, double, double> doubleFunctor7 = qextFunctor7(&doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctor7(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTFunctor7<void, bool, int, int, int, int, int, int> voidFunctorB7 = qextFunctor7(&voidFunctionB7);
    voidFunctorB7(1, 2, 3, 4, 5, 6, 7);
    QEXTFunctor7<int, bool, int, int, int, int, int, int> intFunctorB7 = qextFunctor7(&intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intFunctorB7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intFunctorB7(false, 2, 3, 4, 5, 6, 7));
    QEXTFunctor7<double, bool, double, double, double, double, double, double> doubleFunctorB7 = qextFunctor7(&doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctorB7(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleFunctorB7(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));


    QEXTFunctor<void, int, int, int, int, int, int, int> voidFunctor = qextFunctor(&voidFunction7);
    voidFunctor(1, 2, 3, 4, 5, 6, 7);
    QEXTFunctor<int, int, int, int, int, int, int, int> intFunctor = qextFunctor(&intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTFunctor<double, double, double, double, double, double, double, double> doubleFunctor = qextFunctor(&doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTFunctor<void, bool, int, int, int, int, int, int> voidFunctorB = qextFunctor(&voidFunctionB7);
    voidFunctorB(1, 2, 3, 4, 5, 6, 7);
    QEXTFunctor<int, bool, int, int, int, int, int, int> intFunctorB = qextFunctor(&intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTFunctor<double, bool, double, double, double, double, double, double> doubleFunctorB = qextFunctor(&doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
}

QTEST_APPLESS_MAIN(QEXTFunctorTest)

#include <tst_qextfunctor.moc>
