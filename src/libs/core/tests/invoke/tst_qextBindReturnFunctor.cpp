#include <qextPointerFunctor.h>
#include <qextMemberFunctor.h>
#include <qextReferenceWrapper.h>
#include <qextBindReturnFunctor.h>
#include <qextBindFunctor.h>
#include <qextSlot.h>

#include <QtTest>
#include <QObject>

#include <iostream>
#include <string>
#include <sstream>

class QEXTBindReturnFunctorTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testSimple();
    void testReferences();
    void testAutoDisconnect();
};

static std::string sg_string = "";

struct Foo
{
    void operator()(int i)
    {
        std::stringstream sstream;
        sstream << "Foo(int " << i << ") ";
        sg_string = sstream.str();
    }

    float operator()(float i)
    {
        std::stringstream sstream;
        sstream << "Foo(float " << i << ") ";
        sg_string = sstream.str();
        return i * 5;
    }
};

class Bar : public QObject
{
public:
    Bar(int i = 0) : m_i(i) {}
    operator int()
    {
        return m_i;
    }
    int m_i;
};


void QEXTBindReturnFunctorTest::testSimple()
{
    QVERIFY(-12345 == qextBindReturnFunctor(Foo(), -12345)(5));
    QVERIFY("Foo(int 5) " == sg_string);
}

void QEXTBindReturnFunctorTest::testReferences()
{
    std::string str("guest book");

    qextBindReturnFunctor<QEXTReferenceWrapper<std::string> >(Foo(), qextReferenceWrapper(str))(6) = "main";
    sg_string += str;
    QVERIFY("Foo(int 6) main" == sg_string);
}

void QEXTBindReturnFunctorTest::testAutoDisconnect()
{
    QEXTSlot<int, int> slot;
    {
        Bar choco(-1);
        slot = qextBindReturnFunctor(Foo(), qextReferenceWrapper(choco));
        QVERIFY(-1 == slot(7));
        QVERIFY("Foo(int 7) " == sg_string);
    } // auto-disconnect

    QVERIFY(0 == slot(8));
}

QTEST_APPLESS_MAIN(QEXTBindReturnFunctorTest)

#include <tst_qextBindReturnFunctor.moc>
