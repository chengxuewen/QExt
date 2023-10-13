#include <qextSignal.h>
#include <qextFunction.h>
#include <qextBindFunctor.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>
#include <qextConnection.h>

#include <QtTest>
#include <QObject>

#include <iostream>
#include <sstream>
#include <string>
#include <QVector>
#include <string.h>
#include <stdio.h>

class QExtSignalTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testEmptySignal();
    void testConnectSlots();
    void testReference();
    void testCompareOperator();
    void testCopyOperator();
    void testMakeSlot();
    void testDisconnect();
    void testDisconnectDuringEmit();
    void testAccumulated();
    void testAccumulatedIter();
    void teststdLambda();
};

static QString sg_string;

int foo(int i)
{
    sg_string += "foo(int " + QString::number(i) + ") ";
    return 1;
}

int bar(float i)
{
    sg_string += "bar(float " + QString::number(i) + ") ";
    return 1;
}

struct A : public QObject
{
    int foo(int i)
    {
        sg_string += "A::foo(int " + QString::number(i) + ") ";
        return i;
    }

    int foo1(int i)
    {
        const int result = 20 * i - 14;
        sg_string = "A::foo1(int " + QString::number(result) + ") ";
        return result;
    }

    void bar(QString &str)
    {
        sg_string = "A::bar(string '" + str + "') ";
        str = "bar was here";
    }
};

void goodByeWorld()
{
    sg_string += "Good bye world!";
}

struct B : public QObject
{
    B()
    {
        m_signal.connect(this, &B::destroy);
        m_signal.connect(this, &B::boom);
        m_signal.connect(&goodByeWorld);
    }
    ~B() {}

    // Calling destroy() during signal send seems weird!
    // However, if this works, anything will work!
    void destroy()
    {
        delete this;
    }

    void boom()
    {
        sg_string = "boom!";
    }

    void send()
    {
        m_signal.send();
    }

    QExtSignal<void> m_signal;
};



QExtConnection connection;
class HandlerClass : public QObject
{
public:
    void handler()
    {
        sg_string = "handler called";
        connection.disconnect();
    }
};


struct arithmetic_mean_accumulator
{
    typedef double Return;
    template<typename T_iterator>
    double operator()(T_iterator first, T_iterator last) const
    {
        double value_ = 0;
        int n_ = 0;
        for (; first != last; ++first, ++n_)
        {
            value_ += *first;
        }
        return (n_ ? value_ / n_ : -1); // empty slot list <=> n_==0
    }
};

template<typename  Ret>
struct vector_accumulator
{
    typedef QVector<Ret> Return;

    template<typename T_iterator>
    Return operator()(T_iterator first, T_iterator last) const
    {
        Return vec;
        for (; first != last; ++first)
        {
            vec.push_back(*first);
        }
        return vec;
    }
};



int ident(int i)
{
    return i;
}

template<typename T>
struct min_accum
{
    typedef T Return;

    template<typename T_iterator>
    Return operator()(T_iterator i1, T_iterator i2)
    {
        if (i1 == i2)
        {
            return *i2;
        }
        T_iterator smallest = i1;

        while (++i1 != i2)
            if (*i1 < *smallest)    // or: if (comp(*first,*smallest)) for version (2)
            {
                smallest = i1;
            }
        return *smallest;
    }
};

int foo1(int i)
{
    const int result = 3 * i + 1;
    sg_string = "foo1: " + QString::number(result) + ", ";
    return result;
}

int bar1(double i)
{
    const int result = 5 * int(i) - 3;
    sg_string = "bar1: " + QString::number(i) + ", ";
    return result;
}


void QExtSignalTest::testEmptySignal()
{
    QExtSignal<int, int> sig;
    QVERIFY(0 == sig.size());
    sg_string = "";
    sig(0);
    QVERIFY("" == sg_string);
}

void QExtSignalTest::testConnectSlots()
{
    QExtSignal<int, int> sig;
    // connect some slots before emitting & test auto-disconnection
    {
        sg_string = "";
        A a;
        sig.connect(&foo);
        sig.connect(&a, &A::foo);
        sig.connect(&bar);
        QVERIFY(3 == sig.size());
        sig(1);
        QVERIFY("foo(int 1) A::foo(int 1) bar(float 1) " == sg_string);
    }
    sg_string = "";
    sig(2);
    QVERIFY(2 == sig.size());
    QVERIFY("foo(int 2) bar(float 2) " == sg_string);
}

void QExtSignalTest::testReference()
{
    sg_string = "";
    A a;
    QString str("guest book");
    QExtSignal<void, QString &> sigstr;
    sigstr.connect(&a, &A::bar);
    sigstr(str);
    sg_string += str;
    QVERIFY("A::bar(string 'guest book') bar was here" == sg_string);
}

void QExtSignalTest::testCompareOperator()
{
    A a;
    QExtSignal<void, QString &> sigstr1;
    sigstr1.connect(&a, &A::bar);
    QExtSignal<void, QString &> sigstr2;
    QVERIFY(sigstr1 != sigstr2);
    sigstr2 = sigstr1;
    QVERIFY(sigstr1 == sigstr2);

    sigstr2.connect(&a, &A::bar);
    QVERIFY(sigstr1 != sigstr2);
}

