#include <qextRetypeFunctor.h>

#include <QtTest>
#include <QObject>

#include <iostream>
#include <string>
#include <sstream>

class QExtRetypeFunctorTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testSimple();
};

static std::string *sg_string = QEXT_NULLPTR;


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


void QExtRetypeFunctorTest::testSimple()
{
    std::string string;
    sg_string = &string;

    Foo foo;
    *sg_string = "";
    QVERIFY(1.5 == qextRetypeFunctor(qextMakeFunctor(foo, &Foo::testInt))(1.234f));
    QVERIFY("Foo::testInt(int 1) " == *sg_string);

    *sg_string = "";
    QVERIFY(25 == qextRetypeFunctor(qextMakeFunctor(foo, &Foo::testFloat))(5));
    QVERIFY("Foo::testFloat(float 5) " == *sg_string);

    *sg_string = "";
    qextRetypeFunctor(qextMakeFunctor(foo, &Foo::testVoid))(1.234f);
    QVERIFY("Foo::testVoid(int 1) " == *sg_string);

    *sg_string = "";
    qextRetypeFunctor(qextMakeFunctor(&Bar))(6.789f);
    QVERIFY("bar(short 6)" == *sg_string);
    return;

    *sg_string = "";
    QExtFunction<float, float> s1 = qextRetypeFunctor(qextMakeFunctor(foo, &Foo::testInt));
    QExtFunction<float, int>   s2 = qextRetypeFunctor(qextMakeFunctor(foo, &Foo::testFloat));
    QExtFunction<void, double> s3 = qextRetypeFunctor(qextMakeFunctor(&Bar));
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

QTEST_APPLESS_MAIN(QExtRetypeFunctorTest)

#include <tst_qextRetypeFunctor.moc>
