#include <qextMemberFunctor.h>
#include <qextFunction.h>

#include <QtTest>
#include <QObject>

#include <iostream>
#include <string>
#include <sstream>

class QExtTrackableTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testSimple();
};

static std::string sg_string = "";


class MYClass: public QObject
{
public:
    void foo()
    {
        std::stringstream sstream;
        sstream << i;
        sg_string = sstream.str();
    }

    int i;
};


void QExtTrackableTest::testSimple()
{
    QExtFunction<void> slot;
    MYClass *myClass = new MYClass;
    myClass->i = 11;
    slot = qextMemberFunctor(myClass, &MYClass::foo);
    delete myClass;
    myClass = QEXT_DECL_NULLPTR;

    QExtFunction<void> sl;
    {
        sg_string = "";
        MYClass t;
        t.i = 10;
        sl = qextMemberFunctor(&t, &MYClass::foo);
        sl();
        QVERIFY("10" == sg_string);
    }

    sg_string = "";
    sl();
    QVERIFY("" == sg_string);

    MYClass *myCLass = new MYClass;
    delete myCLass;
    myCLass = QEXT_DECL_NULLPTR;
}

QTEST_APPLESS_MAIN(QExtTrackableTest)

#include <tst_qextTrackable.moc>
