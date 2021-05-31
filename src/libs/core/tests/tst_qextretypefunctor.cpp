#include <qexttrackable.h>
#include <qextretypefunctor.h>

#include <QtTest>
#include <QDebug>


class QEXTRetypeFunctorTest : public QObject
{
    Q_OBJECT
private slots:
    void testSimple();

public:
    static int sm_result;
    static QString sm_string;
};

int QEXTRetypeFunctorTest::sm_result = 0;
QString QEXTRetypeFunctorTest::sm_string = "";



struct Foo : public QEXTTrackable
{
    float testInt(int i) {
        QEXTRetypeFunctorTest::sm_string = QString("Foo::testInt(int %1) ").arg(i);
        return i * 1.5f;
    }

    float testFloat(float f) {
        QEXTRetypeFunctorTest::sm_string = QString("Foo::testFloat(float %1) ").arg(f);
        return f * 5;
    }

    void testVoid(int i) {
        QEXTRetypeFunctorTest::sm_string = QString("Foo::testVoid(int %1) ").arg(i);
    }
};

void Bar(short s)
{
    QEXTRetypeFunctorTest::sm_string = QString("bar(short %1)").arg(s);
}




void QEXTRetypeFunctorTest::testSimple()
{
    Foo foo;
    QEXTRetypeFunctorTest::sm_string = "";
    QVERIFY(1.5 == qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testInt))(1.234f));
    QVERIFY("Foo::testInt(int 1) " == QEXTRetypeFunctorTest::sm_string);

    QEXTRetypeFunctorTest::sm_string = "";
    QVERIFY(25 == qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testFloat))(5));
    QVERIFY("Foo::testFloat(float 5) " == QEXTRetypeFunctorTest::sm_string);

    QEXTRetypeFunctorTest::sm_string = "";
    qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testVoid))(1.234f);
    QVERIFY("Foo::testVoid(int 1) " == QEXTRetypeFunctorTest::sm_string);

    QEXTRetypeFunctorTest::sm_string = "";
    qextRetypeFunctor(qextPointerFunctor(&Bar))(6.789f);
    QVERIFY("bar(short 6)" == QEXTRetypeFunctorTest::sm_string);
    return;

    QEXTRetypeFunctorTest::sm_string = "";
    QEXTSlot<float,float> s1 = qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testInt));
    QEXTSlot<float,int>   s2 = qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testFloat));
    QEXTSlot<void,double> s3 = qextRetypeFunctor(qextPointerFunctor(&Bar));
    QVERIFY(1.5 == s1(1.234f));
    QVERIFY("Foo::testInt(int 1) " == QEXTRetypeFunctorTest::sm_string);

    QEXTRetypeFunctorTest::sm_string = "";
    QVERIFY(25 == s2(5));
    QVERIFY("Foo::testFloat(float 5) " == QEXTRetypeFunctorTest::sm_string);

    QEXTRetypeFunctorTest::sm_string = "";
    s3(6.789);
    QVERIFY("bar(short 6)" == QEXTRetypeFunctorTest::sm_string);

    QEXTRetypeFunctorTest::sm_string = "";
    s2 = qextRetypeFunctor(s1);
    QVERIFY(7.5 == s2(5));
    QVERIFY("Foo::testInt(int 5) " == QEXTRetypeFunctorTest::sm_string);
}

QTEST_APPLESS_MAIN(QEXTRetypeFunctorTest)

#include <tst_qextretypefunctor.moc>