void QExtSignalTest::testCopyOperator()
{
    QExtSignal<int, int> sigstr1;
    sigstr1.connect(&foo);
    QExtSignal<int, int> sigstr2;
    sigstr2 = sigstr1;

    sg_string = "";
    sigstr1(3);
    QVERIFY("foo(int 3) " == sg_string);

    sg_string = "";
    sigstr2(2);
    QVERIFY("foo(int 2) " == sg_string);

//    sigstr2.connect(&foo);
//    QVERIFY(sigstr1 != sigstr2);
//    sg_string = "";
//    sigstr2(2);
//    QVERIFY("foo(int 2) foo(int 2) " == sg_string);
}

void QExtSignalTest::testMakeSlot()
{
    QExtSignal<int, int> sig;
    sg_string = "";
    sig.connect(&foo);
    QExtSignal<int, int> sig2;
    sig2.connect(sig.makeSlot());
    sig2(3);
    QVERIFY("foo(int 3) " == sg_string);
}

void QExtSignalTest::testDisconnect()
{
    QExtSignal<int, int> sig;
    QExtSignal<int, int>::Iterator confoo;
    QExtSignal<int, int>::Iterator conbar;

    {
        sg_string = "";
        A a;
        sig.connect(&a, &A::foo);
        confoo = sig.connect(qextPointerFunctor(&foo));
        conbar = sig.connect(qextPointerFunctor(&bar));
        QVERIFY(3 == sig.size());
        sig(1);
        QVERIFY("A::foo(int 1) foo(int 1) bar(float 1) " == sg_string);
    }                     // auto disconnection! iterators stay valid after disconnections.

    sg_string = "";
    sig(2);
    QVERIFY(2 == sig.size());
    QVERIFY("foo(int 2) bar(float 2) " == sg_string);

    QExtConnection cona;  // connection objects are safe to use beyond the life time of a signal.
    sg_string = "";
    A a;                  // iterators stay valid after further connections.
    cona = sig.slotList().insert(conbar, qextMemberFunctor(&a, &A::foo));
    QVERIFY(3 == sig.size());
    sig(3);
    QVERIFY("foo(int 3) A::foo(int 3) bar(float 3) " == sg_string);

    sg_string = "";
    conbar->disconnect(); // manual disconnection
    QVERIFY(2 == sig.size());
    sig(4);
    QVERIFY("foo(int 4) A::foo(int 4) " == sg_string);

    sg_string = "";
    confoo->disconnect(); // manual disconnection
    QVERIFY(1 == sig.size());
    sig(5);
    QVERIFY("A::foo(int 5) " == sg_string);

    sg_string = "";
    cona.disconnect();    // manual disconnection
    QVERIFY(0 == sig.size());
    sig(6);
    QVERIFY("" == sg_string);

    cona.disconnect();    // already disconnected -> legal with connection objects, however, nothing happens ...

    sg_string = "";
    B *b = new B;
    b->send();
    QVERIFY("Good bye world!" == sg_string);
}

void QExtSignalTest::testDisconnectDuringEmit()
{
    HandlerClass instance;

    sg_string = "";
    QExtSignal<void> signal_test;
    connection = signal_test.connect(instance, &HandlerClass::handler);
    signal_test.send();
    QVERIFY("handler called" == sg_string);
}

void QExtSignalTest::testAccumulated()
{
    QExtSignal<int, int>::Accumulated<arithmetic_mean_accumulator> sig;
    QExtSignal<int, int>::Accumulated<vector_accumulator<int> > sig_vec;

    QVERIFY(-1 == sig(0));
    QVERIFY(sig_vec(0).empty());

    A a;
    sig.connect(&foo1);
    sig.connect(&a, &A::foo1);
    sig.connect(&bar1);

    sig_vec.connect(&foo1);
    sig_vec.connect(&a, &A::foo1);
    sig_vec.connect(&bar1);

    char buf[1024] = "";

    double dres = sig(1);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%.3f", dres);
    QVERIFY("4.000" == QString(buf));

    dres = sig(11);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%.3f", dres);
    QVERIFY("97.333" == QString(buf));

    QVector<int> res1 = sig_vec(1);
    sg_string = "";
    for (QVector<int>::iterator i = res1.begin(); i != res1.end(); ++i)
    {
        sg_string += *i + " ";
    }
    QVERIFY("4 6 2 " == sg_string);

    QVector<int> res3 = sig_vec(3);
    sg_string = "";
    for (QVector<int>::iterator i = res3.begin(); i != res3.end(); ++i)
    {
        sg_string += + *i + " ";
    }
    QVERIFY("10 46 12 " == sg_string);
}

void QExtSignalTest::testAccumulatedIter()
{
    QExtSignal<int>::Accumulated<min_accum<int> > signal;

    signal.connect(qextBindFunctor(&ident, 3));
    signal.connect(qextBindFunctor(&ident, 1));
    signal.connect(qextBindFunctor(&ident, 42));

    QVERIFY(1 == signal.send());
}

void QExtSignalTest::teststdLambda()
{
#if QEXT_CC_STD_11
    QExtSignal<int> readValue;
    int data = 1000;
    readValue.connect([&data] () -> int { return data; });
    QVERIFY(1000 == readValue());
#endif
}

QTEST_APPLESS_MAIN(QExtSignalTest)

#include <tst_qextSignal.moc>
