#ifndef QEXTFUNCTIONS_H
#define QEXTFUNCTIONS_H

#include <qextGlobal.h>

#include <string>

static std::string sg_functionString = "";

void voidFunction0()
{
    sg_functionString = "voidFunction0";
}
void voidFunction1(int a1)
{
    Q_UNUSED(a1)
    sg_functionString = "voidFunction1";
}
void voidFunction2(int a1, int a2)
{
    Q_UNUSED(a1)
    Q_UNUSED(a2)
    sg_functionString = "voidFunction2";
}
void voidFunction3(int a1, int a2, int a3)
{
    Q_UNUSED(a1)
    Q_UNUSED(a2)
    Q_UNUSED(a3)
    sg_functionString = "voidFunction3";
}
void voidFunction4(int a1, int a2, int a3, int a4)
{
    Q_UNUSED(a1)
    Q_UNUSED(a2)
    Q_UNUSED(a3)
    Q_UNUSED(a4)
    sg_functionString = "voidFunction4";
}
void voidFunction5(int a1, int a2, int a3, int a4, int a5)
{
    Q_UNUSED(a1)
    Q_UNUSED(a2)
    Q_UNUSED(a3)
    Q_UNUSED(a4)
    Q_UNUSED(a5)
    sg_functionString = "voidFunction5";
}
void voidFunction6(int a1, int a2, int a3, int a4, int a5, int a6)
{
    Q_UNUSED(a1)
    Q_UNUSED(a2)
    Q_UNUSED(a3)
    Q_UNUSED(a4)
    Q_UNUSED(a5)
    Q_UNUSED(a6)
    sg_functionString = "voidFunction6";
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
    sg_functionString = "voidFunction7";
}
void voidFunctionB1(bool a1)
{
    Q_UNUSED(a1)
    sg_functionString = "voidFunctionB1";
}
void voidFunctionB2(bool a1, int a2)
{
    Q_UNUSED(a1)
    Q_UNUSED(a2)
    sg_functionString = "voidFunctionB2";
}
void voidFunctionB3(bool a1, int a2, int a3)
{
    Q_UNUSED(a1)
    Q_UNUSED(a2)
    Q_UNUSED(a3)
    sg_functionString = "voidFunctionB3";
}
void voidFunctionB4(bool a1, int a2, int a3, int a4)
{
    Q_UNUSED(a1)
    Q_UNUSED(a2)
    Q_UNUSED(a3)
    Q_UNUSED(a4)
    sg_functionString = "voidFunctionB4";
}
void voidFunctionB5(bool a1, int a2, int a3, int a4, int a5)
{
    Q_UNUSED(a1)
    Q_UNUSED(a2)
    Q_UNUSED(a3)
    Q_UNUSED(a4)
    Q_UNUSED(a5)
    sg_functionString = "voidFunctionB5";
}
void voidFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6)
{
    Q_UNUSED(a1)
    Q_UNUSED(a2)
    Q_UNUSED(a3)
    Q_UNUSED(a4)
    Q_UNUSED(a5)
    Q_UNUSED(a6)
    sg_functionString = "voidFunctionB6";
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
    sg_functionString = "voidFunctionB7";
}

void voidFunctionR1(int &a1)
{
    a1++;
}
void voidFunctionR2(int &a1, int &a2)
{
    a1++;
    a2++;
}
void voidFunctionR3(int &a1, int &a2, int &a3)
{
    a1++;
    a2++;
    a3++;
}
void voidFunctionR4(int &a1, int &a2, int &a3, int &a4)
{
    a1++;
    a2++;
    a3++;
    a4++;
}
void voidFunctionR5(int &a1, int &a2, int &a3, int &a4, int &a5)
{
    a1++;
    a2++;
    a3++;
    a4++;
    a5++;
}
void voidFunctionR6(int &a1, int &a2, int &a3, int &a4, int &a5, int &a6)
{
    a1++;
    a2++;
    a3++;
    a4++;
    a5++;
    a6++;
}
void voidFunctionR7(int &a1, int &a2, int &a3, int &a4, int &a5, int &a6, int &a7)
{
    a1++;
    a2++;
    a3++;
    a4++;
    a5++;
    a6++;
    a7++;
}

int intFunction0()
{
    return 0;
}
int intFunction1(int a1)
{
    return a1;
}
int intFunction2(int a1, int a2)
{
    return a1 + a2;
}
int intFunction3(int a1, int a2, int a3)
{
    return a1 + a2 + a3;
}
int intFunction4(int a1, int a2, int a3, int a4)
{
    return a1 + a2 + a3 + a4;
}
int intFunction5(int a1, int a2, int a3, int a4, int a5)
{
    return a1 + a2 + a3 + a4 + a5;
}
int intFunction6(int a1, int a2, int a3, int a4, int a5, int a6)
{
    return a1 + a2 + a3 + a4 + a5 + a6;
}
int intFunction7(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    return a1 + a2 + a3 + a4 + a5 + a6 + a7;
}
int intFunctionB1(bool a1)
{
    return a1;
}
int intFunctionB2(bool a1, int a2)
{
    return a1 ? a2 : 0;
}
int intFunctionB3(bool a1, int a2, int a3)
{
    return a1 ? (a2 + a3) : (a2 * a3);
}
int intFunctionB4(bool a1, int a2, int a3, int a4)
{
    return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
}
int intFunctionB5(bool a1, int a2, int a3, int a4, int a5)
{
    return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
}
int intFunctionB6(bool a1, int a2, int a3, int a4, int a5, int a6)
{
    return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
}
int intFunctionB7(bool a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
    return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
}

double doubleFunction0()
{
    return 0;
}
double doubleFunction1(double a1)
{
    return a1;
}
double doubleFunction2(double a1, double a2)
{
    return a1 + a2;
}
double doubleFunction3(double a1, double a2, double a3)
{
    return a1 + a2 + a3;
}
double doubleFunction4(double a1, double a2, double a3, double a4)
{
    return a1 + a2 + a3 + a4;
}
double doubleFunction5(double a1, double a2, double a3, double a4, double a5)
{
    return a1 + a2 + a3 + a4 + a5;
}
double doubleFunction6(double a1, double a2, double a3, double a4, double a5, double a6)
{
    return a1 + a2 + a3 + a4 + a5 + a6;
}
double doubleFunction7(double a1, double a2, double a3, double a4, double a5, double a6, double a7)
{
    return a1 + a2 + a3 + a4 + a5 + a6 + a7;
}
double doubleFunctionB1(bool a1)
{
    return a1;
}
double doubleFunctionB2(bool a1, double a2)
{
    return a1 ? a2 : 0;
}
double doubleFunctionB3(bool a1, double a2, double a3)
{
    return a1 ? (a2 + a3) : (a2 * a3);
}
double doubleFunctionB4(bool a1, double a2, double a3, double a4)
{
    return a1 ? (a2 + a3 + a4) : (a2 * a3 * a4);
}
double doubleFunctionB5(bool a1, double a2, double a3, double a4, double a5)
{
    return a1 ? (a2 + a3 + a4 + a5) : (a2 * a3 * a4 * a5);
}
double doubleFunctionB6(bool a1, double a2, double a3, double a4, double a5, double a6)
{
    return a1 ? (a2 + a3 + a4 + a5 + a6) : (a2 * a3 * a4 * a5 * a6);
}
double doubleFunctionB7(bool a1, double a2, double a3, double a4, double a5, double a6, double a7)
{
    return a1 ? (a2 + a3 + a4 + a5 + a6 + a7) : (a2 * a3 * a4 * a5 * a6 * a7);
}


#endif // QEXTFUNCTION_H
