
#include <qextargument.h>

#include <QDebug>

#include <algorithm>
#include <iostream>
#include <vector>


using namespace std;

template<class T1>
class SlotBase
{
public:
    virtual void Exec(T1 param1) = 0;
    virtual ~SlotBase() {}
};

template<class T, typename T1>
class SlotImpl : public SlotBase<T1>
{
public:
    SlotImpl(T* pObj, void (T::*func)(T1) )
    {
        m_pObj = pObj;
        m_Func = func;
    }

    void Exec( T1 param1)
    {
        (m_pObj->*m_Func)(param1);
    }

private:
    T* m_pObj;
    void (T::*m_Func)(T1);
};

template<class T1>
class Slot
{
public:
    template<class T>
    Slot(T* pObj, void (T::*func)(T1))
    {
        m_pSlotBase = new SlotImpl<T,T1>(pObj, func);
    }

    ~Slot()
    {
        delete m_pSlotBase;
    }

    void Exec(T1 param1)
    {
        m_pSlotBase->Exec(param1);
    }

private:
    SlotBase<T1>* m_pSlotBase;
};

template<class T1>
class Signal
{
public:
    template<class T>
    void Bind(T* pObj, void (T::*func)(T1))
    {
        m_pSlotSet.push_back( new Slot<T1>(pObj,func) );
    }

    ~Signal()
    {
        for(int i=0;i<(int)m_pSlotSet.size();i++)
        {
            delete m_pSlotSet[i];
        }
    }

    void operator()(T1 param1)
    {
        for(int i=0;i<(int)m_pSlotSet.size();i++)
        {
            m_pSlotSet[i]->Exec(param1);
        }
    }

private:
    vector< Slot<T1>* > m_pSlotSet;
};

#define Connect( sender, signal, receiver, method) ( (sender)->signal.Bind(receiver, method) )

class A
{
public:
    void FuncOfA(int param)
    {
        printf("A::FuncOfA(%d)\n", param);
    }
};

class B
{
public:
    void FuncOfB(int param)
    {
        printf("B::FuncOfB(%d)\n", param);
    }
};

class C
{
public:
    C()
    {
        m_Value = 0;
    }
    void SetValue(int value)
    {
        if(m_Value != value)
        {
            m_Value = value;
            ValueChanged(m_Value);
        }
    }

public:
    Signal<int> ValueChanged;

private:
    int m_Value;
};




class Test1
{
public:
    Test1() : m_num(1) {}

    void print() {
        qDebug() << "Test print";
    }

    int m_num;
};

class Test2 : public Test1
{
public:
    Test2() {}
};



double average(int num,...)
{

    va_list valist;
    double sum = 0.0;
    int i;

    /* 为 num 个参数初始化 valist */
    va_start(valist, num);

    /* 访问所有赋给 valist 的参数 */
    for (i = 0; i < num; i++)
    {
        sum += va_arg(valist, int);
    }
    /* 清理为 valist 保留的内存 */
    va_end(valist);

    return sum/num;
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    //    Test1 test = Test2();
    //    QEXTGenericArgument arg = QEXT_ARG(Test1, test);
    //    qWarning() << arg.name();
    //    (static_cast<Test1 *>(arg.data()))->print();


    //    A* pA = new A;
    //    B* pB = new B;
    //    C* pC = new C;

    //    Connect(pC, ValueChanged, pA, &A::FuncOfA);
    //    Connect(pC, ValueChanged, pB, &B::FuncOfB);

    //    pC->SetValue(10);
    //    pC->SetValue(5);
    //    pC->SetValue(5);

    //    delete pC;
    //    delete pB;
    //    delete pA;

    //    scanf("%*s");

    printf("Average of 2, 3, 4, 5 = %f\n", average(4, 2,3,4,5));
    printf("Average of 5, 10, 15 = %f\n", average(3, 5,10,15));


    return 0;
}
