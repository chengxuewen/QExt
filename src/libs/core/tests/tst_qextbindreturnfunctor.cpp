#include <qexttrackable.h>
#include <qextpointerfunctor.h>
#include <qextmemberfunctor.h>
#include <qextreferencewrapper.h>
#include <qextbindreturnfunctor.h>
#include <qextbindfunctor.h>
#include <qextslot.h>

#include <QtTest>
#include <QDebug>

class QEXTBindReturnFunctorTest : public QObject
{
    Q_OBJECT
private slots:
    void testSimple();
    void testReferences();
    void testAutoDisconnect();

public:
    static int sm_result;
    static QString sm_string;
};

int QEXTBindReturnFunctorTest::sm_result = 0;
QString QEXTBindReturnFunctorTest::sm_string = "";



struct Foo
{
    void operator()(int i) {
        QEXTBindReturnFunctorTest::sm_string = QString("Foo(int %1) ").arg(i);
    }

    float operator()(float i)
    {
        QEXTBindReturnFunctorTest::sm_string = QString("Foo(float %1) ").arg(i);
        return i * 5;
    }
};

struct Bar : public QEXTTrackable
{
    Bar(int i = 0) : m_i(i) {}
    operator int() { return m_i; }
    int m_i;
};




void QEXTBindReturnFunctorTest::testSimple()
{
    QVERIFY(-12345 == qextBindReturnFunctor(Foo(), -12345)(5));
    QVERIFY("Foo(int 5) " == QEXTBindReturnFunctorTest::sm_string);
}

void QEXTBindReturnFunctorTest::testReferences()
{
    QString str("guest book");

    qextBindReturnFunctor<QEXTReferenceWrapper<QString> >(Foo(), qextReferenceWrapper(str))(6) = "main";
    QEXTBindReturnFunctorTest::sm_string += str;
    QVERIFY("Foo(int 6) main" == QEXTBindReturnFunctorTest::sm_string);
}

void QEXTBindReturnFunctorTest::testAutoDisconnect()
{
    QEXTSlot<Bar, int> slot;
    {
        Bar choco(-1);
        slot = qextBindReturnFunctor(Foo(), qextReferenceWrapper(choco));
        QVERIFY(-1 == slot(7));
        QVERIFY("Foo(int 7) " == QEXTBindReturnFunctorTest::sm_string);
    } // auto-disconnect

    QVERIFY(0 == slot(8));
}

QTEST_APPLESS_MAIN(QEXTBindReturnFunctorTest)

#include <tst_qextbindreturnfunctor.moc>
