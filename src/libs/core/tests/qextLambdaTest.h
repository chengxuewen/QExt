#ifndef QEXTLAMBDATEST_H
#define QEXTLAMBDATEST_H

#include <qextLambda.h>
#include <qextLambdaOperator.h>
#include <qextObject.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE


template <typename T_arg>
struct QEXTLambdaActionReturnTypeDeduce<QEXTLBOPRBitwise<QEXTLBOPRLeftshift>, std::string &, T_arg>
{
    typedef std::string &Type;
};


namespace qextLambdaTest
{

    static std::string *sg_string = QEXT_DECL_NULLPTR;

    int foo(int i, int j)
    {
        std::stringstream sstream;
        sstream << "foo(int " << i << ", int " << j << ") ";
        *sg_string = sstream.str();
        return 4 * i + j;
    }

    void fooVoid(int i)
    {
        std::stringstream sstream;
        sstream << "fooVoid(int " << i << ")";
        *sg_string = sstream.str();
    }

    struct Bar
    {
        int test(int i, int j)
        {
            std::stringstream sstream;
            sstream << "Bar::test(int " << i << ", int " << j << ") ";
            *sg_string = sstream.str();
            return 4 * i + j;
        }

        void testVoid(int i)
        {
            std::stringstream sstream;
            sstream << "Bar::testVoid(int " << i << ")";
            *sg_string = sstream.str();
        }
    };

    void egon(std::string &str)
    {
        std::stringstream sstream;
        sstream << "egon(string '" << str << "')";
        *sg_string = sstream.str();
        str = "egon was here";
    }

    struct Book : public QEXTObject
    {
        explicit Book(const std::string &name) : m_name(name) {}
        operator std::string &()
        {
            return m_name;
        }
        std::string m_name;
    };


    TEST_GROUP(qextLambdaTest)
    {
    };

    TEST(qextLambdaTest, testLambdaOperators)
    {
        std::string string;
        sg_string = &string;

        CHECK(7 == (g_qextLambdaSelector1 + g_qextLambdaSelector2)(3, 4));
        CHECK(4 == (g_qextLambdaSelector1 + 1)(3, 4));
        CHECK(4 == (qextLambdaSelectors::_1 + 1)(3, 4));
        CHECK(5 == (g_qextLambdaSelector2 + 1)(3, 4));
        CHECK(5 == (2 + g_qextLambdaSelector1)(3, 4));
        CHECK(6 == (2 + g_qextLambdaSelector2)(3, 4));
        CHECK(7 == (qextLambdaSelectors::_1 + g_qextLambdaSelector2 * g_qextLambdaSelector3)(1, 2, 3));
        CHECK(4 == ((++qextLambdaSelectors::_1) * 2)(1));

        int a = 1;
        CHECK(4 == ((++qextLambdaSelectors::_1) * 2)(a));
//        CHECK(4 == ((++qextLambdaSelectors::_1) * 2)(qextReferenceWrapper(a)));
        CHECK(4 == ((++(*qextLambdaSelectors::_1)) * 2)(&a));
        //    CHECK(4 == ((--(*(&qextLambdaSelectors::_1))) * 2)(qextReferenceWrapper(a)));

        CHECK(5 == (-qextLambdaSelectors::_1)(-5));
//        CHECK(2 == ((qextLambda(&a)[0])()));

        //    CHECK(2 == (qextLambdaSelectors::_1[qextLambdaSelectors::_2])(&a, 0));
        //        CHECK(1 == (*qextLambdaSelectors::_1 = qextLambdaSelectors::_2)(&a, 1));
        //    CHECK(4 == ((--(*(&qextLambdaSelectors::_1))) * 2)(qextReferenceWrapper(a)));
    }

    TEST(qextLambdaTest, testCommaOperators)
    {
        std::string string;
        sg_string = &string;

//        int a = -1;
//        int b = -1;
//        int c = -1;
        //    CHECK(3 == (qextLambda(c) = (qextLambda(a) = qextLambdaSelectors::_1, qextLambda(b) = qextLambdaSelectors::_2))(2, 3));

        // c++ restrictions:
        // - ref() must be used to indicate that the value shall not be copied
        // - constant() is used to create a lambda and delay execution of "result_stream << 1"
        // - var() is used to create a lambda that holds a reference and is interchangable
        //   with ref() in lambda operator expressions
        // - cannot use std::endl without much hackery because it is defined as a template function
        // - cannot use "\n" without var() because arrays cannot be copied
        *sg_string = "";
        //    (qextReferenceWrapper(*sg_string) << qextLambdaSelectors::_1 << std::string("\n"))("hello world");
        //    CHECK("hello world\n" == *sg_string);

        *sg_string = "";
        //    (qextReferenceWrapper(result_stream) << qextLambdaStaticCast<int>(_1) << std::string("\n"))(1.234);
        //    util->check_result(result_stream, "1\n");

        //    (qextLambda(result_stream) << 1 << qextLambda("\n"))();
        //    util->check_result(result_stream, "1\n");

        //    (qextLambda(result_stream) << _1 << std::string("\n"))("hello world");
        //    util->check_result(result_stream, "hello world\n");
    }

    TEST(qextLambdaTest, testAutoDisconnect)
    {
        std::string string;
        sg_string = &string;

        //    QEXTSlot<bool> sl1;
        //    {
        //        *sg_string = "";
        //        Book guest_book("karl");
        //        sl1 = (qextLambda(*sg_string) << qextReferenceWrapper(guest_book) << qextLambda("\n"));
        //        sl1();
        //        CHECK("karl\n" == *sg_string);
        //    } // auto-disconnect

        //    *sg_string = "";
        //    sl1(); // :-)
        //    CHECK("" == *sg_string);
    }

    TEST(qextLambdaTest, testGroupAdaptor)
    {
        std::string string;
        sg_string = &string;

        Bar theBar;
        *sg_string = "";
        CHECK(6 == (qextLambdaGroup(&foo, qextLambdaSelectors::_1, qextLambdaSelectors::_2))(1, 2));
        CHECK("foo(int 1, int 2) " == *sg_string);

        *sg_string = "";
        CHECK(9 == (qextLambdaGroup(&foo, qextLambdaSelectors::_2, qextLambdaSelectors::_1))(1, 2));
        CHECK("foo(int 2, int 1) " == *sg_string);

        *sg_string = "";
        CHECK(6 == (qextLambdaGroup(qextMemberFunctor(&Bar::test), qextLambdaSelectors::_1, qextLambdaSelectors::_2, qextLambdaSelectors::_3))(qextReferenceWrapper(theBar), 1, 2));
        CHECK("Bar::test(int 1, int 2) " == *sg_string);
    }

} // namespace qextLambdaTest

#endif // QEXTLAMBDATEST_H
