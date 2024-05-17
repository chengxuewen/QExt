#include <qextAtomic.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>

class QExtAtomicTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void constructor();
    void copy_constructor();
    void testAndSet();
    void fetchAndStore();

    void limit();
};


void QExtAtomicTest::constructor()
{
    double value = 1;
    for (int i = 0; i < 1000; ++i)
    {
        double dbl = reinterpret_cast<qlonglong>(this) / value;
        QExtAtomicDouble atomic = dbl;
        QCOMPARE(atomic.loadRelaxed(), dbl);

        atomic.storeRelease(value);
        QCOMPARE(atomic.loadAcquire(), value);

        value = value * 0.5;
    }
}

void QExtAtomicTest::copy_constructor()
{
    double one = reinterpret_cast<qlonglong>(this) / 3.3;
    QExtAtomicDouble atomic1 = one;
    QExtAtomicDouble atomic1_copy = atomic1;
    QCOMPARE(atomic1_copy.loadRelaxed(), one);
    QCOMPARE(atomic1_copy.loadRelaxed(), atomic1.loadRelaxed());

    double two = reinterpret_cast<qlonglong>(&one) / 3.3;
    QExtAtomicDouble atomic2 = two;
    QExtAtomicDouble atomic2_copy = atomic2;
    QCOMPARE(atomic2_copy.loadRelaxed(), two);
    QCOMPARE(atomic2_copy.loadRelaxed(), atomic2.loadRelaxed());

    double three = reinterpret_cast<qlonglong>(&two) / 3.3;
    QExtAtomicDouble atomic3 = three;
    QExtAtomicDouble atomic3_copy = atomic3;
    QCOMPARE(atomic3_copy.loadRelaxed(), three);
    QCOMPARE(atomic3_copy.loadRelaxed(), atomic3.loadRelaxed());
}

void QExtAtomicTest::testAndSet()
{
    double one = reinterpret_cast<qlonglong>(this) / 3.3;
    double two = reinterpret_cast<qlonglong>(&one) / 3.3;
    double three = reinterpret_cast<qlonglong>(&two) / 3.3;

    {
        QExtAtomicDouble atomic1 = one;
        QExtAtomicDouble atomic2 = two;
        QExtAtomicDouble atomic3 = three;

        QCOMPARE(atomic1.loadRelaxed(), one);
        QCOMPARE(atomic2.loadRelaxed(), two);
        QCOMPARE(atomic3.loadRelaxed(), three);

        QVERIFY(atomic1.testAndSetRelaxed(one, two));
        QVERIFY(atomic2.testAndSetRelaxed(two, three));
        QVERIFY(atomic3.testAndSetRelaxed(three, one));

        QCOMPARE(atomic1.loadRelaxed(), two);
        QCOMPARE(atomic2.loadRelaxed(), three);
        QCOMPARE(atomic3.loadRelaxed(), one);
    }

    {
        QExtAtomicDouble atomic1 = one;
        QExtAtomicDouble atomic2 = two;
        QExtAtomicDouble atomic3 = three;

        QCOMPARE(atomic1.loadRelaxed(), one);
        QCOMPARE(atomic2.loadRelaxed(), two);
        QCOMPARE(atomic3.loadRelaxed(), three);

        QVERIFY(atomic1.testAndSetAcquire(one, two));
        QVERIFY(atomic2.testAndSetAcquire(two, three));
        QVERIFY(atomic3.testAndSetAcquire(three, one));

        QCOMPARE(atomic1.loadRelaxed(), two);
        QCOMPARE(atomic2.loadRelaxed(), three);
        QCOMPARE(atomic3.loadRelaxed(), one);
    }

    {
        QExtAtomicDouble atomic1 = one;
        QExtAtomicDouble atomic2 = two;
        QExtAtomicDouble atomic3 = three;

        QCOMPARE(atomic1.loadRelaxed(), one);
        QCOMPARE(atomic2.loadRelaxed(), two);
        QCOMPARE(atomic3.loadRelaxed(), three);

        QVERIFY(atomic1.testAndSetRelease(one, two));
        QVERIFY(atomic2.testAndSetRelease(two, three));
        QVERIFY(atomic3.testAndSetRelease(three, one));

        QCOMPARE(atomic1.loadRelaxed(), two);
        QCOMPARE(atomic2.loadRelaxed(), three);
        QCOMPARE(atomic3.loadRelaxed(), one);
    }

    {
        QExtAtomicDouble atomic1 = one;
        QExtAtomicDouble atomic2 = two;
        QExtAtomicDouble atomic3 = three;

        QCOMPARE(atomic1.loadRelaxed(), one);
        QCOMPARE(atomic2.loadRelaxed(), two);
        QCOMPARE(atomic3.loadRelaxed(), three);

        QVERIFY(atomic1.testAndSetOrdered(one, two));
        QVERIFY(atomic2.testAndSetOrdered(two, three));
        QVERIFY(atomic3.testAndSetOrdered(three, one));

        QCOMPARE(atomic1.loadRelaxed(), two);
        QCOMPARE(atomic2.loadRelaxed(), three);
        QCOMPARE(atomic3.loadRelaxed(), one);
    }
}

