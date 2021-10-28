#include <qextSlot.h>
#include <qextBindFunctor.h>
#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>
#include <qextTrackObjectFunctor.h>

#include <QtTest>
#include <QObject>

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

#if QEXT_CC_STD_11
#include <functional>
#endif

class QEXTSlotTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void str();
    void testSimple();
    void testImplicitConversion();
    void testReference();
    void testEqualOperator();
    void testCopyCtor();
    void testDisconnect();
    void testFunctor();
    void testMemFunctor();
    void testCompare();
    void testCopyInvalid();
    void teststdLambda();
    void teststdFunction();
    void teststdBind();
};

static int sg_result = 0;
static std::string *sg_string = QEXT_DECL_NULLPTR;

void fooObj(QObject &)
{
    *sg_string = "fooObj(x)";
}

class Foo
{
public:
    void operator()(int i)
    {
        sg_result = i;
        std::stringstream sstream;
        sstream << "foo(int " << i << ")";
        *sg_string = sstream.str();
    }

    void operator()(std::string &str)
    {
        std::stringstream sstream;
        sstream << "foo(string '" << str << "') ";
        *sg_string = sstream.str();
        str = "foo was here";
    }

    void operator()(int, int)
    {
        *sg_string = "foo(int, int)";
    }
};

class MObj : public QObject
{
public:
    MObj() {}

    void function()
    {
        *sg_string = "MObj::function()";
    }
};



void QEXTSlotTest::str()
{
    std::string string;
    sg_string = &string;

    *sg_string = "qextSlotTest";
}

void QEXTSlotTest::testSimple()
{
    std::string string;
    sg_string = &string;

    QEXTSlot< void, int > s1 = Foo();
    s1(1);
    QVERIFY(1 == sg_result);

    s1 = Foo();
    s1(2);
    QVERIFY(2 == sg_result);
}

void QEXTSlotTest::testImplicitConversion()
{
    std::string string;
    sg_string = &string;

    QEXTSlot< void, char > s2 = Foo();
    s2(3);
    QVERIFY(3 == sg_result);
}

void QEXTSlotTest::testReference()
{
    std::string string;
    sg_string = &string;

    QEXTSlot< void, std::string & > sl1 = Foo();
    std::string str("guest book");
    sl1(str);
    *sg_string += str;
    QVERIFY("foo(string 'guest book') foo was here" == *sg_string);
}

void QEXTSlotTest::testEqualOperator()
{
    std::string string;
    sg_string = &string;

    QEXTSlot< void, std::string & > sl1 = Foo();
    std::string str("guest book");
    sl1(str);

    str = "guest book";
    QEXTSlot< void, std::string & > sl2;
    sl2 = sl1;
    sl1 = sl2;
    sl1(str);
    *sg_string += "foo was here";
    QVERIFY("foo(string 'guest book') foo was here" == *sg_string);
}

void QEXTSlotTest::testCopyCtor()
{
    std::string string;
    sg_string = &string;

    QEXTSlot< void, int > s1 = Foo();
    s1(1);
    QVERIFY(1 == sg_result);

    s1 = Foo();
    s1(2);
    QVERIFY(2 == sg_result);

    QEXTSlot< void, int > s1_clone(s1);
    s1_clone(4);
    QVERIFY("foo(int 4)" == *sg_string);
}

void functionFoo()
{
    *sg_string = "functionFoo";
}

void functionBar()
{
    *sg_string = "functionBar";
}


void QEXTSlotTest::testDisconnect()
{
    std::string string;
    sg_string = &string;

    QEXTSlot< void > theSlot(&functionFoo);
    QVERIFY(!theSlot.isConnected());
    QVERIFY(!theSlot.isBlocked());
    QVERIFY(!theSlot.isNull());
    QVERIFY(!theSlot.isTrackable());
    QVERIFY(theSlot.isValid());
    theSlot();
    QVERIFY("functionFoo" == *sg_string);

    theSlot = qextPointerFunctor(&functionBar);
    theSlot();
    QVERIFY("functionBar" == string);

    QEXTSlot< void > objS1ot;
    {
        MObj mObj;
        *sg_string = "";
        objS1ot = qextMemberFunctor(&mObj, &MObj::function);
        QVERIFY(!objS1ot.isConnected());
        QVERIFY(!objS1ot.isBlocked());
        QVERIFY(!objS1ot.isNull());
        QVERIFY(objS1ot.isTrackable());
        QVERIFY(objS1ot.isValid());
        objS1ot();
        QVERIFY("MObj::function()" == string);
    }
    QVERIFY(objS1ot.isNull());
    QVERIFY(!objS1ot.isValid());
    objS1ot();
    QVERIFY("MObj::function()" == string);
}

int func1(int i)
{
    return i;
}

void QEXTSlotTest::testFunctor()
{
    QEXTPointerFunctor<int, int> func = qextPointerFunctor(&func1);
    QEXTSlot<int, int> slot = func;
    QVERIFY(1 == slot(1));
}

class FType
{
public:
    FType() {}

    int func(int i)
    {
        return i;
    }

    void funcR(int &i)
    {
        i++;
    }
};

