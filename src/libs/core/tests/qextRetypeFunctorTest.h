#ifndef QEXTRETYPEFUNCTORTEST_H
#define QEXTRETYPEFUNCTORTEST_H

#include <qextRetypeFunctor.h>

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextRetypeFunctorTest
{

    static std::string *sg_string = QEXT_DECL_NULLPTR;


    struct Foo : public QEXTObject
    {
        float testInt(int i)
        {
            std::stringstream sstream;
            sstream << "Foo::testInt(int " << i << ") ";
            *sg_string = sstream.str();
            return i * 1.5f;
        }

        float testFloat(float f)
        {
            std::stringstream sstream;
            sstream << "Foo::testFloat(float " << f << ") ";
            *sg_string = sstream.str();
            return f * 5;
        }

        void testVoid(int i)
        {
            std::stringstream sstream;
            sstream << "Foo::testVoid(int " << i << ") ";
            *sg_string = sstream.str();
        }
    };

    void Bar(short s)
    {
        std::stringstream sstream;
        sstream << "bar(short " << s << ")";
        *sg_string = sstream.str();
    }




    TEST_GROUP(qextRetypeFunctorTest)
    {
    };

    TEST(qextRetypeFunctorTest, testSimple)
    {
        std::string string;
        sg_string = &string;

        Foo foo;
        *sg_string = "";
        CHECK(1.5 == qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testInt))(1.234f));
        CHECK("Foo::testInt(int 1) " == *sg_string);

        *sg_string = "";
        CHECK(25 == qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testFloat))(5));
        CHECK("Foo::testFloat(float 5) " == *sg_string);

        *sg_string = "";
        qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testVoid))(1.234f);
        CHECK("Foo::testVoid(int 1) " == *sg_string);

        *sg_string = "";
        qextRetypeFunctor(qextPointerFunctor(&Bar))(6.789f);
        CHECK("bar(short 6)" == *sg_string);
        return;

        *sg_string = "";
        QEXTSlot<float, float> s1 = qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testInt));
        QEXTSlot<float, int>   s2 = qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testFloat));
        QEXTSlot<void, double> s3 = qextRetypeFunctor(qextPointerFunctor(&Bar));
        CHECK(1.5 == s1(1.234f));
        CHECK("Foo::testInt(int 1) " == *sg_string);

        *sg_string = "";
        CHECK(25 == s2(5));
        CHECK("Foo::testFloat(float 5) " == *sg_string);

        *sg_string = "";
        s3(6.789);
        CHECK("bar(short 6)" == *sg_string);

        *sg_string = "";
        //TODO
//        s2 = qextRetypeFunctor(s1);
        CHECK(7.5 == s2(5));
        CHECK("Foo::testInt(int 5) " == *sg_string);
    }

} // namespace qextRetypeFunctorTest

#endif // QEXTRETYPEFUNCTORTEST_H
