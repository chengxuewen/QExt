#include <qextsignal.h>
#include <qextconnection.h>
#include <qextpointerfunctor.h>
#include <qexttrackable.h>
#include <qextbindfunctor.h>

#include <QtTest>
#include <QDebug>

#include <string>
#include <cstdlib>
#include <algorithm>


class QEXTSignalTest : public QObject
{
    Q_OBJECT
private slots:
    void testEmptySignal();
    void testConnectSlots();
    void testReference();
    void testMakeSlot();
    void testDisconnect();
    void testDisconnectDuringEmit();
    void testAccumulated();
    void testAccumulatedIter();

public:
    static int sm_result;
    static QString sm_string;
    QEXTSignal<int,int> sig;
};

int QEXTSignalTest::sm_result = 0;
QString QEXTSignalTest::sm_string = "";


int foo(int i)
{
    QEXTSignalTest::sm_string +=  QString("foo(int %1) ").arg(i);
    return 1;
}

int bar(float i)
{
    QEXTSignalTest::sm_string +=  QString("bar(float %1) ").arg(i);
    return 1;
}

struct A : public QEXTTrackable
{
    int foo(int i) {
        QEXTSignalTest::sm_string +=  QString("A::foo(int %1) ").arg(i);
        return 1;
    }

    int foo1(int i) {
        const int result = 20 * i - 14;
        QEXTSignalTest::sm_string +=  QString("A::foo1(int %1) ").arg(result);
        return result;
    }

    void bar(QString &str) {
        QEXTSignalTest::sm_string +=  QString("A::bar(string '%1') ").arg(str);
        str = "bar was here";
    }
};



void goodByeWorld()
{
    QEXTSignalTest::sm_string += "Good bye world!";
}

struct B : public QEXTTrackable
{
    B() {
        m_signal.connect(qextMemberFunctor(this, &B::destroy));
        m_signal.connect(qextMemberFunctor(this, &B::boom));
        m_signal.connect(qextPointerFunctor(&goodByeWorld));
    }

    // Calling destroy() during signal emission seems weird!
    // However, if this works, anything will work!
    void destroy() {
        delete this;
    }

    void boom() {
        QEXTSignalTest::sm_string = "boom!";
    }

    void send() {
        m_signal.send();
    }

    QEXTSignal<void> m_signal;
};



QEXTConnection connection;
class HandlerClass : public QEXTTrackable
{
public:
    void handler() {
        QEXTSignalTest::sm_string = "handler called";
        connection.disconnect();
    }
};



struct arithmetic_mean_accumulator
{
    typedef double ResultType;
    template<typename T_iterator>
    double operator()(T_iterator first, T_iterator last) const
    {
        double value_ = 0;
        int n_ = 0;
        for (; first != last; ++first, ++n_) {
            value_ += *first;
        }
        return (n_ ? value_ / n_ : -1); // empty slot list <=> n_==0
    }
};

template<class Ret>
struct vector_accumulator
{
    typedef QVector<Ret> ResultType;
    template<typename T_iterator>
    ResultType operator()(T_iterator first, T_iterator last) const
    {
        ResultType vec;
        for (; first != last; ++first) {
            vec.push_back(*first);
        }
        return vec;
    }
};

int foo1(int i)
{
    const int result = 3 * i + 1;
    QEXTSignalTest::sm_string += QString("foo1: %1, ").arg(result);
    return result;
}

int bar1(double i)
{
    const int result = 5 * int(i) - 3;
    QEXTSignalTest::sm_string += QString("bar1: %1, ").arg(i);
    return result;
}



void QEXTSignalTest::testEmptySignal()
{
    sm_string = "";
    sig(0);
    QVERIFY("" == sm_string);
}

void QEXTSignalTest::testConnectSlots()
{
    // connect some slots before emitting & test auto-disconnection
    {
        sm_string = "";
        A a;
        sig.connect(qextPointerFunctor(&foo));
        sig.connect(qextMemberFunctor1(&a, &A::foo));
        sig.connect(qextPointerFunctor1(&bar));
        QVERIFY(3 == sig.size());
        sig(1);
        QVERIFY2("foo(int 1) A::foo(int 1) bar(float 1) " == sm_string, sm_string.toLatin1().data());
    }
    sm_string = "";
    sig(2);
    QVERIFY(2 == sig.size());
    QVERIFY("foo(int 2) bar(float 2) " == sm_string);
}

void QEXTSignalTest::testReference()
{
    sm_string = "";
    A a;
    QString str("guest book");
    QEXTSignal<void, QString &> sigstr;
    sigstr.connect(qextMemberFunctor(&a, &A::bar));
    sigstr(str);
    qDebug() << str;
    sm_string += str;
    QVERIFY2("A::bar(string 'guest book') bar was here" == sm_string, str.toLatin1().data());
}

void QEXTSignalTest::testMakeSlot()
{
    sm_string = "";
    sig.connect(qextPointerFunctor(&foo));
    QEXTSignal<int,int> sig2;
    sig2.connect(sig.makeSlot());
    sig2(3);
    QVERIFY2("foo(int 3) bar(float 3) foo(int 3) " == sm_string, sm_string.toLatin1().data());
}

