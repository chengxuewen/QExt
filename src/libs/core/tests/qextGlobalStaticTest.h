#ifndef QEXTGLOBALSTATICTEST_H
#define QEXTGLOBALSTATICTEST_H

#include <qextGlobal.h>
#include <qextAtomic.h>
#include <qextGlobalStatic.h>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextGlobalStaticTest
{

    TEST_GROUP(qextGlobalStaticTest)
    {
        void setup()
        {

        }

        void teardown()
        {
            // Un-init stuff
        }
    };


    QEXT_GLOBAL_STATIC_WITH_ARGS(const int, constInt, (42))
    QEXT_GLOBAL_STATIC_WITH_ARGS(volatile int, volatileInt, (-47))

    void otherFunction()
    {
        // never called
        constInt();
        volatileInt();
    }

    // do not initialize the following QEXT_GLOBAL_STATIC
    QEXT_GLOBAL_STATIC(int, checkedBeforeInitialization)
    TEST(qextGlobalStaticTest, beforeInitialization)
    {
        CHECK(!checkedBeforeInitialization.exists());
        CHECK(!checkedBeforeInitialization.isDestroyed());
    }

    struct Type
    {
        int i;
    };

    QEXT_GLOBAL_STATIC(Type, checkedAfterInitialization)
    TEST(qextGlobalStaticTest, api)
    {
        // check the API
        CHECK((Type *)checkedAfterInitialization);
        CHECK(checkedAfterInitialization());
        *checkedAfterInitialization = Type();
        *checkedAfterInitialization() = Type();

        checkedAfterInitialization()->i = 47;
        checkedAfterInitialization->i = 42;
        CHECK_EQUAL(checkedAfterInitialization()->i, 42);
        checkedAfterInitialization()->i = 47;
        CHECK_EQUAL(checkedAfterInitialization->i, 47);

        CHECK(checkedAfterInitialization.exists());
        CHECK(!checkedAfterInitialization.isDestroyed());
    }

    TEST(qextGlobalStaticTest, constVolatile)
    {
        CHECK_EQUAL(*constInt(), 42);
        CHECK_EQUAL((int)*volatileInt(), -47);
        CHECK_EQUAL(*constInt(), 42);
        CHECK_EQUAL((int)*volatileInt(), -47);
    }

    struct ThrowingType
    {
        static QEXTBasicAtomicInt constructedCount;
        static QEXTBasicAtomicInt destructedCount;
        ThrowingType()
        {
            throw 0;
        }

        ThrowingType(QEXTBasicAtomicInt &throwControl)
        {
            constructedCount.ref();
            if (throwControl.fetchAndAddRelaxed(-1) != 0)
            {
                throw 0;
            }
        }
        ~ThrowingType()
        {
            destructedCount.ref();
        }
    };

    QEXTBasicAtomicInt ThrowingType::constructedCount = QEXT_BASIC_ATOMIC_INITIALIZER(0);
    QEXTBasicAtomicInt ThrowingType::destructedCount = QEXT_BASIC_ATOMIC_INITIALIZER(0);

    QEXT_GLOBAL_STATIC(ThrowingType, throwingGS)
    TEST(qextGlobalStaticTest, exception)
    {
        bool exceptionCaught = false;
        try
        {
            throwingGS();
        }
        catch (int)
        {
            exceptionCaught = true;
        }
        CHECK(exceptionCaught);
        CHECK_EQUAL(QEXT_QGS_throwingGS::guard.load(), 0);
        CHECK(!throwingGS.exists());
        CHECK(!throwingGS.isDestroyed());
    }

    QEXTBasicAtomicInt exceptionControlVar = QEXT_BASIC_ATOMIC_INITIALIZER(1);
    QEXT_GLOBAL_STATIC_WITH_ARGS(ThrowingType, exceptionGS, (exceptionControlVar))
    TEST(qextGlobalStaticTest, catchExceptionAndRetry)
    {
        if (exceptionControlVar.load() != 1)
        {
            FAIL("This test cannot be run more than once");
        }
        ThrowingType::constructedCount.store(0);
        ThrowingType::destructedCount.store(0);

        bool exceptionCaught = false;
        try
        {
            exceptionGS();
        }
        catch (int)
        {
            exceptionCaught = true;
        }
        CHECK_EQUAL(ThrowingType::constructedCount.load(), 1);
        CHECK(exceptionCaught);

        exceptionGS();
        CHECK_EQUAL(ThrowingType::constructedCount.load(), 2);
    }

    QEXTBasicAtomicInt threadStressTestControlVar = QEXT_BASIC_ATOMIC_INITIALIZER(5);
    QEXT_GLOBAL_STATIC_WITH_ARGS(ThrowingType, threadStressTestGS, (threadStressTestControlVar))


    TEST(qextGlobalStaticTest, threadStressTest)
    {
        //TODO
//        class ThreadStressTestThread: public QThread
//        {
//        public:
////            QReadWriteLock *lock;
//            void run()
//            {
//                QReadLocker l(lock);
//                //usleep(qrand() * 200 / RAND_MAX);
//                // thundering herd
//                try
//                {
//                    threadStressTestGS();
//                }
//                catch (int)
//                {
//                }
//            }
//        };

//        ThrowingType::constructedCount.store(0);
//        ThrowingType::destructedCount.store(0);
//        int expectedConstructionCount = threadStressTestControlVar.load() + 1;
//        if (expectedConstructionCount <= 0)
//        {
//            FAIL("This test cannot be run more than once");
//        }

//        const int numThreads = 200;
//        ThreadStressTestThread threads[numThreads];
//        QReadWriteLock lock;
//        lock.lockForWrite();
//        for (int i = 0; i < numThreads; ++i)
//        {
//            threads[i].lock = &lock;
//            threads[i].start();
//        }

//        // wait for all threads
//        // release the herd
//        lock.unlock();

//        for (int i = 0; i < numThreads; ++i)
//        {
//            threads[i].wait();
//        }

//        CHECK_EQUAL(ThrowingType::constructedCount.loadAcquire(), expectedConstructionCount);
//        CHECK_EQUAL(ThrowingType::destructedCount.loadAcquire(), 0);
    }

    QEXT_GLOBAL_STATIC(int, checkedAfterDestruction)
    TEST(qextGlobalStaticTest, afterDestruction)
    {
        // this test will not produce results now
        // it will simply run some code on destruction (after the global statics have been deleted)
        // if that fails, this will cause a crash

        // static destruction is LIFO: so we must add our exit-time code before the
        // global static is used for the first time
        static struct RunAtExit
        {
            ~RunAtExit()
            {
                int *ptr = checkedAfterDestruction();
                if (ptr)
                {
                    FAIL("Global static is not null as was expected");
                }
            }
        } runAtExit;
        (void) runAtExit;

        *checkedAfterDestruction = 42;
    }

}

#endif // QEXTGLOBALSTATICTEST_H
