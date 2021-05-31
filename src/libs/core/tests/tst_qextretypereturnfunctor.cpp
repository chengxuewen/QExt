#include <qexttrackable.h>
#include <qextpointerfunctor.h>
#include <qextmemberfunctor.h>
#include <qextreferencewrapper.h>
#include <qextbindfunctor.h>
#include <qextretypereturnfunctor.h>
#include <qextslot.h>

#include <QtTest>
#include <QDebug>

class QEXTRetypeReturnFunctorTest : public QObject
{
    Q_OBJECT
private slots:
    void testSimple();


public:
    static int sm_result;
    static QString sm_string;
};

int QEXTRetypeReturnFunctorTest::sm_result = 0;
QString QEXTRetypeReturnFunctorTest::sm_string = "";




struct Foo : public QEXTFunctorBase
{
    typedef float ResultType;

    float operator()(int i) {
        QEXTRetypeReturnFunctorTest::sm_string = QString("Foo(int %1) ").arg(i);
        return i;
    }

    float operator()(float i) {
        QEXTRetypeReturnFunctorTest::sm_string = QString("Foo(float %1) ").arg(i);
        return i * 5;
    }
};

struct Bar : public QEXTTrackable, public QEXTFunctorBase
{
    typedef int ResultType;

    int operator()(int i) {
        QEXTRetypeReturnFunctorTest::sm_string =  QString("Bar(int %1)").arg(i);
        return i;
    }
};




void QEXTRetypeReturnFunctorTest::testSimple()
{
    // retype_return<int>
    QEXTRetypeReturnFunctorTest::sm_string = "";
    QVERIFY(6 == qextRetypeReturnFunctor<int>(Foo())(1.234f));
    QVERIFY("Foo(float 1.234) " == QEXTRetypeReturnFunctorTest::sm_string);

    // retype_return<void> / hide_return
    QEXTRetypeReturnFunctorTest::sm_string = "";
    QEXTSlot<void, int> sl;
    sl = qextRetypeReturnFunctor<void>(Bar());
    sl(5);
    QVERIFY("Bar(int 5)" == QEXTRetypeReturnFunctorTest::sm_string);

    QEXTRetypeReturnFunctorTest::sm_string = "";
    sl = qextHideReturnFunctor(Bar());
    sl(6);
    QVERIFY("Bar(int 6)" == QEXTRetypeReturnFunctorTest::sm_string);
}

QTEST_APPLESS_MAIN(QEXTRetypeReturnFunctorTest)

#include <tst_qextretypereturnfunctor.moc>
