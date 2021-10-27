#ifndef QEXTHIDEFUNCTORTEST_H
#define QEXTHIDEFUNCTORTEST_H

#include <qextObject.h>
#include <qextHideFunctor.h>

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextHideFunctorTest
{

    static std::string sg_string = "";

    struct Foo : public QEXTFunctorBase
    {
        // choose a type that can hold all return values
        typedef int Return;

        int operator()()
        {
            sg_string = "Foo() ";
            return true;
        }

        int operator()(int j)
        {
            std::stringstream sstream;
            sstream << "Foo(int " << j << ") ";
            sg_string = sstream.str();
            return 1 + j;
        }
    };

    struct FooVoid : public QEXTFunctorBase
    {
        typedef void Return;

        void operator()()
        {
            sg_string = "FooVoid()";
        }
    };


    TEST_GROUP(qextHideFunctorTest)
    {
    };

    TEST(qextHideFunctorTest, testSimple)
    {
        sg_string = "";
        CHECK(3 == qextHideFunctor<0>(Foo())(1, 2));
        CHECK("Foo(int 2) " == sg_string);

        sg_string = "";
        CHECK(2 == qextHideFunctor<1>(Foo())(1, 2));
        CHECK("Foo(int 1) " == sg_string);

        sg_string = "";
        CHECK(1 == qextHideFunctor < -1 > (Foo())(1));
        CHECK("Foo() " == sg_string);

        sg_string = "";
        CHECK(1 == qextHideFunctor(Foo())(1));
        CHECK("Foo() " == sg_string);

        sg_string = "";
        qextHideFunctor(FooVoid())(1); // void test
        CHECK("FooVoid()" == sg_string);
    }

} // namespace qextHideFunctorTest

#endif // QEXTHIDEFUNCTORTEST_H
