#include <qextLimitReference.h>
#include <qextMemberFunctor.h>
#include <qextBindReturnFunctor.h>
#include <qextBindFunctor.h>
#include <qextFunction.h>

#include <QtTest>

#include <iostream>
#include <string>
#include <sstream>

class QExtLimitReferenceTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testSimple();
};

static QString sg_string = "";

class Base : virtual public QObject
{
public:
    Base() {}
};

class Base2
{
public:
    virtual ~Base2() {}
};

class Derived : virtual public Base, public Base2
{
public:
    void method()
    {
        sg_string = "method()";
    }
};


void QExtLimitReferenceTest::testSimple()
{
    sg_string = "";
    Derived *instance = new Derived;
    QExtFunction<void> handler = qextMemberFunctor(instance, &Derived::method);
    handler();
    QVERIFY("method()" == sg_string);

    sg_string = "";
    QExtFunction<void> param = qextBindFunctor(QExtFunction<void, Derived &>(), qextReferenceWrapper(*instance));
    param();
    QVERIFY("" == sg_string);

    sg_string = "";
    //TODO
    //        QExtFunction<Derived *> ret = qextBindReturnFunctor(QExtFunction<void>(), qextReferenceWrapper(*instance));
    //        ret();
    //        CHECK("" == sg_string);

    //        delete instance;

    //        handler();
    //        param();
    //        ret();
    //        CHECK("" == sg_string);
}



QTEST_APPLESS_MAIN(QExtLimitReferenceTest)

#include <tst_qextLimitReference.moc>
