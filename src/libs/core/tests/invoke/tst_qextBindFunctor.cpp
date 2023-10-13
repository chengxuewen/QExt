#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>
#include <qextReferenceWrapper.h>
#include <qextBindFunctor.h>
#include <qextFunction.h>

#include <QtTest>
#include <QObject>

#include <iostream>
#include <string>
#include <sstream>

class QExtBindFunctorTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testBind2nd();
    void testMultiple();
    void testBindFromEnd();
    void testUsedTogether();
    void testVoidReturn();
    void testFunctionPointerInsteadOfFunctor();
    void testReturnTypeOfBindFunctorOverloadWithNoArguments();
    void testReferences();
};

static std::string *sg_string = QEXT_DECL_NULLPTR;

struct Foo : public QExtFunctorBase
{
    // choose a type that can hold all return values
    typedef int Return;

    int operator()(int i)
    {
        std::stringstream sstream;
        sstream << "Foo(int " << i << ") ";
        *sg_string = sstream.str();
        return i > 0;
    }

    int operator()(int i, int j)
    {
        std::stringstream sstream;
        sstream << "Foo(int " << i << ", int " << j << ") ";
        *sg_string = sstream.str();
        return i + j;
    }

    int operator()(int i, int j, int k)
    {
        std::stringstream sstream;
        sstream << "Foo(int " << i << ", int " << j << ", int " << k << ") ";
        *sg_string = sstream.str();
        return 0;
    }
};

struct FooVoid : public QExtFunctorBase
{
    typedef void Return;

    void operator()(int i)
    {
        std::stringstream sstream;
        sstream << "FooVoid(int " << i << ")";
        *sg_string = sstream.str();
    }
};

int Bar(int i, int j)
{
    std::stringstream sstream;
    sstream << "bar(int " << i << ", int " << j << ") ";
    *sg_string = sstream.str();
    return i + j;
}

bool simple(bool test)
{
    std::stringstream sstream;
    sstream << "simple(bool " << test << ") ";
    *sg_string = sstream.str();
    return test;
}

void egon(std::string &str)
{
    std::stringstream sstream;
    sstream << "egon(string '" << str << "')";
    *sg_string = sstream.str();
    str = "egon was here";
}


class Book : public QObject
{
public:
    Book(const std::string &name) : m_name(name) {}
    std::string &getName()
    {
        return m_name;
    }
    operator std::string &()
    {
        return getName();
    }

private:
    std::string m_name;

    //non-copyable:
    Book(const Book &);
    Book &operator=(const Book &);
};


class Param : public QObject
{
public:
    Param(const std::string &name) : m_name(name) {}

    void operator()() { }

    std::string m_name;

private:
    //non-copyable, so it can only be used with qextBindFunctor() via qextReferenceWrapper()
    Param(const Param &);
    Param &operator=(const Param &);
};

void handler(Param &param)
{
    std::stringstream sstream;
    sstream << "  handler(param): param.name_=" << param.m_name;
    *sg_string = sstream.str();
}


void QExtBindFunctorTest::testBind2nd()
{
    std::string string;
    sg_string = &string;

    *sg_string = "";
    int ret = qextBindFunctor<0>(Foo(), -12345)(5);
    QVERIFY(-12345 + 5 == ret);
    QVERIFY("Foo(int -12345, int 5) " == *sg_string);

    *sg_string = "";
    ret = qextBindFunctor<1>(Foo(), -12345)(5);
    QVERIFY(-12345 + 5 == ret);
    QVERIFY("Foo(int 5, int -12345) " == *sg_string);
}

void QExtBindFunctorTest::testMultiple()
{
    std::string string;
    sg_string = &string;

    *sg_string = "";
    qextBindFunctor(Foo(), 1, 2)();
    QVERIFY("Foo(int 1, int 2) " == *sg_string);
}

void QExtBindFunctorTest::testBindFromEnd()
{
    std::string string;
    sg_string = &string;

    *sg_string = "";
    qextBindFunctor < -1 > (Foo(), 4)(3);
    QVERIFY("Foo(int 3, int 4) " == *sg_string);

    *sg_string = "";
    qextBindFunctor(Foo(), 4)(3);
    QVERIFY("Foo(int 3, int 4) " == *sg_string);
}

void QExtBindFunctorTest::testUsedTogether()
{
    std::string string;
    sg_string = &string;

    *sg_string = "";
    qextBindFunctor<0>(qextBindFunctor<0>(Foo(), 7), 8)();
    QVERIFY("Foo(int 7, int 8) " == *sg_string);
}

void QExtBindFunctorTest::testVoidReturn()
{
    std::string string;
    sg_string = &string;

    *sg_string = "";
    qextBindFunctor(Foo(), 9, 10)(11); // (only returned void if typeof() would be supported)
    QVERIFY("Foo(int 11, int 9, int 10) " == *sg_string);

    *sg_string = "";
    qextBindFunctor(FooVoid(), 12)();
    QVERIFY("FooVoid(int 12)" == *sg_string);
}

void QExtBindFunctorTest::testFunctionPointerInsteadOfFunctor()
{
    std::string string;
    sg_string = &string;

    *sg_string = "";
    Book testBook("otto");
    *sg_string = qextBindFunctor<0>(&Book::getName, qextReferenceWrapper(testBook))();
    QVERIFY("otto" == *sg_string);
}

void QExtBindFunctorTest::testReturnTypeOfBindFunctorOverloadWithNoArguments()
{
    std::string string;
    sg_string = &string;

    *sg_string = "";
    qextBindFunctor(Foo(), 15)();
    QVERIFY("Foo(int 15) " == *sg_string);

    *sg_string = "";
    qextBindFunctor(&simple, true)();
    QVERIFY("simple(bool 1) " == *sg_string);
}

void QExtBindFunctorTest::testReferences()
{
    std::string string;
    sg_string = &string;

    std::string str("guest book");
    qextBindFunctor(&egon, qextReferenceWrapper(str))(); // Tell bind that it shall store a reference.
    QVERIFY("egon was here" == str);
    QVERIFY("egon(string 'guest book')" == *sg_string);

    QExtFunction<void> slot;
    {
        *sg_string = "";
        Book guestBook("karl");
        slot = qextBindFunctor(&egon, qextReferenceWrapper(guestBook));
        slot();
        QVERIFY("egon was here" == str);
        QVERIFY("egon(string 'karl')" == *sg_string);
    } // auto-disconnect

    *sg_string = "";
    slot();
    QVERIFY("" == *sg_string);



    QExtFunction<void, Param &> slotFull = qextPointerFunctor(handler);
    QExtFunction<void> slotBound;

    *sg_string = "";
    slotBound();
    QVERIFY("" == *sg_string);

    {
        //Because Param derives from QEXTQmlQuickObject(), qextReferenceWrapper() should disconnect
        // the signal handler when param is destroyed.
        Param param("murrayc");
        // A convoluted way to do
        slotBound = qextBindFunctor(slotFull, qextReferenceWrapper(param));

        *sg_string = "";
        slotBound();
        QVERIFY("  handler(param): param.name_=murrayc" == *sg_string);
    } // auto-disconnect

    *sg_string = "Calling slot when param does not exist:";
    slotBound();
    QVERIFY("Calling slot when param does not exist:" == *sg_string);
}


QTEST_APPLESS_MAIN(QExtBindFunctorTest)

#include <tst_qextBindFunctor.moc>