void QEXTSlotTest::testMemFunctor()
{
    FType fType;
    QEXTMemberFunctor<int, FType, int> memFunc = qextMemberFunctor(&FType::func);
    QEXTSlot<int, FType *, int> slot = memFunc;
    QVERIFY(1 == slot(&fType, 1));

    QEXTMemberFunctor<void, FType, int &> memFuncR = qextMemberFunctor(&FType::funcR);
    QEXTSlot<void, FType *, int &> slotR = memFuncR;
    int a1 = 1;
    slotR(&fType, a1);
    QVERIFY(2 == a1);

    QEXTBoundMemberFunctor<int, FType, int> boundMemFunc = qextMemberFunctor(&fType, &FType::func);
    QEXTSlot<int, int> slot2 = boundMemFunc;
    QVERIFY(1 == slot2(1));
}

void QEXTSlotTest::testCompare()
{
    QEXTMemberFunctor<void, FType, int &> memFuncR = qextMemberFunctor(&FType::funcR);
    QEXTSlot<void, FType *, int &> slotR = memFuncR;
    QEXTSlot<void, FType *, int &> slotR1 = slotR;
    QEXTSlot<void, FType *, int &> slotR2;
    QEXTSlot<void, FType *, int &> slotR3;
    QVERIFY(slotR == slotR1);
    QVERIFY(slotR != slotR2);
    QVERIFY(slotR2 == slotR3);
}

void QEXTSlotTest::testCopyInvalid()
{
    std::string string;
    sg_string = &string;

    QObject *obj = new QObject;

    *sg_string = "";
    QEXTSlot<void> fooSlot = qextBindFunctor(qextPointerFunctor(&fooObj), qextReferenceWrapper(*obj));
    fooSlot();
    QVERIFY("fooObj(x)" == *sg_string);

    // This invalidates foo.
    delete obj;

    // Try to crash if the invalid slot parameter is used by libsigc++,
    // and get a debugger backtrace at the point that it happens.
    //
    // Comment this out to get a meaningful backtrace from valgrind.
    //
    // Try to pollute the memory previously occupied by the QObject
    // instance. The hope is that with a regular memory allocator (i.e. not
    // valgrind), we end up with buffer == (void *)t.
    void *buffer = malloc(sizeof(QObject));
    memset(buffer, 0xFF, sizeof(QObject));

    //  the copy constructor fails
    // because the pointer value it dereferences does not point to a
    // QObject anymore, it now points to a polluted buffer.
    *sg_string = "";
    QEXTSlot<void> barSlot = fooSlot;
    barSlot();
    QVERIFY("" == *sg_string);

    free(buffer);
}


void egon(std::string &str)
{
    std::stringstream sstream;
    sstream << "egon(string '" << str << "')";
    *sg_string = sstream.str();
    str = "egon was here";
}


void QEXTSlotTest::teststdLambda()
{
#if QEXT_CC_STD_11
    std::string string;
    sg_string = &string;

    QEXTSlot<void> slot;

    std::string guestBook("karl");
    slot = [ = ]()
    {
        *sg_string = "stdLambda";
    };
    slot();
    QVERIFY("stdLambda" == *sg_string);

    QEXTFunction<void> trackObjectTestFunctor = [ = ]()
    {
        *sg_string = "qextTrackObjectFunctor::stdLambda";
    };
    slot = qextTrackObjectFunctor(trackObjectTestFunctor, guestBook);
    slot();
    QVERIFY("qextTrackObjectFunctor::stdLambda" == *sg_string);

    QEXTSlot<int> slot1 = []() ->int { return 22;};
    QVERIFY(22 == slot1());

    QEXTSlot<int, int> slot2 = [](int i) ->int { return i;};
    QVERIFY(11 == slot2(11));

    QEXTSlot<std::string, int &> slot3 = [](int &i)
    {
        i++;
        return std::string("name");
    };
    int iValue = 5;
    QVERIFY("name" == slot3(iValue));
    QVERIFY(6 == iValue);

    QEXTSlot<double, int, int> slot4 = [](int i, int j)
    {
        return double(i + j);
    };
    QVERIFY(3 == slot4(1, 2));


    QEXTSlot<double, int, int> slot5;
    auto mod = [](int i, int j)
    {
        return double(i + j);
    };
    slot5 = mod;
    QVERIFY(3 == slot5(1, 2));
#endif
}

void QEXTSlotTest::teststdFunction()
{
#if QEXT_CC_STD_11
    std::string string;
    sg_string = &string;

    QEXTSlot<int, int> slot;
    typedef std::function<int(int)> Functional;
    auto lambda = [](int a) ->int { return a; };
    Functional obj = lambda;
    slot = obj;
    QVERIFY(1 == slot(1));
#endif
}

void QEXTSlotTest::teststdBind()
{
#if QEXT_CC_STD_11
    std::string string;
    sg_string = &string;

    QEXTSlot<void> slot;

    std::string guestBook("karl");
    std::function<void()> func(std::bind(&egon, std::ref(guestBook)));
    //        slot = std::bind(&egon, std::ref(guestBook)); // does not compile
    slot = func;
    slot();
    QVERIFY("egon(string 'karl')" == string);
#endif
}


QTEST_APPLESS_MAIN(QEXTSlotTest)

#include <tst_qextSlot.moc>
