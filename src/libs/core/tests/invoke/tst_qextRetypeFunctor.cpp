#include <qextRetypeFunctor.h>

#include <QtTest>
#include <QObject>

#include <iostream>
#include <string>
#include <sstream>

class QEXTRetypeFunctorTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testSimple();
};

static std::string *sg_string = QEXT_DECL_NULLPTR;


struct Foo : public QObject
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


void QEXTRetypeFunctorTest::testSimple()
{
    std::string string;
    sg_string = &string;

    Foo foo;
    *sg_string = "";
    QVERIFY(1.5 == qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testInt))(1.234f));
    QVERIFY("Foo::testInt(int 1) " == *sg_string);

    *sg_string = "";
    QVERIFY(25 == qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testFloat))(5));
    QVERIFY("Foo::testFloat(float 5) " == *sg_string);

    *sg_string = "";
    qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testVoid))(1.234f);
    QVERIFY("Foo::testVoid(int 1) " == *sg_string);

    *sg_string = "";
    qextRetypeFunctor(qextPointerFunctor(&Bar))(6.789f);
    QVERIFY("bar(short 6)" == *sg_string);
    return;

    *sg_string = "";
    QEXTSlot<float, float> s1 = qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testInt));
    QEXTSlot<float, int>   s2 = qextRetypeFunctor(qextMemberFunctor(foo, &Foo::testFloat));
    QEXTSlot<void, double> s3 = qextRetypeFunctor(qextPointerFunctor(&Bar));
    QVERIFY(1.5 == s1(1.234f));
    QVERIFY("Foo::testInt(int 1) " == *sg_string);

    *sg_string = "";
    QVERIFY(25 == s2(5));
    QVERIFY("Foo::testFloat(float 5) " == *sg_string);

    *sg_string = "";
    s3(6.789);
    QVERIFY("bar(short 6)" == *sg_string);

    *sg_string = "";
    //TODO
    //        s2 = qextRetypeFunctor(s1);
    QVERIFY(7.5 == s2(5));
    QVERIFY("Foo::testInt(int 5) " == *sg_string);
}

QTEST_APPLESS_MAIN(QEXTRetypeFunctorTest)

#include <tst_qextRetypeFunctor.moc>
