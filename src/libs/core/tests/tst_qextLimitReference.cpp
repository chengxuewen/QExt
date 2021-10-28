#include <qextLimitReference.h>
#include <qextMemberFunctor.h>
#include <qextBindReturnFunctor.h>
#include <qextBindFunctor.h>
#include <qextSlot.h>

#include <QtTest>

#include <iostream>
#include <string>
#include <sstream>

class QEXTLimitReferenceTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testSimple();
};

static std::string sg_string = "";

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


void QEXTLimitReferenceTest::testSimple()
{
    sg_string = "";
    Derived *instance = new Derived;
    QEXTSlot<void> handler = qextMemberFunctor(instance, &Derived::method);
    handler();
    QVERIFY("method()" == sg_string);

    sg_string = "";
    QEXTSlot<void> param = qextBindFunctor(QEXTSlot<void, Derived &>(), qextReferenceWrapper(*instance));
    param();
    QVERIFY("" == sg_string);

    sg_string = "";
    //TODO
    //        QEXTSlot<Derived *> ret = qextBindReturnFunctor(QEXTSlot<void>(), qextReferenceWrapper(*instance));
    //        ret();
    //        CHECK("" == sg_string);

    //        delete instance;

    //        handler();
    //        param();
    //        ret();
    //        CHECK("" == sg_string);
}



QTEST_APPLESS_MAIN(QEXTLimitReferenceTest)

#include <tst_qextLimitReference.moc>
