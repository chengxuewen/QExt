#include <qextpointerfunctor.h>

#include <QtTest>
#include <QDebug>

void voidFunction0() {
    qDebug() << "voidFunction0";
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

void voidFunctionR1(int &a1) {
    a1++;
}
void voidFunctionR2(int &a1, int &a2) {
    a1++;
    a2++;
}
void voidFunctionR3(int &a1, int &a2, int &a3) {
    a1++;
    a2++;
    a3++;
}
void voidFunctionR4(int &a1, int &a2, int &a3, int &a4) {
    a1++;
    a2++;
    a3++;
    a4++;
}
void voidFunctionR5(int &a1, int &a2, int &a3, int &a4, int &a5) {
    a1++;
    a2++;
    a3++;
    a4++;
    a5++;
}
void voidFunctionR6(int &a1, int &a2, int &a3, int &a4, int &a5, int &a6) {
    a1++;
    a2++;
    a3++;
    a4++;
    a5++;
    a6++;
}
void voidFunctionR7(int &a1, int &a2, int &a3, int &a4, int &a5, int &a6, int &a7) {
    a1++;
    a2++;
    a3++;
    a4++;
    a5++;
    a6++;
    a7++;
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


class QEXTPointerFunctorTest : public QObject
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



void QEXTPointerFunctorTest::testFunctorWith0Arg()
{
    QEXTPointerFunctor0<void> voidFunctor0_ = qextPointerFunctor(&voidFunction0);
    voidFunctor0_();
    QEXTPointerFunctor0<int> intFunctor0_ = qextPointerFunctor(&intFunction0);
    QVERIFY(0 == intFunctor0_());
    QEXTPointerFunctor0<double> doubleFunctor0_ = qextPointerFunctor(&doubleFunction0);
    QVERIFY(0 == doubleFunctor0_());

    QEXTPointerFunctor0<void> voidFunctor0 = qextPointerFunctor0(&voidFunction0);
    voidFunctor0();
    QEXTPointerFunctor0<int> intFunctor0 = qextPointerFunctor0(&intFunction0);
    QVERIFY(0 == intFunctor0());
    QEXTPointerFunctor0<double> doubleFunctor0 = qextPointerFunctor0(&doubleFunction0);
    QVERIFY(0 == doubleFunctor0());

    QEXTPointerFunctor<void> voidFunctor = qextPointerFunctor(&voidFunction0);
    voidFunctor();
    QEXTPointerFunctor<int> intFunctor = qextPointerFunctor(&intFunction0);
    QVERIFY(0 == intFunctor());
    QEXTPointerFunctor<double> doubleFunctor = qextPointerFunctor(&doubleFunction0);
    QVERIFY(0 == doubleFunctor());
}

void QEXTPointerFunctorTest::testFunctorWith1Arg()
{
    QEXTPointerFunctor1<void, int> voidFunctor1_ = qextPointerFunctor(&voidFunction1);
    voidFunctor1_(1);
    QEXTPointerFunctor1<int, int> intFunctor1_ = qextPointerFunctor(&intFunction1);
    QVERIFY(1 == intFunctor1_(1));
    QEXTPointerFunctor1<double, double> doubleFunctor1_ = qextPointerFunctor(&doubleFunction1);
    QVERIFY(1.1 == doubleFunctor1_(1.1));

    QEXTPointerFunctor1<void, bool> voidFunctorB1_ = qextPointerFunctor(&voidFunctionB1);
    voidFunctorB1_(1);
    QEXTPointerFunctor1<int, bool> intFunctorB1_ = qextPointerFunctor(&intFunctionB1);
    QVERIFY(1 == intFunctorB1_(true));
    QVERIFY(0 == intFunctorB1_(false));
    QEXTPointerFunctor1<double, bool> doubleFunctorB1_ = qextPointerFunctor(&doubleFunctionB1);
    QVERIFY(1 == doubleFunctorB1_(true));
    QVERIFY(0 == doubleFunctorB1_(false));


    QEXTPointerFunctor1<void, int> voidFunctor1 = qextPointerFunctor1(&voidFunction1);
    voidFunctor1(1);
    QEXTPointerFunctor1<int, int> intFunctor1 = qextPointerFunctor1(&intFunction1);
    QVERIFY(1 == intFunctor1(1));
    QEXTPointerFunctor1<double, double> doubleFunctor1 = qextPointerFunctor1(&doubleFunction1);
    QVERIFY(1.1 == doubleFunctor1(1.1));

    QEXTPointerFunctor1<void, bool> voidFunctorB1 = qextPointerFunctor1(&voidFunctionB1);
    voidFunctorB1(1);
    QEXTPointerFunctor1<int, bool> intFunctorB1 = qextPointerFunctor1(&intFunctionB1);
    QVERIFY(1 == intFunctorB1(true));
    QVERIFY(0 == intFunctorB1(false));
    QEXTPointerFunctor1<double, bool> doubleFunctorB1 = qextPointerFunctor1(&doubleFunctionB1);
    QVERIFY(1 == doubleFunctorB1(true));
    QVERIFY(0 == doubleFunctorB1(false));


    QEXTPointerFunctor<void, int> voidFunctor = qextPointerFunctor(&voidFunction1);
    voidFunctor(1);
    QEXTPointerFunctor<int, int> intFunctor = qextPointerFunctor(&intFunction1);
    QVERIFY(1 == intFunctor(1));
    QEXTPointerFunctor<double, double> doubleFunctor = qextPointerFunctor(&doubleFunction1);
    QVERIFY(1.1 == doubleFunctor(1.1));

    QEXTPointerFunctor<void, bool> voidFunctorB = qextPointerFunctor(&voidFunctionB1);
    voidFunctorB(1);
    QEXTPointerFunctor<int, bool> intFunctorB = qextPointerFunctor(&intFunctionB1);
    QVERIFY(1 == intFunctorB(true));
    QVERIFY(0 == intFunctorB(false));
    QEXTPointerFunctor<double, bool> doubleFunctorB = qextPointerFunctor(&doubleFunctionB1);
    QVERIFY(1 == doubleFunctorB(true));
    QVERIFY(0 == doubleFunctorB(false));

    QEXTPointerFunctor<void, int&> voidFunctorR = qextPointerFunctor(&voidFunctionR1);
    int a1 = 1;
    voidFunctorR(a1);
    QVERIFY(2 == a1);
}

void QEXTPointerFunctorTest::testFunctorWith2Arg()
{
    QEXTPointerFunctor2<void, int, int> voidFunctor2_ = qextPointerFunctor(&voidFunction2);
    voidFunctor2_(1, 2);
    QEXTPointerFunctor2<int, int, int> intFunctor2_ = qextPointerFunctor(&intFunction2);
    QVERIFY(1 + 2 == intFunctor2_(1, 2));
    QEXTPointerFunctor2<double, double, double> doubleFunctor2_ = qextPointerFunctor(&doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleFunctor2_(1.1, 2.2));

    QEXTPointerFunctor2<void, bool, int> voidFunctorB2_ = qextPointerFunctor(&voidFunctionB2);
    voidFunctorB2_(true, 2);
    QEXTPointerFunctor2<int, bool, int> intFunctorB2_ = qextPointerFunctor(&intFunctionB2);
    QVERIFY(2 == intFunctorB2_(true, 2));
    QVERIFY(0 == intFunctorB2_(false, 2));
    QEXTPointerFunctor2<double, bool, double> doubleFunctorB2_ = qextPointerFunctor(&doubleFunctionB2);
    QVERIFY(2.2 == doubleFunctorB2_(true, 2.2));
    QVERIFY(0 == doubleFunctorB2_(false, 2.2));


    QEXTPointerFunctor2<void, int, int> voidFunctor2 = qextPointerFunctor2(&voidFunction2);
    voidFunctor2(1, 2);
    QEXTPointerFunctor2<int, int, int> intFunctor2 = qextPointerFunctor2(&intFunction2);
    QVERIFY(1 + 2 == intFunctor2(1, 2));
    QEXTPointerFunctor2<double, double, double> doubleFunctor2 = qextPointerFunctor2(&doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleFunctor2(1.1, 2.2));

    QEXTPointerFunctor2<void, bool, int> voidFunctorB2 = qextPointerFunctor2(&voidFunctionB2);
    voidFunctorB2(true, 2);
    QEXTPointerFunctor2<int, bool, int> intFunctorB2 = qextPointerFunctor2(&intFunctionB2);
    QVERIFY(2 == intFunctorB2(true, 2));
    QVERIFY(0 == intFunctorB2(false, 2));
    QEXTPointerFunctor2<double, bool, double> doubleFunctorB2 = qextPointerFunctor2(&doubleFunctionB2);
    QVERIFY(2.2 == doubleFunctorB2(true, 2.2));
    QVERIFY(0 == doubleFunctorB2(false, 2.2));


    QEXTPointerFunctor<void, int, int> voidFunctor = qextPointerFunctor(&voidFunction2);
    voidFunctor(1, 2);
    QEXTPointerFunctor<int, int, int> intFunctor = qextPointerFunctor(&intFunction2);
    QVERIFY(1 + 2 == intFunctor(1, 2));
    QEXTPointerFunctor<double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction2);
    QVERIFY(1.1 + 2.2 == doubleFunctor(1.1, 2.2));

    QEXTPointerFunctor<void, bool, int> voidFunctorB = qextPointerFunctor(&voidFunctionB2);
    voidFunctorB(true, 2);
    QEXTPointerFunctor<int, bool, int> intFunctorB = qextPointerFunctor(&intFunctionB2);
    QVERIFY(2 == intFunctorB(true, 2));
    QVERIFY(0 == intFunctorB(false, 2));
    QEXTPointerFunctor<double, bool, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB2);
    QVERIFY(2.2 == doubleFunctorB(true, 2.2));
    QVERIFY(0 == doubleFunctorB(false, 2.2));

    QEXTPointerFunctor<void, int&, int&> voidFunctorR = qextPointerFunctor(&voidFunctionR2);
    int a1 = 1;
    int a2 = 2;
    voidFunctorR(a1, a2);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
}

