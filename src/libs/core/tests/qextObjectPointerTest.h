#ifndef QEXTOBJECTPOINTERTEST_H
#define QEXTOBJECTPOINTERTEST_H

#include <qextGlobal.h>
#include <qextObjectPointer.h>

#include <iostream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextObjectPointerTest
{

    TEST_GROUP(qextObjectPointerTest){};

    TEST(qextObjectPointerTest, constructors)
    {
        QEXTObject *obj = new QEXTObject;
        QEXTObjectPointer< QEXTObject > p1;
        QEXTObjectPointer< QEXTObject > p2(obj);
        QEXTObjectPointer< QEXTObject > p3(p2);
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(0));
        CHECK_EQUAL(p2, QEXTObjectPointer< QEXTObject >(obj));
        CHECK_EQUAL(p3, QEXTObjectPointer< QEXTObject >(obj));
        delete obj;
    }

    TEST(qextObjectPointerTest, destructor)
    {
        // Make two QEXTObjectPointer's to the same object
        QEXTObject * const object = new QEXTObject;
        QEXTObjectPointer< QEXTObject > p1 = object;
        QEXTObjectPointer< QEXTObject > p2 = object;
        // Check that they point to the correct object
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(object));
        CHECK_EQUAL(p2, QEXTObjectPointer< QEXTObject >(object));
        CHECK_EQUAL(p1, p2);
        // Destroy the guarded object
        delete object;
        // Check that both pointers were zeroed
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(0));
        CHECK_EQUAL(p2, QEXTObjectPointer< QEXTObject >(0));
        CHECK_EQUAL(p1, p2);
    }

    TEST(qextObjectPointerTest, assignment_operators)
    {
        QEXTObjectPointer< QEXTObject > p1;
        QEXTObjectPointer< QEXTObject > p2;

        QEXTObject *obj = new QEXTObject;
        // Test assignment with a QEXTObject-derived object pointer
        p1 = obj;
        p2 = p1;
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(obj));
        CHECK_EQUAL(p2, QEXTObjectPointer< QEXTObject >(obj));
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(p2));

        // Test assignment with a null pointer
        p1 = 0;
        p2 = p1;
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(0));
        CHECK_EQUAL(p2, QEXTObjectPointer< QEXTObject >(0));
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(p2));

        // Test assignment with a real QEXTObject pointer
        QEXTObject * const object = new QEXTObject;

        p1 = object;
        p2 = p1;
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(object));
        CHECK_EQUAL(p2, QEXTObjectPointer< QEXTObject >(object));
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(p2));

        // Test assignment with the same pointer that's already guarded
        p1 = object;
        p2 = p1;
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(object));
        CHECK_EQUAL(p2, QEXTObjectPointer< QEXTObject >(object));
        CHECK_EQUAL(p1, QEXTObjectPointer< QEXTObject >(p2));

        // Cleanup
        delete obj;
        delete object;
    }

    TEST(qextObjectPointerTest, equality_operators)
    {
        QEXTObjectPointer< QEXTObject > p1;
        QEXTObjectPointer< QEXTObject > p2;

        CHECK(p1 == p2);

        QEXTObject * const object = 0;

        p1 = object;
        CHECK(p1 == p2);
        CHECK(p1 == object);
        p2 = object;
        CHECK(p2 == p1);
        CHECK(p2 == object);

        QEXTObject *obj = new QEXTObject;
        p1 = obj;
        CHECK(p1 != p2);
        p2 = p1;
        CHECK(p1 == p2);

        // compare to zero
        p1 = 0;
        CHECK(p1 == 0);
        CHECK(0 == p1);
        CHECK(p2 != 0);
        CHECK(0 != p2);
        CHECK(p1 == object);
        CHECK(object == p1);
        CHECK(p2 != object);
        CHECK(object != p2);

        delete obj;
    }

    TEST(qextObjectPointerTest, swap)
    {
        QEXTObjectPointer< QEXTObject > c1, c2;
        {
            QEXTObject o;
            c1 = &o;
            CHECK(c2.isNull());
            CHECK_EQUAL(c1.data(), &o);
            c1.swap(c2);
            CHECK(c1.isNull());
            CHECK_EQUAL(c2.data(), &o);
        }
        CHECK(c1.isNull());
        CHECK(c2.isNull());
    }

    TEST(qextObjectPointerTest, isNull)
    {
        QEXTObjectPointer< QEXTObject > p1;
        CHECK(p1.isNull());
        QEXTObject *obj = new QEXTObject;
        p1 = obj;
        CHECK(!p1.isNull());
        p1 = 0;
        CHECK(p1.isNull());
        delete obj;
    }

    class QEXTTstObjectPointer : public QEXTObject
    {
    public:
        QEXTTstObjectPointer() {}

        inline QEXTTstObjectPointer *me() const
        { return const_cast<QEXTTstObjectPointer *>(this); }
    };

    TEST(qextObjectPointerTest, dereference_operators)
    {
        QEXTTstObjectPointer * const obj = new QEXTTstObjectPointer;
        QEXTObjectPointer< QEXTTstObjectPointer > p1 = obj;
        QEXTObjectPointer< QEXTTstObjectPointer > p2;

        // operator->() -- only makes sense if not null
        QEXTObject * const object = p1->me();
        CHECK_EQUAL(object, obj);

        // operator*() -- only makes sense if not null
        QEXTObject &ref = *p1;
        CHECK_EQUAL(&ref, obj);

        // operator T*()
        CHECK_EQUAL(static_cast< QEXTObject * >(p1), obj);
        CHECK_EQUAL(static_cast< QEXTObject * >(p2), static_cast< QEXTObject * >(0));

        // data()
        CHECK_EQUAL(p1.data(), obj);
        CHECK_EQUAL(p2.data(), static_cast< QEXTObject * >(0));
        delete obj;
    }

