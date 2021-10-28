#include <qextLambda.h>
#include <qextLambdaOperator.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>

#include <QtTest>
#include <iostream>
#include <string>
#include <sstream>

class QEXTLambdaTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testLambdaOperators();
    void testCommaOperators();
    void testAutoDisconnect();
    void testGroupAdaptor();
};


template <typename T_arg>
struct QEXTLambdaActionReturnTypeDeduce<QEXTLBOPRBitwise<QEXTLBOPRLeftshift>, std::string &, T_arg>
{
    typedef std::string &Type;
};

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

struct Book : public QObject
{
    explicit Book(const std::string &name) : m_name(name) {}
    operator std::string &()
    {
        return m_name;
    }
    std::string m_name;
};


void QEXTLambdaTest::testLambdaOperators()
{
    std::string string;
    sg_string = &string;

    QVERIFY(7 == (g_qextLambdaSelector1 + g_qextLambdaSelector2)(3, 4));
    QVERIFY(4 == (g_qextLambdaSelector1 + 1)(3, 4));
    QVERIFY(4 == (qextLambdaSelectors::_1 + 1)(3, 4));
    QVERIFY(5 == (g_qextLambdaSelector2 + 1)(3, 4));
    QVERIFY(5 == (2 + g_qextLambdaSelector1)(3, 4));
    QVERIFY(6 == (2 + g_qextLambdaSelector2)(3, 4));
    QVERIFY(7 == (qextLambdaSelectors::_1 + g_qextLambdaSelector2 * g_qextLambdaSelector3)(1, 2, 3));
    QVERIFY(4 == ((++qextLambdaSelectors::_1) * 2)(1));

    int a = 1;
    QVERIFY(4 == ((++qextLambdaSelectors::_1) * 2)(a));
    //        QVERIFY(4 == ((++qextLambdaSelectors::_1) * 2)(qextReferenceWrapper(a)));
    QVERIFY(4 == ((++(*qextLambdaSelectors::_1)) * 2)(&a));
    //    QVERIFY(4 == ((--(*(&qextLambdaSelectors::_1))) * 2)(qextReferenceWrapper(a)));

    QVERIFY(5 == (-qextLambdaSelectors::_1)(-5));
    //        QVERIFY(2 == ((qextLambda(&a)[0])()));

    //    QVERIFY(2 == (qextLambdaSelectors::_1[qextLambdaSelectors::_2])(&a, 0));
    //        QVERIFY(1 == (*qextLambdaSelectors::_1 = qextLambdaSelectors::_2)(&a, 1));
    //    QVERIFY(4 == ((--(*(&qextLambdaSelectors::_1))) * 2)(qextReferenceWrapper(a)));
}

void QEXTLambdaTest::testCommaOperators()
{
    std::string string;
    sg_string = &string;

    //        int a = -1;
    //        int b = -1;
    //        int c = -1;
    //    QVERIFY(3 == (qextLambda(c) = (qextLambda(a) = qextLambdaSelectors::_1, qextLambda(b) = qextLambdaSelectors::_2))(2, 3));

    // c++ restrictions:
    // - ref() must be used to indicate that the value shall not be copied
    // - constant() is used to create a lambda and delay execution of "result_stream << 1"
    // - var() is used to create a lambda that holds a reference and is interchangable
    //   with ref() in lambda operator expressions
    // - cannot use std::endl without much hackery because it is defined as a template function
    // - cannot use "\n" without var() because arrays cannot be copied
    *sg_string = "";
    //    (qextReferenceWrapper(*sg_string) << qextLambdaSelectors::_1 << std::string("\n"))("hello world");
    //    QVERIFY("hello world\n" == *sg_string);

    *sg_string = "";
    //    (qextReferenceWrapper(result_stream) << qextLambdaStaticCast<int>(_1) << std::string("\n"))(1.234);
    //    util->check_result(result_stream, "1\n");

    //    (qextLambda(result_stream) << 1 << qextLambda("\n"))();
    //    util->check_result(result_stream, "1\n");

    //    (qextLambda(result_stream) << _1 << std::string("\n"))("hello world");
    //    util->check_result(result_stream, "hello world\n");
}

void QEXTLambdaTest::testAutoDisconnect()
{
    std::string string;
    sg_string = &string;

    //    QEXTSlot<bool> sl1;
    //    {
    //        *sg_string = "";
    //        Book guest_book("karl");
    //        sl1 = (qextLambda(*sg_string) << qextReferenceWrapper(guest_book) << qextLambda("\n"));
    //        sl1();
    //        QVERIFY("karl\n" == *sg_string);
    //    } // auto-disconnect

    //    *sg_string = "";
    //    sl1(); // :-)
    //    QVERIFY("" == *sg_string);
}

void QEXTLambdaTest::testGroupAdaptor()
{
    std::string string;
    sg_string = &string;

    Bar theBar;
    *sg_string = "";
    QVERIFY(6 == (qextLambdaGroup(&foo, qextLambdaSelectors::_1, qextLambdaSelectors::_2))(1, 2));
    QVERIFY("foo(int 1, int 2) " == *sg_string);

    *sg_string = "";
    QVERIFY(9 == (qextLambdaGroup(&foo, qextLambdaSelectors::_2, qextLambdaSelectors::_1))(1, 2));
    QVERIFY("foo(int 2, int 1) " == *sg_string);

    *sg_string = "";
    QVERIFY(6 == (qextLambdaGroup(qextMemberFunctor(&Bar::test), qextLambdaSelectors::_1, qextLambdaSelectors::_2, qextLambdaSelectors::_3))(qextReferenceWrapper(theBar), 1, 2));
    QVERIFY("Bar::test(int 1, int 2) " == *sg_string);
}


QTEST_APPLESS_MAIN(QEXTLambdaTest)

#include <tst_qextLambda.moc>
