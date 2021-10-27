#ifndef QEXTLIMITREFERENCETEST_H
#define QEXTLIMITREFERENCETEST_H

#include <qextLimitReference.h>
#include <qextMemberFunctor.h>
#include <qextBindReturnFunctor.h>
#include <qextBindFunctor.h>
#include <qextSlot.h>
#include <qextObject.h>

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextLimitReferenceTest
{

    static std::string sg_string = "";

    class Base : virtual public QEXTObject
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


    TEST_GROUP(qextLimitReferenceTest)
    {
    };

    TEST(qextLimitReferenceTest, testSimple)
    {
        sg_string = "";
        Derived *instance = new Derived;
        QEXTSlot<void> handler = qextMemberFunctor(instance, &Derived::method);
        handler();
        CHECK("method()" == sg_string);

        sg_string = "";
        QEXTSlot<void> param = qextBindFunctor(QEXTSlot<void, Derived &>(), qextReferenceWrapper(*instance));
        param();
        CHECK("" == sg_string);

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

} // namespace qextLimitReferenceTest

#endif // QEXTLIMITREFERENCETEST_H
