#ifndef QEXTRETYPERETURNFUNCTORTEST_H
#define QEXTRETYPERETURNFUNCTORTEST_H

#include <qextObject.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>
#include <qextReferenceWrapper.h>
#include <qextBindFunctor.h>
#include <qextRetypeReturnFunctor.h>
#include <qextSlot.h>

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextRetypeReturnFunctorTest
{

    static std::string *sg_string = QEXT_DECL_NULLPTR;

    struct Foo : public QEXTFunctorBase
    {
        typedef float Return;

        float operator()(int i)
        {
            std::stringstream sstream;
            sstream << "Foo(int " << i << ") ";
            *sg_string = sstream.str();
            return i;
        }

        float operator()(float i)
        {
            std::stringstream sstream;
            sstream << "Foo(float " << i << ") ";
            *sg_string = sstream.str();
            return i * 5;
        }
    };

    struct Bar : public QEXTFunctorBase
    {
        typedef int Return;

        int operator()(int i)
        {
            std::stringstream sstream;
            sstream << "Bar(int " << i << ")";
            *sg_string = sstream.str();
            return i;
        }
    };



    TEST_GROUP(qextRetypeReturnFunctorTest)
    {
    };

    TEST(qextRetypeReturnFunctorTest, testSimple)
    {
        std::string string;
        sg_string = &string;

        // retype_return<int>
        *sg_string = "";
        CHECK(6 == qextRetypeReturnFunctor<int>(Foo())(1.234f));
        CHECK("Foo(float 1.234) " == *sg_string);

        // retype_return<void> / hide_return
        *sg_string = "";
        QEXTSlot<void, int> sl;
        sl = qextRetypeReturnFunctor<void>(Bar());
        sl(5);
        CHECK("Bar(int 5)" == *sg_string);

        *sg_string = "";
        sl = qextHideReturnFunctor(Bar());
        sl(6);
        CHECK("Bar(int 6)" == *sg_string);
    }

} // namespace qextRetypeReturnFunctorTest

#endif // QEXTRETYPERETURNFUNCTORTEST_H
