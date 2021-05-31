#include <qextlimitreference.h>
#include <qexttrackable.h>
#include <qextmemberfunctor.h>
#include <qextbindreturnfunctor.h>
#include <qextbindfunctor.h>
#include <qextslot.h>

#include <QtTest>
#include <QDebug>

class QEXTLimitReferenceTest : public QObject
{
    Q_OBJECT
private slots:
    void testSimple();

public:
    static int sm_result;
    static QString sm_string;
};

int QEXTLimitReferenceTest::sm_result = 0;
QString QEXTLimitReferenceTest::sm_string = "";



class Base : virtual public QEXTTrackable
{
};

class Base2
{
public:
    virtual ~Base2() {}
};

class Derived : virtual public Base, public Base2
{
public:
    void method() {
        QEXTLimitReferenceTest::sm_string = "method()";
    }
};





void QEXTLimitReferenceTest::testSimple()
{
    QEXTLimitReferenceTest::sm_string = "";
    Derived *instance = new Derived;
    QEXTSlot<void> handler = qextMemberFunctor(instance, &Derived::method);
    handler();
    QVERIFY("method()" == QEXTLimitReferenceTest::sm_string);

    QEXTLimitReferenceTest::sm_string = "";
    QEXTSlot<void> param = qextBindFunctor(QEXTSlot<void, Derived&>(), qextReferenceWrapper(*instance));
    param();
    QVERIFY("" == QEXTLimitReferenceTest::sm_string);

    QEXTLimitReferenceTest::sm_string = "";
    QEXTSlot<Derived> ret = qextBindReturnFunctor(QEXTSlot<void>(), qextReferenceWrapper(*instance));
    ret();
    QVERIFY("" == QEXTLimitReferenceTest::sm_string);

    delete instance;

    handler();
    param();
    ret();
    QVERIFY("" == QEXTLimitReferenceTest::sm_string);
}

QTEST_APPLESS_MAIN(QEXTLimitReferenceTest)

#include <tst_qextlimitreference.moc>
