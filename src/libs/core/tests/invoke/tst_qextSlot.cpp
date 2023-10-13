#include <qextFunction.h>
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

class QExtFunctionTest : public QObject
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



void QExtFunctionTest::str()
{
    std::string string;
    sg_string = &string;

    *sg_string = "qextSlotTest";
}

void QExtFunctionTest::testSimple()
{
    std::string string;
    sg_string = &string;

    QExtFunction< void, int > s1 = Foo();
    s1(1);
    QVERIFY(1 == sg_result);

    s1 = Foo();
    s1(2);
    QVERIFY(2 == sg_result);
}

void QExtFunctionTest::testImplicitConversion()
{
    std::string string;
    sg_string = &string;

    QExtFunction< void, char > s2 = Foo();
    s2(3);
    QVERIFY(3 == sg_result);
}

void QExtFunctionTest::testReference()
{
    std::string string;
    sg_string = &string;

    QExtFunction< void, std::string & > sl1 = Foo();
    std::string str("guest book");
    sl1(str);
    *sg_string += str;
    QVERIFY("foo(string 'guest book') foo was here" == *sg_string);
}

void QExtFunctionTest::testEqualOperator()
{
    std::string string;
    sg_string = &string;

    QExtFunction< void, std::string & > sl1 = Foo();
    std::string str("guest book");
    sl1(str);

    str = "guest book";
    QExtFunction< void, std::string & > sl2;
    sl2 = sl1;
    sl1 = sl2;
    sl1(str);
    *sg_string += "foo was here";
    QVERIFY("foo(string 'guest book') foo was here" == *sg_string);
}

void QExtFunctionTest::testCopyCtor()
{
    std::string string;
    sg_string = &string;

    QExtFunction< void, int > s1 = Foo();
    s1(1);
    QVERIFY(1 == sg_result);

    s1 = Foo();
    s1(2);
    QVERIFY(2 == sg_result);

    QExtFunction< void, int > s1_clone(s1);
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


void QExtFunctionTest::testDisconnect()
{
    std::string string;
    sg_string = &string;

    QExtFunction< void > theSlot(&functionFoo);
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

    QExtFunction< void > objS1ot;
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

void QExtFunctionTest::testFunctor()
{
    QExtPointerFunctor<int, int> func = qextPointerFunctor(&func1);
    QExtFunction<int, int> slot = func;
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

void QExtFunctionTest::testMemFunctor()
{
    FType fType;
    QExtMemberFunctor<int, FType, int> memFunc = qextMemberFunctor(&FType::func);
    QExtFunction<int, FType *, int> slot = memFunc;
    QVERIFY(1 == slot(&fType, 1));

    QExtMemberFunctor<void, FType, int &> memFuncR = qextMemberFunctor(&FType::funcR);
    QExtFunction<void, FType *, int &> slotR = memFuncR;
    int a1 = 1;
    slotR(&fType, a1);
    QVERIFY(2 == a1);

    QExtBoundMemberFunctor<int, FType, int> boundMemFunc = qextMemberFunctor(&fType, &FType::func);
    QExtFunction<int, int> slot2 = boundMemFunc;
    QVERIFY(1 == slot2(1));
}

void QExtFunctionTest::testCompare()
{
    QExtMemberFunctor<void, FType, int &> memFuncR = qextMemberFunctor(&FType::funcR);
    QExtFunction<void, FType *, int &> slotR = memFuncR;
    QExtFunction<void, FType *, int &> slotR1 = slotR;
    QExtFunction<void, FType *, int &> slotR2;
    QExtFunction<void, FType *, int &> slotR3;
    QVERIFY(slotR == slotR1);
    QVERIFY(slotR != slotR2);
    QVERIFY(slotR2 == slotR3);
}

void QExtFunctionTest::testCopyInvalid()
{
    std::string string;
    sg_string = &string;

    QObject *obj = new QObject;

    *sg_string = "";
    QExtFunction<void> fooSlot = qextBindFunctor(qextPointerFunctor(&fooObj), qextReferenceWrapper(*obj));
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
    QExtFunction<void> barSlot = fooSlot;
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


void QExtFunctionTest::teststdLambda()
{
#if QEXT_CC_STD_11
    std::string string;
    sg_string = &string;

    QExtFunction<void> slot;

    std::string guestBook("karl");
    slot = [ = ]()
    {
        *sg_string = "stdLambda";
    };
    slot();
    QVERIFY("stdLambda" == *sg_string);

    QExtFunction<void> trackObjectTestFunctor = [ = ]()
    {
        *sg_string = "qextTrackObjectFunctor::stdLambda";
    };
    slot = qextTrackObjectFunctor(trackObjectTestFunctor, guestBook);
    slot();
    QVERIFY("qextTrackObjectFunctor::stdLambda" == *sg_string);

    QExtFunction<int> slot1 = []() ->int { return 22;};
    QVERIFY(22 == slot1());

    QExtFunction<int, int> slot2 = [](int i) ->int { return i;};
    QVERIFY(11 == slot2(11));

    QExtFunction<std::string, int &> slot3 = [](int &i)
    {
        i++;
        return std::string("name");
    };
    int iValue = 5;
    QVERIFY("name" == slot3(iValue));
    QVERIFY(6 == iValue);

    QExtFunction<double, int, int> slot4 = [](int i, int j)
    {
        return double(i + j);
    };
    QVERIFY(3 == slot4(1, 2));


    QExtFunction<double, int, int> slot5;
    auto mod = [](int i, int j)
    {
        return double(i + j);
    };
    slot5 = mod;
    QVERIFY(3 == slot5(1, 2));
#endif
}

void QExtFunctionTest::teststdFunction()
{
#if QEXT_CC_STD_11
    std::string string;
    sg_string = &string;

    QExtFunction<int, int> slot;
    typedef std::function<int(int)> Functional;
    auto lambda = [](int a) ->int { return a; };
    Functional obj = lambda;
    slot = obj;
    QVERIFY(1 == slot(1));
#endif
}

void QExtFunctionTest::teststdBind()
{
#if QEXT_CC_STD_11
    std::string string;
    sg_string = &string;

    QExtFunction<void> slot;

    std::string guestBook("karl");
    std::function<void()> func(std::bind(&egon, std::ref(guestBook)));
    //        slot = std::bind(&egon, std::ref(guestBook)); // does not compile
    slot = func;
    slot();
    QVERIFY("egon(string 'karl')" == string);
#endif
}


QTEST_APPLESS_MAIN(QExtFunctionTest)

#include <tst_qextSlot.moc>
