#include <qexttrackable.h>
#include <qextpointerfunctor.h>
#include <qextmemberfunctor.h>
#include <qextreferencewrapper.h>
#include <qextbindfunctor.h>
#include <qextslot.h>

#include <QtTest>
#include <QDebug>


class QEXTBindFunctorTest : public QObject
{
    Q_OBJECT
private slots:
    void testBind2nd();
    void testMultiple();
    void testBindFromEnd();
    void testUsedTogether();
    void testVoidReturn();
    void testFunctionPointerInsteadOfFunctor();
    void testReturnTypeOfBindFunctorOverloadWithNoArguments();
    void testReferences();


public:
    static int sm_result;
    static QString sm_string;
};

int QEXTBindFunctorTest::sm_result = 0;
QString QEXTBindFunctorTest::sm_string = "";



struct Foo : public QEXTFunctorBase
{
    // choose a type that can hold all return values
    typedef int ResultType;

    int operator()(int i)
    {
        QEXTBindFunctorTest::sm_string = QString("Foo(int %1) ").arg(i);
        return i > 0;
    }

    int operator()(int i, int j)
    {
        QEXTBindFunctorTest::sm_string = QString("Foo(int %1, int %2) ").arg(i).arg(j);
        return i + j;
    }

    int operator()(int i, int j, int k)
    {
        QEXTBindFunctorTest::sm_string = QString("Foo(int %1, int %2, int %3) ").arg(i).arg(j).arg(k);
        return 0;
    }
};

struct FooVoid : public QEXTFunctorBase
{
    typedef void ResultType;

    void operator()(int i)
    {
        QEXTBindFunctorTest::sm_string = QString("FooVoid(int %1)").arg(i);
    }
};

int Bar(int i, int j)
{
    QEXTBindFunctorTest::sm_string = QString("bar(int %1, int %2) ").arg(i).arg(j);
    return i + j;
}

bool simple(bool test)
{
    QEXTBindFunctorTest::sm_string = QString("simple(bool %1) ").arg(test);
    return test;
}

void egon(QString &str)
{
    QEXTBindFunctorTest::sm_string = QString("egon(string '%1')").arg(str);
    str = "egon was here";
}


struct Book : public QEXTTrackable
{
    Book(const QString &name) : m_name(name) {}
    QString &getName()  { return m_name; }
    operator QString &() { return getName(); }

private:
    QString m_name;

    //non-copyable:
    Book(const Book&);
    Book& operator=(const Book&);
};


class Param : public QEXTTrackable
{
public:
    Param(const QString &name) : m_name(name) {}

    operator void () { }

    QString m_name;

private:
    //non-copyable, so it can only be used with qextBindFunctor() via qextReferenceWrapper()
    Param(const Param&);
    Param& operator=(const Param&);
};

void handler(Param &param)
{
    QEXTBindFunctorTest::sm_string = QString("  handler(param): param.name_=%1").arg(param.m_name);
}


void QEXTBindFunctorTest::testBind2nd()
{
    QEXTBindFunctorTest::sm_string = "";
    int ret = qextBindFunctor<0>(Foo(), -12345)(5);
    QVERIFY(-12345 + 5 == ret);
    QVERIFY("Foo(int -12345, int 5) " == QEXTBindFunctorTest::sm_string);

    QEXTBindFunctorTest::sm_string = "";
    ret = qextBindFunctor<1>(Foo(), -12345)(5);
    QVERIFY(-12345 + 5 == ret);
    QVERIFY("Foo(int 5, int -12345) " == QEXTBindFunctorTest::sm_string);
}

void QEXTBindFunctorTest::testMultiple()
{
    QEXTBindFunctorTest::sm_string = "";
    qextBindFunctor(Foo(), 1, 2)();
    QVERIFY("Foo(int 1, int 2) " == QEXTBindFunctorTest::sm_string);
}

void QEXTBindFunctorTest::testBindFromEnd()
{
    QEXTBindFunctorTest::sm_string = "";
    qextBindFunctor<-1>(Foo(), 4)(3);
    QVERIFY("Foo(int 3, int 4) " == QEXTBindFunctorTest::sm_string);

    QEXTBindFunctorTest::sm_string = "";
    qextBindFunctor(Foo(), 4)(3);
    QVERIFY("Foo(int 3, int 4) " == QEXTBindFunctorTest::sm_string);
}

