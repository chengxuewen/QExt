#include <qexttypetrait.h>

#include <QtTest>
#include <QDebug>


class QEXTTypeTraitTest : public QObject
{
    Q_OBJECT
private slots:
    void testBaseAndDerived();
};


class MClassBase
{
public:
    MClassBase() {}
};

class MClass : public MClassBase
{
public:
    MClass() {}
};


class A
{
public:
    A() {}
};

template <typename T_obj, bool I_derives_base = QEXTBaseAndDerivedTester<MClassBase, T_obj>::value>
struct MClassTrait
{
    bool data() { return true; }
};

template <typename T_obj>
struct MClassTrait<T_obj, false>
{
    bool data() { return false; }
};



void QEXTTypeTraitTest::testBaseAndDerived()
{
    bool drived = true;
    drived = QEXTBaseAndDerivedTester<MClassBase, MClass>::value;
    QVERIFY(drived);
    drived = QEXTBaseAndDerivedTester<MClassBase, MClassBase>::value;
    QVERIFY(drived);

    QVERIFY(MClassTrait<MClassBase>().data());
    QVERIFY(MClassTrait<MClass>().data());
    QVERIFY(!MClassTrait<A>().data());
}

QTEST_APPLESS_MAIN(QEXTTypeTraitTest)

#include <tst_qexttypetrait.moc>