void QEXTPointerFunctorTest::testFunctorWith3Arg()
{
    QEXTPointerFunctor3<void, int, int, int> voidFunctor3_ = qextPointerFunctor(&voidFunction3);
    voidFunctor3_(1, 2, 3);
    QEXTPointerFunctor3<int, int, int, int> intFunctor3_ = qextPointerFunctor(&intFunction3);
    QVERIFY(1 + 2 + 3 == intFunctor3_(1, 2, 3));
    QEXTPointerFunctor3<double, double, double, double> doubleFunctor3_ = qextPointerFunctor(&doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleFunctor3_(1.1, 2.2, 3.3));

    QEXTPointerFunctor3<void, bool, int, int> voidFunctorB3_ = qextPointerFunctor(&voidFunctionB3);
    voidFunctorB3_(true, 2, 3);
    QEXTPointerFunctor3<int, bool, int, int> intFunctorB3_ = qextPointerFunctor(&intFunctionB3);
    QVERIFY(2 + 3 == intFunctorB3_(true, 2, 3));
    QVERIFY(2 * 3 == intFunctorB3_(false, 2, 3));
    QEXTPointerFunctor3<double, bool, double, double> doubleFunctorB3_ = qextPointerFunctor(&doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleFunctorB3_(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleFunctorB3_(false, 2.2, 3.3));


    QEXTPointerFunctor3<void, int, int, int> voidFunctor3 = qextPointerFunctor3(&voidFunction3);
    voidFunctor3(1, 2, 3);
    QEXTPointerFunctor3<int, int, int, int> intFunctor3 = qextPointerFunctor3(&intFunction3);
    QVERIFY(1 + 2 + 3 == intFunctor3(1, 2, 3));
    QEXTPointerFunctor3<double, double, double, double> doubleFunctor3 = qextPointerFunctor3(&doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleFunctor3(1.1, 2.2, 3.3));

    QEXTPointerFunctor3<void, bool, int, int> voidFunctorB3 = qextPointerFunctor3(&voidFunctionB3);
    voidFunctorB3(true, 2, 3);
    QEXTPointerFunctor3<int, bool, int, int> intFunctorB3 = qextPointerFunctor3(&intFunctionB3);
    QVERIFY(2 + 3 == intFunctorB3(true, 2, 3));
    QVERIFY(2 * 3 == intFunctorB3(false, 2, 3));
    QEXTPointerFunctor3<double, bool, double, double> doubleFunctorB3 = qextPointerFunctor3(&doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleFunctorB3(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleFunctorB3(false, 2.2, 3.3));


    QEXTPointerFunctor<void, int, int, int> voidFunctor = qextPointerFunctor(&voidFunction3);
    voidFunctor(1, 2, 3);
    QEXTPointerFunctor<int, int, int, int> intFunctor = qextPointerFunctor(&intFunction3);
    QVERIFY(1 + 2 + 3 == intFunctor(1, 2, 3));
    QEXTPointerFunctor<double, double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction3);
    QVERIFY(1.1 + 2.2 + 3.3 == doubleFunctor(1.1, 2.2, 3.3));

    QEXTPointerFunctor<void, bool, int, int> voidFunctorB = qextPointerFunctor(&voidFunctionB3);
    voidFunctorB3(true, 2, 3);
    QEXTPointerFunctor<int, bool, int, int> intFunctorB = qextPointerFunctor(&intFunctionB3);
    QVERIFY(2 + 3 == intFunctorB(true, 2, 3));
    QVERIFY(2 * 3 == intFunctorB(false, 2, 3));
    QEXTPointerFunctor<double, bool, double, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB3);
    QVERIFY(2.2 + 3.3 == doubleFunctorB(true, 2.2, 3.3));
    QVERIFY(2.2 * 3.3 == doubleFunctorB(false, 2.2, 3.3));

    QEXTPointerFunctor<void, int&, int&, int&> voidFunctorR = qextPointerFunctor(&voidFunctionR3);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    voidFunctorR(a1, a2, a3);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
}

