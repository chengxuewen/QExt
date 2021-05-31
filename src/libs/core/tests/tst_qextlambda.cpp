#include <qextlambda.h>
#include <qexttrackable.h>
#include <qextpointerfunctor.h>
#include <qextmemberfunctor.h>
#include <qextslot.h>

#include <QtTest>
#include <QDebug>
#include <QString>


class QEXTLambdaTest : public QObject
{
    Q_OBJECT
private slots:
    void testLambdaOperators();
    void testCommaOperators();
    void testAutoDisconnect();
    void testGroupAdaptor();


public:
    static int sm_result;
    static QString sm_string;
};


int QEXTLambdaTest::sm_result = 0;
QString QEXTLambdaTest::sm_string = "";



template <class T_arg>
struct QEXTLambdaActionResultTypeDeduce<bitwise<leftshift>, QString&, T_arg>
{
    typedef QString& Type;
};


int Foo(int i, int j)
{
    QEXTLambdaTest::sm_string = QString("foo(int %1, int %2) ").arg(i).arg(j);
    return 4 * i + j;
}

void fooVoid(int i)
{
    QEXTLambdaTest::sm_string = QString("fooVoid(int %1)").arg(i);
}

struct Bar
{
    int test(int i, int j) {
        QEXTLambdaTest::sm_string = QString("Bar::test(int %1, int %2) ").arg(i).arg(j);
        return 4 * i + j;
    }

    void testVoid(int i) {
        QEXTLambdaTest::sm_string = QString("Bar::testVoid(int %1)").arg(i);
    }
};

void egon(QString &str)
{
    QEXTLambdaTest::sm_string = QString("egon(string '%1')").arg(str);
    str = "egon was here";
}

struct Book : public QEXTTrackable
{
    explicit Book(const QString &name) : m_name(name) {}
    operator QString& () { return m_name; }
    QString m_name;
};



void QEXTLambdaTest::testLambdaOperators()
{
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
    //    QVERIFY(4 == ((++qextLambdaSelectors::_1) * 2)(qextReferenceWrapper(a)));
    QVERIFY(4 == ((++(*qextLambdaSelectors::_1)) * 2)(&a));
    //    QVERIFY(4 == ((--(*(&qextLambdaSelectors::_1))) * 2)(qextReferenceWrapper(a)));

    QVERIFY(5 == (-qextLambdaSelectors::_1)(-5));
    //    QVERIFY(2 == ((qextLambsda(&a)[0])()));

    //    QVERIFY(2 == (qextLambdaSelectors::_1[qextLambdaSelectors::_2])(&a, 0));
    //        QVERIFY(1 == (*qextLambdaSelectors::_1 = qextLambdaSelectors::_2)(&a, 1));
    //    QVERIFY(4 == ((--(*(&qextLambdaSelectors::_1))) * 2)(qextReferenceWrapper(a)));
}

void QEXTLambdaTest::testCommaOperators()
{
    int a = -1;
    int b = -1;
    int c = -1;
    //    QVERIFY(3 == (qextLambda(c) = (qextLambda(a) = qextLambdaSelectors::_1, qextLambda(b) = qextLambdaSelectors::_2))(2, 3));

    // c++ restrictions:
    // - ref() must be used to indicate that the value shall not be copied
    // - constant() is used to create a lambda and delay execution of "result_stream << 1"
    // - var() is used to create a lambda that holds a reference and is interchangable
    //   with ref() in lambda operator expressions
    // - cannot use std::endl without much hackery because it is defined as a template function
    // - cannot use "\n" without var() because arrays cannot be copied
    QEXTLambdaTest::sm_string = "";
    //    (qextReferenceWrapper(QEXTLambdaTest::sm_string) << qextLambdaSelectors::_1 << QString("\n"))("hello world");
    //    QVERIFY("hello world\n" == QEXTLambdaTest::sm_string);

    QEXTLambdaTest::sm_string = "";
    //    (sigc::ref(result_stream) << sigc::static_cast_<int>(_1) << std::string("\n"))(1.234);
    //    util->check_result(result_stream, "1\n");

    //    (sigc::var(result_stream) << 1 << sigc::var("\n"))();
    //    util->check_result(result_stream, "1\n");

    //    (sigc::var(result_stream) << _1 << std::string("\n"))("hello world");
    //    util->check_result(result_stream, "hello world\n");
}

void QEXTLambdaTest::testAutoDisconnect()
{
    //    QEXTSlot<bool> sl1;
    //    {
    //        QEXTLambdaTest::sm_string = "";
    //        Book guest_book("karl");
    //        sl1 = (qextLambda(QEXTLambdaTest::sm_string) << qextReferenceWrapper(guest_book) << qextLambda("\n"));
    //        sl1();
    //        QVERIFY("karl\n" == QEXTLambdaTest::sm_string);
    //    } // auto-disconnect

    //    QEXTLambdaTest::sm_string = "";
    //    sl1(); // :-)
    //    QVERIFY("" == QEXTLambdaTest::sm_string);
}

void QEXTLambdaTest::testGroupAdaptor()
{
    Bar theBar;
    QEXTLambdaTest::sm_string = "";
    QVERIFY(6 == (qextLambdaGroup(&Foo, qextLambdaSelectors::_1, qextLambdaSelectors::_2))(1, 2));
    QVERIFY("foo(int 1, int 2) " == QEXTLambdaTest::sm_string);

    QEXTLambdaTest::sm_string = "";
    QVERIFY(9 == (qextLambdaGroup(&Foo, qextLambdaSelectors::_2, qextLambdaSelectors::_1))(1, 2));
    QVERIFY("foo(int 2, int 1) " == QEXTLambdaTest::sm_string);

    QEXTLambdaTest::sm_string = "";
    QVERIFY(6 == (qextLambdaGroup(qextMemberFunctor(&Bar::test), qextLambdaSelectors::_1, qextLambdaSelectors::_2, qextLambdaSelectors::_3))(qextReferenceWrapper(theBar), 1, 2));
    QVERIFY("Bar::test(int 1, int 2) " == QEXTLambdaTest::sm_string);
}

QTEST_APPLESS_MAIN(QEXTLambdaTest)

#include <tst_qextlambda.moc>