//    TEST(qextObjectPointerTest, disconnect)
//    {
//        // Verify that pointer remains guarded when all signals are disconencted.
//        QEXTObjectPointer< QEXTObject > p1 = new QEXTObject;
//        CHECK(!p1.isNull());
//        p1->disconnect();
//        CHECK(!p1.isNull());
//        delete static_cast< QEXTObject * >(p1);
//        CHECK(p1.isNull());
//    }

    class ChildObject : public QEXTObject
    {
        QEXTObjectPointer< QEXTObject > guardedPointer;

    public:
        ChildObject(QEXTObject *parent) : guardedPointer(parent) {}
        ~ChildObject();
    };

    ChildObject::~ChildObject()
    {
        CHECK_EQUAL(static_cast< QEXTObject * >(guardedPointer), static_cast< QEXTObject * >(0));
        CHECK_EQUAL(qextObjectCast< QEXTObject * >(guardedPointer), static_cast< QEXTObject * >(0));
    }


    class DerivedChild;

    class DerivedParent : public QEXTObject
    {
        //        Q_OBJECT
        DerivedChild *derivedChild;

    public:
        DerivedParent();
        ~DerivedParent();
    };

    class DerivedChild : public QEXTObject
    {
        //        Q_OBJECT

        DerivedParent *parentPointer;
        QEXTObjectPointer< DerivedParent > guardedParentPointer;

    public:
        DerivedChild(DerivedParent *parent) : parentPointer(parent), guardedParentPointer(parent) {}
        ~DerivedChild();
    };

    DerivedParent::DerivedParent()
    {
        derivedChild = new DerivedChild(this);
    }

    DerivedParent::~DerivedParent()
    {
        delete derivedChild;
    }

    DerivedChild::~DerivedChild()
    {
        CHECK_EQUAL(static_cast< DerivedParent * >(guardedParentPointer), parentPointer);
        CHECK_EQUAL(qextObjectCast< DerivedParent * >(guardedParentPointer), parentPointer);
    }

    TEST(qextObjectPointerTest, castDuringDestruction)
    {
        {
            QEXTObject *parentObject = new QEXTObject;
            (void)new ChildObject(parentObject);
            delete parentObject;
        }


        {
            delete new DerivedParent;
        }
    }

//    class TestRunnable : public QEXTObject, public QEXTRunnable
//    {
//        void run()
//        {
//            QEXTObjectPointer< QEXTObject > obj1 = new QEXTObject;
//            QEXTObjectPointer< QEXTObject > obj2 = new QEXTObject;
//            obj1->moveToThread(thread()); // this is the owner thread
//            obj1->deleteLater();          // the delete will happen in the owner thread
//            obj2->moveToThread(thread()); // this is the owner thread
//            obj2->deleteLater();          // the delete will happen in the owner thread
//        }
//    };

//    TEST(qextObjectPointerTest, threadSafety)
//    {

//        QEXTThread owner;
//        owner.start();

//        QEXTThreadPool pool;
//        for (int i = 0; i < 300; i++)
//        {
//            QEXTObjectPointer< TestRunnable > task = new TestRunnable;
//            task->setAutoDelete(true);
//            task->moveToThread(&owner);
//            pool.start(task);
//        }
//        pool.waitForDone();

//        owner.quit();
//        owner.wait();
//    }

    TEST(qextObjectPointerTest, constObjectPointer)
    {
        // Check that const QObjectPointers work. It's a bit weird to mark a pointer
        // const if its value can change, but the shallow-const principle in C/C++
        // allows this, and people use it, so document it with a test.
        //
        // It's unlikely that this test will fail in and out of itself, but it
        // presents the use-case to static and dynamic checkers that can raise
        // a warning (hopefully) should this become an issue.
        QEXTObject *o = new QEXTObject();
        const QEXTObjectPointer< QEXTObject > p = o;
        delete o;
        CHECK(!p);
    }

} // namespace qextObjectPointerTest

#endif // QEXTOBJECTPOINTERTEST_H