void QExtAtomicTest::fetchAndStore()
{
    double one = reinterpret_cast<qlonglong>(this) / 3.3;
    double two = reinterpret_cast<qlonglong>(&one) / 3.3;
    double three = reinterpret_cast<qlonglong>(&two) / 3.3;

    {
        QExtAtomicDouble atomic1 = one;
        QExtAtomicDouble atomic2 = two;
        QExtAtomicDouble atomic3 = three;

        QCOMPARE(atomic1.loadRelaxed(), one);
        QCOMPARE(atomic2.loadRelaxed(), two);
        QCOMPARE(atomic3.loadRelaxed(), three);

        QCOMPARE(atomic1.fetchAndStoreRelaxed(two), one);
        QCOMPARE(atomic2.fetchAndStoreRelaxed(three), two);
        QCOMPARE(atomic3.fetchAndStoreRelaxed(one), three);

        QCOMPARE(atomic1.loadRelaxed(), two);
        QCOMPARE(atomic2.loadRelaxed(), three);
        QCOMPARE(atomic3.loadRelaxed(), one);
    }

    {
        QExtAtomicDouble atomic1 = one;
        QExtAtomicDouble atomic2 = two;
        QExtAtomicDouble atomic3 = three;

        QCOMPARE(atomic1.loadRelaxed(), one);
        QCOMPARE(atomic2.loadRelaxed(), two);
        QCOMPARE(atomic3.loadRelaxed(), three);

        QCOMPARE(atomic1.fetchAndStoreAcquire(two), one);
        QCOMPARE(atomic2.fetchAndStoreAcquire(three), two);
        QCOMPARE(atomic3.fetchAndStoreAcquire(one), three);

        QCOMPARE(atomic1.loadRelaxed(), two);
        QCOMPARE(atomic2.loadRelaxed(), three);
        QCOMPARE(atomic3.loadRelaxed(), one);
    }

    {
        QExtAtomicDouble atomic1 = one;
        QExtAtomicDouble atomic2 = two;
        QExtAtomicDouble atomic3 = three;

        QCOMPARE(atomic1.loadRelaxed(), one);
        QCOMPARE(atomic2.loadRelaxed(), two);
        QCOMPARE(atomic3.loadRelaxed(), three);

        QCOMPARE(atomic1.fetchAndStoreRelease(two), one);
        QCOMPARE(atomic2.fetchAndStoreRelease(three), two);
        QCOMPARE(atomic3.fetchAndStoreRelease(one), three);

        QCOMPARE(atomic1.loadRelaxed(), two);
        QCOMPARE(atomic2.loadRelaxed(), three);
        QCOMPARE(atomic3.loadRelaxed(), one);
    }

    {
        QExtAtomicDouble atomic1 = one;
        QExtAtomicDouble atomic2 = two;
        QExtAtomicDouble atomic3 = three;

        QCOMPARE(atomic1.loadRelaxed(), one);
        QCOMPARE(atomic2.loadRelaxed(), two);
        QCOMPARE(atomic3.loadRelaxed(), three);

        QCOMPARE(atomic1.fetchAndStoreOrdered(two), one);
        QCOMPARE(atomic2.fetchAndStoreOrdered(three), two);
        QCOMPARE(atomic3.fetchAndStoreOrdered(one), three);

        QCOMPARE(atomic1.loadRelaxed(), two);
        QCOMPARE(atomic2.loadRelaxed(), three);
        QCOMPARE(atomic3.loadRelaxed(), one);
    }
}

void QExtAtomicTest::limit()
{
    double dblMin = std::numeric_limits<double>::min();
    QExtAtomicDouble atomicMin = dblMin;
    QCOMPARE(atomicMin.loadRelaxed(), dblMin);

    double dblMax = std::numeric_limits<double>::max();
    QExtAtomicDouble atomicMax = dblMax;
    QCOMPARE(atomicMax.loadRelaxed(), dblMax);
}

QTEST_APPLESS_MAIN(QExtAtomicTest)

#include <tst_qextAtomic.moc>