void QEXTSignalTest::testDisconnect()
{
    QEXTSignal<int, int> sig;
    QEXTSignal<int, int>::Iterator confoo;
    QEXTSignal<int, int>::Iterator conbar;
    QEXTConnection cona;  // connection objects are safe to use beyond the life time of a signal.

    {
        sm_string = "";
        A a;
        sig.connect(qextMemberFunctor1(&a, &A::foo));
        confoo = sig.connect(qextPointerFunctor1(&foo));
        conbar = sig.connect(qextPointerFunctor1(&bar));
        QVERIFY(3 == sig.size());
        sig(1);
        QVERIFY("A::foo(int 1) foo(int 1) bar(float 1) " == sm_string);
    }                     // auto disconnection! iterators stay valid after disconnections.

    sm_string = "";
    QVERIFY(2 == sig.size());
    sig(2);
    QVERIFY("foo(int 2) bar(float 2) " == sm_string);

    sm_string = "";
    A a;                  // iterators stay valid after further connections.
    cona = sig.slotList().insert(conbar, qextMemberFunctor1(&a, &A::foo));
    QVERIFY(3 == sig.size());
    sig(3);
    QVERIFY("foo(int 3) A::foo(int 3) bar(float 3) " == sm_string);

    sm_string = "";
    conbar->disconnect(); // manual disconnection
    QVERIFY(2 == sig.size());
    sig(4);
    QVERIFY("foo(int 4) A::foo(int 4) " == sm_string);

    sm_string = "";
    confoo->disconnect(); // manual disconnection
    QVERIFY(1 == sig.size());
    sig(5);
    QVERIFY("A::foo(int 5) " == sm_string);

    sm_string = "";
    cona.disconnect();    // manual disconnection
    QVERIFY(0 == sig.size());
    sig(6);
    QVERIFY("" == sm_string);

    cona.disconnect();    // already disconnected -> legal with connection objects, however, nothing happens ...

    sm_string = "";
    B* b = new B;
    b->send();
    QVERIFY("Good bye world!" == sm_string);
}

void QEXTSignalTest::testDisconnectDuringEmit()
{
    HandlerClass instance;

    sm_string = "";
    QEXTSignal<void> signal_test;
    connection = signal_test.connect(qextMemberFunctor(instance, &HandlerClass::handler));
    signal_test.send();
    QVERIFY("handler called" == sm_string);
}

void QEXTSignalTest::testAccumulated()
{
    QEXTSignal<int, int>::Accumulated<arithmetic_mean_accumulator> sig;
    QEXTSignal<int, int>::Accumulated<vector_accumulator<int> > sig_vec;

    QVERIFY(-1 == sig(0));
    QVERIFY("handler called" == sm_string);
    QVERIFY(sig_vec(0).empty());

    A a;
    sig.connect(qextPointerFunctor(&foo1));
    sig.connect(qextMemberFunctor(&a, &A::foo1));
    sig.connect(qextPointerFunctor(&bar1));

    sig_vec.connect(qextPointerFunctor(&foo1));
    sig_vec.connect(qextMemberFunctor(&a, &A::foo1));
    sig_vec.connect(qextPointerFunctor(&bar1));

    double dres = sig(1);
    QVERIFY("4.000" == QString::number(dres, 'f', 3));

    dres = sig(11);
    QVERIFY("97.333" == QString::number(dres, 'f', 3));

    QVector<int> res1 = sig_vec(1);
    QVERIFY("97.333" == QString::number(dres, 'f', 3));
    sm_string = "";
    for (QVector<int>::iterator i = res1.begin(); i != res1.end(); ++i) {
        sm_string += QString("%1 ").arg(*i);
    }
    QVERIFY("4 6 2 " == sm_string);

    QVector<int> res3 = sig_vec(3);
    sm_string = "";
    for (QVector<int>::iterator i = res3.begin(); i != res3.end(); ++i) {
        sm_string += QString("%1 ").arg(*i);
    }
    QVERIFY("10 46 12 " == sm_string);
}


int ident(int i)
{
    return i;
}

template<typename T>
struct min_accum
{
    typedef T ResultType;

    template<typename I>
    typename std::iterator_traits<I>::value_type operator()(I i1, I i2)
    {
        return *std::min_element(i1, i2);
    }
};

void QEXTSignalTest::testAccumulatedIter()
{
    //    QEXTSignal0<int, min_accum<int> > signal;

    //    signal.connect(qextBindFunctor(qextPointerFunctor(ident), 3));
    //    signal.connect(qextBindFunctor(qextPointerFunctor(ident), 1));
    //    signal.connect(qextBindFunctor(qextPointerFunctor(ident), 42));

    //    QVERIFY(1 == signal());
}

QTEST_APPLESS_MAIN(QEXTSignalTest)

#include <tst_qextsignal.moc>
