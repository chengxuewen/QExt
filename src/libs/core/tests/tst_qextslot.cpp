#include <qextslot.h>
#include <qextfunctor.h>

#include <QtTest>
#include <QDebug>

class QEXTSlotTest : public QObject
{
    Q_OBJECT
private slots:
    void testSimple();
    void testImplicitConversion();
    void testReference();
    void testEqualOperator();
    void testCopyCtor();
    void testDisconnect();

public:
    static int sm_result;
    static QString sm_string;
};

int QEXTSlotTest::sm_result = 0;
QString QEXTSlotTest::sm_string = "";

class Foo
{
public:
    void operator()(int i) {
        QEXTSlotTest::sm_result = i;
        QEXTSlotTest::sm_string = QString("foo(int %1)").arg(i);
    }

    void operator()(QString &str) {
        QEXTSlotTest::sm_string = QString("foo(string '%1') ").arg(str);
        str = "foo was here";
    }

    void operator()(int, int) {
        QEXTSlotTest::sm_string = "foo(int, int)";
    }
};




void QEXTSlotTest::testSimple()
{
    QEXTSlot<void, int> s1 = Foo();
    s1(1);
    QVERIFY(1 == sm_result);

    s1 = Foo();
    s1(2);
    QVERIFY(2 == sm_result);
}

void QEXTSlotTest::testImplicitConversion()
{
    QEXTSlot<void, char> s2 = Foo();
    s2(3);
    QVERIFY(3 == sm_result);
}

void QEXTSlotTest::testReference()
{
    QEXTSlot<void, QString &> sl1 = Foo();
    QString str("guest book");
    sl1(str);
    sm_string += "foo was here";
    QVERIFY("foo(string 'guest book') foo was here" == sm_string);
}

void QEXTSlotTest::testEqualOperator()
{
    QEXTSlot<void, QString &> sl1 = Foo();
    QString str("guest book");
    sl1(str);
    sm_string += "foo was here";
    QVERIFY("foo(string 'guest book') foo was here" == sm_string);

    str = "guest book";
    QEXTSlot<void, QString &> sl2;
    sl2 = sl1;
    sl1 = sl2;
    sl1(str);
    sm_string += "foo was here";
    QVERIFY("foo(string 'guest book') foo was here" == sm_string);
}

void QEXTSlotTest::testCopyCtor()
{
    QEXTSlot<void, int> s1 = Foo();
    s1(1);
    QVERIFY(1 == sm_result);

    s1 = Foo();
    s1(2);
    QVERIFY(2 == sm_result);

    QEXTSlot<void, int> s1_clone(s1);
    s1_clone(4);
    QVERIFY("foo(int 4)" == sm_string);
}

void functionFoo()
{
    QEXTSlotTest::sm_string = "functionFoo";
}

void functionBar()
{
    QEXTSlotTest::sm_string = "functionBar";
}

void QEXTSlotTest::testDisconnect()
{
    QEXTSlot<void> theSlot(qextFunctor(&functionFoo));
    theSlot();
    QVERIFY("functionFoo" == QEXTSlotTest::sm_string);

    QEXTSlotTest::sm_string = "";
    theSlot.disconnect();
    theSlot();
    QVERIFY("" == QEXTSlotTest::sm_string);

    theSlot = qextFunctor(&functionBar);
    theSlot();
    QVERIFY("functionBar" == QEXTSlotTest::sm_string);
}

QTEST_APPLESS_MAIN(QEXTSlotTest)

#include <tst_qextslot.moc>
