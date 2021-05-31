#include <qextslot.h>
#include <qextbindfunctor.h>
#include <qextpointerfunctor.h>
#include <qextmemberfunctor.h>

#include <QtTest>
#include <QDebug>

class QEXTSlotTest : public QObject
{
    Q_OBJECT
private slots:
    void testSimple();
    void testImplicitConversion();
    void testReference();
    void testEqualOperator();
    void testCopyCtor();
    void testDisconnect();
    void testFunctor();
    void testMemFunctor();
    void testCopyInvalid();

public:
    static int sm_result;
    static QString sm_string;
};

int QEXTSlotTest::sm_result = 0;
QString QEXTSlotTest::sm_string = "";



void foo(QEXTTrackable&)
{
    QEXTSlotTest::sm_string = "foo(x)";
}


class Foo
{
public:
    void operator()(int i) {
        QEXTSlotTest::sm_result = i;
        QEXTSlotTest::sm_string = QString("foo(int %1)").arg(i);
    }

    void operator()(QString &str) {
        QEXTSlotTest::sm_string = QString("foo(string '%1') ").arg(str);
        str = "foo was here";
    }

    void operator()(int, int) {
        QEXTSlotTest::sm_string = "foo(int, int)";
    }
};




void QEXTSlotTest::testSimple()
{
    QEXTSlot<void, int> s1 = Foo();
    s1(1);
    QVERIFY(1 == sm_result);

    s1 = Foo();
    s1(2);
    QVERIFY(2 == sm_result);
}

void QEXTSlotTest::testImplicitConversion()
{
    QEXTSlot<void, char> s2 = Foo();
    s2(3);
    QVERIFY(3 == sm_result);
}

void QEXTSlotTest::testReference()
{
    QEXTSlot<void, QString &> sl1 = Foo();
    QString str("guest book");
    sl1(str);
    sm_string += str;
    QVERIFY2("foo(string 'guest book') foo was here" == sm_string, str.toLatin1().data());
}

void QEXTSlotTest::testEqualOperator()
{
    QEXTSlot<void, QString &> sl1 = Foo();
    QString str("guest book");
    sl1(str);

    str = "guest book";
    QEXTSlot<void, QString &> sl2;
    sl2 = sl1;
    sl1 = sl2;
    sl1(str);
    sm_string += "foo was here";
    QVERIFY("foo(string 'guest book') foo was here" == sm_string);
}

void QEXTSlotTest::testCopyCtor()
{
    QEXTSlot<void, int> s1 = Foo();
    s1(1);
    QVERIFY(1 == sm_result);

    s1 = Foo();
    s1(2);
    QVERIFY(2 == sm_result);

    QEXTSlot<void, int> s1_clone(s1);
    s1_clone(4);
    QVERIFY("foo(int 4)" == sm_string);
}

void functionFoo()
{
    QEXTSlotTest::sm_string = "functionFoo";
}

void functionBar()
{
    QEXTSlotTest::sm_string = "functionBar";
}

void QEXTSlotTest::testDisconnect()
{
    QEXTSlot<void> theSlot(qextPointerFunctor(&functionFoo));
    theSlot();
    QVERIFY("functionFoo" == QEXTSlotTest::sm_string);

    QEXTSlotTest::sm_string = "";
    theSlot.disconnect();
    theSlot();
    QVERIFY("" == QEXTSlotTest::sm_string);

    theSlot = qextPointerFunctor(&functionBar);
    theSlot();
    QVERIFY("functionBar" == QEXTSlotTest::sm_string);
}

int func1(int i) {
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

    int func(int i) {
        return i;
    }


    void funcR(int &i) {
        i++;
    }
};

void QEXTSlotTest::testMemFunctor()
{
    FType fType;
    QEXTMemberFunctor<int, FType, int> memFunc = qextMemberFunctor(&FType::func);
    QEXTSlot<int, FType*, int> slot = memFunc;
    QVERIFY(1 == slot(&fType, 1));

    QEXTMemberFunctor<void, FType, int&> memFuncR = qextMemberFunctor(&FType::funcR);
    QEXTSlot<void, FType*, int&> slotR = memFuncR;
    int a1 = 1;
    slotR(&fType, a1);
    QVERIFY(2 == a1);

    QEXTBoundMemberFunctor<int, FType, int> boundMemFunc = qextMemberFunctor(&fType, &FType::func);
    QEXTSlot<int, int> slot2 = boundMemFunc;
    QVERIFY(1 == slot2(1));
}

void QEXTSlotTest::testCopyInvalid()
{
    //    std::ostringstream pointer_stream;
    QEXTTrackable *t = new QEXTTrackable;
    //    pointer_stream << t;
    //    result_stream << "sigc::trackable instance at " << pointer_stream.str();
    //    util->check_result(result_stream, "sigc::trackable instance at " + pointer_stream.str());
    //    pointer_stream.str("");

    sm_string = "";
    QEXTSlot<void> fooSlot = qextBindFunctor(qextPointerFunctor(&foo), qextReferenceWrapper(*t));
    fooSlot();
    QVERIFY("foo(x)" == sm_string);

    // This invalidates foo.
    delete t;

    // Try to crash if the invalid slot parameter is used by libsigc++,
    // and get a debugger backtrace at the point that it happens.
    //
    // Comment this out to get a meaningful backtrace from valgrind.
    //
    // Try to pollute the memory previously occupied by the sigc::trackable
    // instance. The hope is that with a regular memory allocator (i.e. not
    // valgrind), we end up with buffer == (void *)t.
    void *buffer = malloc(sizeof(QEXTTrackable));
    memset(buffer, 0xFF, sizeof(QEXTTrackable));

    //    pointer_stream << buffer;
    //    result_stream << "         Polluted buffer at " << pointer_stream.str();
    //    util->check_result(result_stream, "         Polluted buffer at " + pointer_stream.str());
    //    pointer_stream.str("");

    //  the copy constructor fails
    // because the pointer value it dereferences does not point to a
    // QEXTTrackable anymore, it now points to a polluted buffer.
    sm_string = "";
    QEXTSlot<void> barSlot = fooSlot;
    barSlot();
    QVERIFY("" == sm_string);

    free(buffer);
}

QTEST_APPLESS_MAIN(QEXTSlotTest)

#include <tst_qextslot.moc>
