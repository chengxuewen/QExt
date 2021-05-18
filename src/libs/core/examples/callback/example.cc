#include <iostream>
#include <string>
#include <QDebug>

#include "callback.h"
#include "qextcallback.h"



class TButton0 {
public:
    TButton0(const QEXTCallback<void>& cb)
        : qextNotify(cb)
    {
        QEXTCallback<void> notify;
        qDebug() << notify.isNull();
        notify = qextNotify;
        qDebug() << notify.isNull();
        notify();
    }

    void click()
    {
        qextNotify();
    }

private:
    QEXTCallback<void> qextNotify;
};

void funcCallback0()
{
    std::cout << "funcCallback0" << std::endl;
}

class TButton1 {
public:
    TButton1(const QEXTCallback<void, int>& cb)
        : qextNotify(cb)
    {

    }

    void click()
    {
        qextNotify(2);
    }

private:
    QEXTCallback<void, int> qextNotify;
};

void funcCallback1(int i)
{
    std::cout << "funcCallback1" << std::endl;
}

class TButton2 {
public:
    TButton2(const QEXTCallback<void, int, int>& cb)
        : qextNotify(cb)
    {
    }

    void click()
    {
        qextNotify(1, 2);
    }

private:
    QEXTCallback<void, int, int> qextNotify;
};

void funcCallback2(int i, int m)
{
    std::cout << "funcCallback2" << std::endl;
}


class Button {
public:
    Button(const NCallback<void, int>& cb)
        : notify(cb)
    {
    }

    void click(int x = 5)
    {
        notify(x);
    }

private:
    NCallback<void, int> notify;
};

class AnotherButton {
public:
    AnotherButton(const NCallback<int, int, float, std::string>& cb)
        : notify(cb)
    {
    }

    int click(int x = 5, float y = 5.5, std::string z = "Hello World")
    {
        notify(x, y, z);
        return 42;
    }

private:
    NCallback<int, int, float, std::string> notify;
};

class MemberCallback {
public:
    void buttonCB(int x) { std::cout << "Callback called with x = " << x << std::endl; }
    int anotherButtonCB(int x, float y, std::string z)
    {
        std::cout << "Callback called with x = " << x << " y = " << y << " z = " << z << std::endl;
        return 42;
    }

    void funcCallback0()
    {
        std::cout << "MemberCallback::funcCallback0" << std::endl;
    }

    void funcCallback1(int x)
    {
        std::cout << "MemberCallback::funcCallback1" << std::endl;
    }

    void funcCallback2(int x, int y)
    {
        std::cout << "MemberCallback::funcCallback2" << std::endl;
    }
};

void funcCallback(int x)
{
    std::cout << "Callback called with x = " << x << std::endl;
}




int main()
{
    MemberCallback cbClass;

    Button b1(NGenerateCallback((NCallback<void, int>*)0, cbClass, &MemberCallback::buttonCB));
    AnotherButton b2(NGenerateCallback((NCallback<int, int, float, std::string>*)0, cbClass, &MemberCallback::anotherButtonCB));
    Button b3(NGenerateCallback((NCallback<void, int>*)0, &funcCallback));

    TButton0 tButton0(qextGenerateCallback((QEXTCallback<void>*)0, &funcCallback0));
    TButton1 tButton1(qextGenerateCallback((QEXTCallback<void, int>*)0, &funcCallback1));
    TButton2 tButton2(qextGenerateCallback((QEXTCallback<void, int, int>*)0, &funcCallback2));


    TButton0 mButton0(qextGenerateCallback((QEXTCallback<void>*)0, cbClass, &MemberCallback::funcCallback0));
    TButton1 mButton1(qextGenerateCallback((QEXTCallback<void, int>*)0, cbClass, &MemberCallback::funcCallback1));
    TButton2 mButton2(qextGenerateCallback((QEXTCallback<void, int, int>*)0, cbClass, &MemberCallback::funcCallback2));


    b1.click(532);
    std::cout << "With return: " << b2.click(42, 43.5, "Hello Callback") << std::endl;
    b3.click();

    tButton0.click();
    tButton1.click();
    tButton2.click();

    mButton0.click();
    mButton1.click();
    mButton2.click();


    return 0;
}
