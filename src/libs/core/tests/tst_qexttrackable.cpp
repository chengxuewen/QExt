#include <qexttrackable.h>
#include <qextmemberfunctor.h>
#include <qextslot.h>

#include <QtTest>
#include <QDebug>

class QEXTTrackAbleTest : public QObject
{
    Q_OBJECT
private slots:
    void testSimple();


public:
    static int sm_result;
    static QString sm_string;
};

int QEXTTrackAbleTest::sm_result = 0;
QString QEXTTrackAbleTest::sm_string = "";



class MYClass: public QEXTTrackable
{
public:
    void foo() {
        QEXTTrackAbleTest::sm_string = QString::number(i);
    }

    int i;
};

void QEXTTrackAbleTest::testSimple()
{
    QEXTSlot<void> slot;
    MYClass *myClass = new MYClass;
    myClass->i = 11;
    slot = qextMemberFunctor0(myClass, &MYClass::foo);
    delete myClass;
    myClass = QEXT_NULLPTR;

    QEXTSlot<void> sl;
    {
        sm_string = "";
        MYClass t;
        t.i = 10;
        sl = qextMemberFunctor0(&t, &MYClass::foo);
        sl();
        QVERIFY("10" == sm_string);
    }

    sm_string = "";
    sl();
    QVERIFY("" == sm_string);

    MYClass *myCLass = new MYClass;
    delete myCLass;
    myCLass = QEXT_NULLPTR;
}

QTEST_APPLESS_MAIN(QEXTTrackAbleTest)

#include <tst_qexttrackable.moc>
