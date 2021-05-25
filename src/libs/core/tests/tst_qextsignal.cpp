#include <qextsignal.h>
#include <qextfunctor.h>
#include <qexttrackable.h>

#include <QtTest>
#include <QDebug>

#include <string>
#include <cstdlib>


class QEXTSignalTest : public QObject
{
    Q_OBJECT
private slots:
    void testEmptySignal();
    void testConnectSlots();
    void testReference();
    void testMakeSlot();

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

    void bar(QString &str) {
        QEXTSignalTest::sm_string +=  QString("A::bar(string '%1') ").arg(str);
        str = "bar was here";
    }
};




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
        sig.connect(qextFunctor(&foo));
        sig.connect(qextMemberFunctor1(&a, &A::foo));
        sig.connect(qextFunctor1(&bar));
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
    //    QEXTBoundMemberFunctor<void, A, QString &> functor = qextMemberFunctor(&a, &A::bar);
    //    functor(str);
    qDebug() << str;
    sm_string += str;
    QVERIFY2("A::bar(string 'guest book') bar was here" == sm_string, str.toLatin1().data());
}

void QEXTSignalTest::testMakeSlot()
{
    sm_string = "";
    sig.connect(qextFunctor(&foo));
    QEXTSignal<int,int> sig2;
    sig2.connect(sig.makeSlot());
    sig2(3);
    QVERIFY2("foo(int 3) bar(float 3) foo(int 3) " == sm_string, sm_string.toLatin1().data());
}

QTEST_APPLESS_MAIN(QEXTSignalTest)

#include <tst_qextsignal.moc>
