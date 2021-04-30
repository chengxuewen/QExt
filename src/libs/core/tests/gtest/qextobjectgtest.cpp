#include <qextsimpleobject.h>

#include <gtest/gtest.h>
#include <QObject>

TEST(QEXTObjectGTest, simpleQEXTObjectTest)
{
    QEXTSimpleObject *obj1 = new QEXTSimpleObject();
    obj1->setString("string");
    ASSERT_TRUE("string" == obj1->string());

    QObject qObject;
    QEXTSimpleObject *obj2 = new QEXTSimpleObject(&qObject);
    obj2->setString("string");
    ASSERT_TRUE("string" == obj2->string());

    QEXTSimpleObject obj3;
    obj3.setString("string");
    ASSERT_TRUE("string" == obj3.string());
}
