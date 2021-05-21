#include "qextsimpleobject.h"

#include <QtTest>
#include <QDebug>

class QEXTObjectTest: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    {
        qDebug("Called before everything else.");
    }

    void simpleQEXTObjectTest()
    {
        QEXTSimpleObject *obj1 = new QEXTSimpleObject;
        obj1->setString("string");
        QCOMPARE(QString("string"), obj1->string());

        QEXTSimpleObject *obj2 = new QEXTSimpleObject(this);
        obj2->setString("string");
        QCOMPARE(QString("string"), obj2->string());

        QEXTSimpleObject obj3;
        obj3.setString("string");
        QCOMPARE(QString("string"), obj3.string());
    }

    void cleanupTestCase()
    {
        qDebug("Called after myFirstTest and mySecondTest.");
    }
};

QTEST_APPLESS_MAIN(QEXTObjectTest)

#include <tst_qextobject.moc>