void QEXTPointerFunctorTest::testFunctorWith4Arg()
{
    QEXTPointerFunctor4<void, int, int, int, int> voidFunctor4_ = qextPointerFunctor(&voidFunction4);
    voidFunctor4_(1, 2, 3, 4);
    QEXTPointerFunctor4<int, int, int, int, int> intFunctor4_ = qextPointerFunctor(&intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intFunctor4_(1, 2, 3, 4));
    QEXTPointerFunctor4<double, double, double, double, double> doubleFunctor4_ = qextPointerFunctor(&doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleFunctor4_(1.1, 2.2, 3.3, 4.4));

    QEXTPointerFunctor4<void, bool, int, int, int> voidFunctorB4_ = qextPointerFunctor(&voidFunctionB4);
    voidFunctorB4_(1, 2, 3, 4);
    QEXTPointerFunctor4<int, bool, int, int, int> intFunctorB4_ = qextPointerFunctor(&intFunctionB4);
    QVERIFY(2 + 3 + 4 == intFunctorB4_(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intFunctorB4_(false, 2, 3, 4));
    QEXTPointerFunctor4<double, bool, double, double, double> doubleFunctorB4_ = qextPointerFunctor(&doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleFunctorB4_(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleFunctorB4_(false, 2.2, 3.3, 4.4));


    QEXTPointerFunctor4<void, int, int, int, int> voidFunctor4 = qextPointerFunctor4(&voidFunction4);
    voidFunctor4(1, 2, 3, 4);
    QEXTPointerFunctor4<int, int, int, int, int> intFunctor4 = qextPointerFunctor4(&intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intFunctor4(1, 2, 3, 4));
    QEXTPointerFunctor4<double, double, double, double, double> doubleFunctor4 = qextPointerFunctor4(&doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleFunctor4(1.1, 2.2, 3.3, 4.4));

    QEXTPointerFunctor4<void, bool, int, int, int> voidFunctorB4 = qextPointerFunctor4(&voidFunctionB4);
    voidFunctorB4(1, 2, 3, 4);
    QEXTPointerFunctor4<int, bool, int, int, int> intFunctorB4 = qextPointerFunctor4(&intFunctionB4);
    QVERIFY(2 + 3 + 4 == intFunctorB4(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intFunctorB4(false, 2, 3, 4));
    QEXTPointerFunctor4<double, bool, double, double, double> doubleFunctorB4 = qextPointerFunctor4(&doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleFunctorB4(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleFunctorB4(false, 2.2, 3.3, 4.4));


    QEXTPointerFunctor<void, bool, int, int, int> voidFunctorB = qextPointerFunctor(&voidFunctionB4);
    voidFunctorB(1, 2, 3, 4);
    QEXTPointerFunctor<int, bool, int, int, int> intFunctorB = qextPointerFunctor(&intFunctionB4);
    QVERIFY(2 + 3 + 4 == intFunctorB(true, 2, 3, 4));
    QVERIFY(2 * 3 * 4 == intFunctorB(false, 2, 3, 4));
    QEXTPointerFunctor<double, bool, double, double, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB4);
    QVERIFY(2.2 + 3.3 + 4.4 == doubleFunctorB(true, 2.2, 3.3, 4.4));
    QVERIFY(2.2 * 3.3 * 4.4 == doubleFunctorB(false, 2.2, 3.3, 4.4));


    QEXTPointerFunctor<void, int, int, int, int> voidFunctor = qextPointerFunctor(&voidFunction4);
    voidFunctor(1, 2, 3, 4);
    QEXTPointerFunctor<int, int, int, int, int> intFunctor = qextPointerFunctor(&intFunction4);
    QVERIFY(1 + 2 + 3 + 4 == intFunctor(1, 2, 3, 4));
    QEXTPointerFunctor<double, double, double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction4);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 == doubleFunctor(1.1, 2.2, 3.3, 4.4));

    QEXTPointerFunctor<void, int&, int&, int&, int&> voidFunctorR = qextPointerFunctor(&voidFunctionR4);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    voidFunctorR(a1, a2, a3, a4);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
    QVERIFY(5 == a4);
}

void QEXTPointerFunctorTest::testFunctorWith5Arg()
{
    QEXTPointerFunctor5<void, int, int, int, int, int> voidFunctor5_ = qextPointerFunctor(&voidFunction5);
    voidFunctor5_(1, 2, 3, 4, 5);
    QEXTPointerFunctor5<int, int, int, int, int, int> intFunctor5_ = qextPointerFunctor(&intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intFunctor5_(1, 2, 3, 4, 5));
    QEXTPointerFunctor5<double, double, double, double, double, double> doubleFunctor5_ = qextPointerFunctor(&doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleFunctor5_(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTPointerFunctor5<void, bool, int, int, int, int> voidFunctorB5_ = qextPointerFunctor(&voidFunctionB5);
    voidFunctorB5_(true, 2, 3, 4, 5);
    QEXTPointerFunctor5<int, bool, int, int, int, int> intFunctorB5_ = qextPointerFunctor(&intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intFunctorB5_(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intFunctorB5_(false, 2, 3, 4, 5));
    QEXTPointerFunctor5<double, bool, double, double, double, double> doubleFunctorB5_ = qextPointerFunctor(&doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleFunctorB5_(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleFunctorB5_(false, 2.2, 3.3, 4.4, 5.5));


    QEXTPointerFunctor5<void, int, int, int, int, int> voidFunctor5 = qextPointerFunctor5(&voidFunction5);
    voidFunctor5(1, 2, 3, 4, 5);
    QEXTPointerFunctor5<int, int, int, int, int, int> intFunctor5 = qextPointerFunctor5(&intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intFunctor5(1, 2, 3, 4, 5));
    QEXTPointerFunctor5<double, double, double, double, double, double> doubleFunctor5 = qextPointerFunctor5(&doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleFunctor5(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTPointerFunctor5<void, bool, int, int, int, int> voidFunctorB5 = qextPointerFunctor5(&voidFunctionB5);
    voidFunctorB5(true, 2, 3, 4, 5);
    QEXTPointerFunctor5<int, bool, int, int, int, int> intFunctorB5 = qextPointerFunctor5(&intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intFunctorB5(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intFunctorB5(false, 2, 3, 4, 5));
    QEXTPointerFunctor5<double, bool, double, double, double, double> doubleFunctorB5 = qextPointerFunctor5(&doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleFunctorB5(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleFunctorB5(false, 2.2, 3.3, 4.4, 5.5));


    QEXTPointerFunctor<void, int, int, int, int, int> voidFunctor = qextPointerFunctor(&voidFunction5);
    voidFunctor(1, 2, 3, 4, 5);
    QEXTPointerFunctor<int, int, int, int, int, int> intFunctor = qextPointerFunctor(&intFunction5);
    QVERIFY(1 + 2 + 3 + 4 + 5 == intFunctor(1, 2, 3, 4, 5));
    QEXTPointerFunctor<double, double, double, double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction5);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5));

    QEXTPointerFunctor<void, bool, int, int, int, int> voidFunctorB = qextPointerFunctor(&voidFunctionB5);
    voidFunctorB(true, 2, 3, 4, 5);
    QEXTPointerFunctor<int, bool, int, int, int, int> intFunctorB = qextPointerFunctor(&intFunctionB5);
    QVERIFY(2 + 3 + 4 + 5 == intFunctorB(true, 2, 3, 4, 5));
    QVERIFY(2 * 3 * 4 * 5 == intFunctorB(false, 2, 3, 4, 5));
    QEXTPointerFunctor<double, bool, double, double, double, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB5);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5));

    QEXTPointerFunctor<void, int&, int&, int&, int&, int&> voidFunctorR = qextPointerFunctor(&voidFunctionR5);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    int a5 = 5;
    voidFunctorR(a1, a2, a3, a4, a5);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
    QVERIFY(5 == a4);
    QVERIFY(6 == a5);
}

void QEXTPointerFunctorTest::testFunctorWith6Arg()
{
    QEXTPointerFunctor6<void, int, int, int, int, int, int> voidFunctor6_ = qextPointerFunctor(&voidFunction6);
    voidFunctor6_(1, 2, 3, 4, 5, 6);
    QEXTPointerFunctor6<int, int, int, int, int, int, int> intFunctor6_ = qextPointerFunctor(&intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intFunctor6_(1, 2, 3, 4, 5, 6));
    QEXTPointerFunctor6<double, double, double, double, double, double, double> doubleFunctor6_ = qextPointerFunctor(&doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctor6_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTPointerFunctor6<void, bool, int, int, int, int, int> voidFunctorB6_ = qextPointerFunctor(&voidFunctionB6);
    voidFunctorB6_(true, 2, 3, 4, 5, 6);
    QEXTPointerFunctor6<int, bool, int, int, int, int, int> intFunctorB6_ = qextPointerFunctor(&intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intFunctorB6_(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intFunctorB6_(false, 2, 3, 4, 5, 6));
    QEXTPointerFunctor6<double, bool, double, double, double, double, double> doubleFunctorB6_ = qextPointerFunctor(&doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctorB6_(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleFunctorB6_(false, 2.2, 3.3, 4.4, 5.5, 6.6));


    QEXTPointerFunctor6<void, int, int, int, int, int, int> voidFunctor6 = qextPointerFunctor6(&voidFunction6);
    voidFunctor6(1, 2, 3, 4, 5, 6);
    QEXTPointerFunctor6<int, int, int, int, int, int, int> intFunctor6 = qextPointerFunctor6(&intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intFunctor6(1, 2, 3, 4, 5, 6));
    QEXTPointerFunctor6<double, double, double, double, double, double, double> doubleFunctor6 = qextPointerFunctor6(&doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctor6(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTPointerFunctor6<void, bool, int, int, int, int, int> voidFunctorB6 = qextPointerFunctor6(&voidFunctionB6);
    voidFunctorB6(true, 2, 3, 4, 5, 6);
    QEXTPointerFunctor6<int, bool, int, int, int, int, int> intFunctorB6 = qextPointerFunctor6(&intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intFunctorB6(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intFunctorB6(false, 2, 3, 4, 5, 6));
    QEXTPointerFunctor6<double, bool, double, double, double, double, double> doubleFunctorB6 = qextPointerFunctor6(&doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctorB6(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleFunctorB6(false, 2.2, 3.3, 4.4, 5.5, 6.6));


    QEXTPointerFunctor<void, int, int, int, int, int, int> voidFunctor = qextPointerFunctor(&voidFunction6);
    voidFunctor(1, 2, 3, 4, 5, 6);
    QEXTPointerFunctor<int, int, int, int, int, int, int> intFunctor = qextPointerFunctor(&intFunction6);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 == intFunctor(1, 2, 3, 4, 5, 6));
    QEXTPointerFunctor<double, double, double, double, double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction6);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTPointerFunctor<void, bool, int, int, int, int, int> voidFunctorB = qextPointerFunctor(&voidFunctionB6);
    voidFunctorB(true, 2, 3, 4, 5, 6);
    QEXTPointerFunctor<int, bool, int, int, int, int, int> intFunctorB = qextPointerFunctor(&intFunctionB6);
    QVERIFY(2 + 3 + 4 + 5 + 6 == intFunctorB(true, 2, 3, 4, 5, 6));
    QVERIFY(2 * 3 * 4 * 5 * 6 == intFunctorB(false, 2, 3, 4, 5, 6));
    QEXTPointerFunctor<double, bool, double, double, double, double, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB6);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6));

    QEXTPointerFunctor<void, int&, int&, int&, int&, int&, int&> voidFunctorR = qextPointerFunctor(&voidFunctionR6);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    int a5 = 5;
    int a6 = 6;
    voidFunctorR(a1, a2, a3, a4, a5, a6);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
    QVERIFY(5 == a4);
    QVERIFY(6 == a5);
    QVERIFY(7 == a6);
}

void QEXTPointerFunctorTest::testFunctorWith7Arg()
{
    QEXTPointerFunctor7<void, int, int, int, int, int, int, int> voidFunctor7_ = qextPointerFunctor(&voidFunction7);
    voidFunctor7_(1, 2, 3, 4, 5, 6, 7);
    QEXTPointerFunctor7<int, int, int, int, int, int, int, int> intFunctor7_ = qextPointerFunctor(&intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intFunctor7_(1, 2, 3, 4, 5, 6, 7));
    QEXTPointerFunctor7<double, double, double, double, double, double, double, double> doubleFunctor7_ = qextPointerFunctor(&doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctor7_(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTPointerFunctor7<void, bool, int, int, int, int, int, int> voidFunctorB7_ = qextPointerFunctor(&voidFunctionB7);
    voidFunctorB7_(1, 2, 3, 4, 5, 6, 7);
    QEXTPointerFunctor7<int, bool, int, int, int, int, int, int> intFunctorB7_ = qextPointerFunctor(&intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intFunctorB7_(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intFunctorB7_(false, 2, 3, 4, 5, 6, 7));
    QEXTPointerFunctor7<double, bool, double, double, double, double, double, double> doubleFunctorB7_ = qextPointerFunctor(&doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctorB7_(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleFunctorB7_(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));


    QEXTPointerFunctor7<void, int, int, int, int, int, int, int> voidFunctor7 = qextPointerFunctor7(&voidFunction7);
    voidFunctor7(1, 2, 3, 4, 5, 6, 7);
    QEXTPointerFunctor7<int, int, int, int, int, int, int, int> intFunctor7 = qextPointerFunctor7(&intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intFunctor7(1, 2, 3, 4, 5, 6, 7));
    QEXTPointerFunctor7<double, double, double, double, double, double, double, double> doubleFunctor7 = qextPointerFunctor7(&doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctor7(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTPointerFunctor7<void, bool, int, int, int, int, int, int> voidFunctorB7 = qextPointerFunctor7(&voidFunctionB7);
    voidFunctorB7(1, 2, 3, 4, 5, 6, 7);
    QEXTPointerFunctor7<int, bool, int, int, int, int, int, int> intFunctorB7 = qextPointerFunctor7(&intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intFunctorB7(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intFunctorB7(false, 2, 3, 4, 5, 6, 7));
    QEXTPointerFunctor7<double, bool, double, double, double, double, double, double> doubleFunctorB7 = qextPointerFunctor7(&doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctorB7(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleFunctorB7(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));


    QEXTPointerFunctor<void, int, int, int, int, int, int, int> voidFunctor = qextPointerFunctor(&voidFunction7);
    voidFunctor(1, 2, 3, 4, 5, 6, 7);
    QEXTPointerFunctor<int, int, int, int, int, int, int, int> intFunctor = qextPointerFunctor(&intFunction7);
    QVERIFY(1 + 2 + 3 + 4 + 5 + 6 + 7 == intFunctor(1, 2, 3, 4, 5, 6, 7));
    QEXTPointerFunctor<double, double, double, double, double, double, double, double> doubleFunctor = qextPointerFunctor(&doubleFunction7);
    QVERIFY(1.1 + 2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctor(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));

    QEXTPointerFunctor<void, bool, int, int, int, int, int, int> voidFunctorB = qextPointerFunctor(&voidFunctionB7);
    voidFunctorB(1, 2, 3, 4, 5, 6, 7);
    QEXTPointerFunctor<int, bool, int, int, int, int, int, int> intFunctorB = qextPointerFunctor(&intFunctionB7);
    QVERIFY(2 + 3 + 4 + 5 + 6 + 7 == intFunctorB(true, 2, 3, 4, 5, 6, 7));
    QVERIFY(2 * 3 * 4 * 5 * 6 * 7 == intFunctorB(false, 2, 3, 4, 5, 6, 7));
    QEXTPointerFunctor<double, bool, double, double, double, double, double, double> doubleFunctorB = qextPointerFunctor(&doubleFunctionB7);
    QVERIFY(2.2 + 3.3 + 4.4 + 5.5 + 6.6 + 7.7 == doubleFunctorB(true, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));
    QVERIFY(2.2 * 3.3 * 4.4 * 5.5 * 6.6 * 7.7 == doubleFunctorB(false, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7));


    QEXTPointerFunctor<void, int&, int&, int&, int&, int&, int&, int&> voidFunctorR = qextPointerFunctor(&voidFunctionR7);
    int a1 = 1;
    int a2 = 2;
    int a3 = 3;
    int a4 = 4;
    int a5 = 5;
    int a6 = 6;
    int a7 = 7;
    voidFunctorR(a1, a2, a3, a4, a5, a6, a7);
    QVERIFY(2 == a1);
    QVERIFY(3 == a2);
    QVERIFY(4 == a3);
    QVERIFY(5 == a4);
    QVERIFY(6 == a5);
    QVERIFY(7 == a6);
    QVERIFY(8 == a7);
}

QTEST_APPLESS_MAIN(QEXTPointerFunctorTest)

#include <tst_qextpointerfunctor.moc>