void QEXTBindFunctorTest::testUsedTogether()
{
    QEXTBindFunctorTest::sm_string = "";
    qextBindFunctor<0>(qextBindFunctor<0>(Foo(), 7), 8)();
    QVERIFY("Foo(int 7, int 8) " == QEXTBindFunctorTest::sm_string);
}

void QEXTBindFunctorTest::testVoidReturn()
{
    QEXTBindFunctorTest::sm_string = "";
    qextBindFunctor(Foo(), 9, 10)(11); // (only returned void if typeof() would be supported)
    QVERIFY("Foo(int 11, int 9, int 10) " == QEXTBindFunctorTest::sm_string);

    QEXTBindFunctorTest::sm_string = "";
    qextBindFunctor(FooVoid(), 12)();
    QVERIFY("FooVoid(int 12)" == QEXTBindFunctorTest::sm_string);
}

void QEXTBindFunctorTest::testFunctionPointerInsteadOfFunctor()
{
    QEXTBindFunctorTest::sm_string = "";
    Book testBook("otto");
    QEXTBindFunctorTest::sm_string = qextBindFunctor<0>(&Book::getName, qextReferenceWrapper(testBook))();
    QVERIFY("otto" == QEXTBindFunctorTest::sm_string);
}

void QEXTBindFunctorTest::testReturnTypeOfBindFunctorOverloadWithNoArguments()
{
    QEXTBindFunctorTest::sm_string = "";
    qextBindFunctor(Foo(), 15)();
    QVERIFY("Foo(int 15) " == QEXTBindFunctorTest::sm_string);

    QEXTBindFunctorTest::sm_string = "";
    qextBindFunctor(&simple, true)();
    QVERIFY("simple(bool 1) " == QEXTBindFunctorTest::sm_string);
}

void QEXTBindFunctorTest::testReferences()
{
    QEXTBindFunctorTest::sm_string = "";
    QString str("guest book");
    qextBindFunctor(&egon, qextReferenceWrapper(str))(); // Tell bind that it shall store a reference.
    QVERIFY("egon was here" == str);
    QVERIFY("egon(string 'guest book')" == QEXTBindFunctorTest::sm_string);

    QEXTSlot<void> slot;
    {
        QEXTBindFunctorTest::sm_string = "";
        Book guestBook("karl");
        slot = qextBindFunctor(&egon, qextReferenceWrapper(guestBook));
        slot();
        QVERIFY("egon was here" == str);
        QVERIFY("egon(string 'karl')" == QEXTBindFunctorTest::sm_string);
    } // auto-disconnect

    QEXTBindFunctorTest::sm_string = "";
    slot();
    QVERIFY("" == QEXTBindFunctorTest::sm_string);



    QEXTSlot<void, Param&> slotFull = qextPointerFunctor(&handler);
    QEXTSlot<void> slotBound;

    QEXTBindFunctorTest::sm_string = "";
    slotBound();
    QVERIFY("" == QEXTBindFunctorTest::sm_string);

    {
        //Because Param derives from QEXTTrackable(), qextReferenceWrapper() should disconnect
        // the signal handler when param is destroyed.
        Param param("murrayc");
        // A convoluted way to do
        slotBound = qextBindFunctor(slotFull, qextReferenceWrapper(param));

        QEXTBindFunctorTest::sm_string = "";
        slotBound();
        QVERIFY2("  handler(param): param.name_=murrayc" == QEXTBindFunctorTest::sm_string, QEXTBindFunctorTest::sm_string.toLatin1().data());
    } // auto-disconnect

    QEXTBindFunctorTest::sm_string = "Calling slot when param does not exist:";
    slotBound();
    QVERIFY("Calling slot when param does not exist:" == QEXTBindFunctorTest::sm_string);
}


QTEST_APPLESS_MAIN(QEXTBindFunctorTest)

#include <tst_qextbindfunctor.moc>
