#include <qextConcurrent.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>
#include <QThread>
#include <QSemaphore>
#include <QThreadPool>

class QExtConcurrentTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void constructor();

    void multithread();
};


void QExtConcurrentTest::constructor()
{
    QExtConcurrent<int> concurrentInt(0);
    QCOMPARE(0, concurrentInt);
    QCOMPARE(0, concurrentInt.get());

    QExtConcurrentInt concurrentInt2(0);
    QCOMPARE(0, concurrentInt2);
    QCOMPARE(0, concurrentInt2.get());
    QCOMPARE(concurrentInt, concurrentInt2);
    QCOMPARE(concurrentInt.get(), concurrentInt2.get());

    const double dblMin = std::numeric_limits<double>::min();
    QExtConcurrentDouble concurrentDoubleMin(dblMin);
    QCOMPARE(dblMin, concurrentDoubleMin);
    QCOMPARE(dblMin, concurrentDoubleMin.get());

    const double dblMax = std::numeric_limits<double>::max();
    QExtConcurrentDouble concurrentDoubleMax(dblMax);
    QCOMPARE(dblMax, concurrentDoubleMax);
    QCOMPARE(dblMax, concurrentDoubleMax.get());
}

struct MultiThreadData
{
    MultiThreadData() : concurrentInt(0), concurrentDouble(0), concurrentInt64(0) {}
    QExtConcurrentInt concurrentInt;
    QExtConcurrentDouble concurrentDouble;
    QExtConcurrent<qint64> concurrentInt64;
};
class MultiThreadRunnable : public QRunnable
{
public:
    MultiThreadRunnable(bool sub, int loopNum, QSemaphore &semaphore, MultiThreadData &multiThreadData)
        : m_sub(sub),
          m_loopNum(loopNum),
          m_semaphore(semaphore),
          m_multiThreadData(multiThreadData)
    {
    }
    ~MultiThreadRunnable() {}

protected:
    void run()
    {
        m_semaphore.acquire();
        for (int i = 0; i < m_loopNum; ++i)
        {
            m_multiThreadData.concurrentInt64.fetch_set(m_sub ? int64_sub_func : int64_add_func);
            if (m_sub)
            {
                m_multiThreadData.concurrentInt.fetch_sub(1);
                m_multiThreadData.concurrentDouble.fetch_sub(0.001);
            }
            else
            {
                m_multiThreadData.concurrentInt.fetch_add(1);
                m_multiThreadData.concurrentDouble.fetch_add(0.001);
            }
        }
    }

    static qint64 int64_add_func(const qint64 &i) { return i + 1; }
    static qint64 int64_sub_func(const qint64 &i) { return i - 1; }

private:
    const bool m_sub;
    const int m_loopNum;
    QSemaphore &m_semaphore;
    MultiThreadData &m_multiThreadData;
};
void QExtConcurrentTest::multithread()
{
#define NUMTHREADS 10
    QSemaphore semaphore(NUMTHREADS);
    semaphore.acquire(NUMTHREADS);
    MultiThreadData multiThreadData;
    const int incrementsPerThread = 100000;
    QThreadPool threadPool;
    threadPool.setMaxThreadCount(NUMTHREADS);
    for (int i = 0; i < NUMTHREADS; ++i)
    {
        threadPool.start(new MultiThreadRunnable(0 == i % 2, incrementsPerThread, semaphore, multiThreadData));
    }
    semaphore.release(NUMTHREADS);
    threadPool.waitForDone();
    QCOMPARE(0, multiThreadData.concurrentInt.get());
    QCOMPARE(0, multiThreadData.concurrentInt64.get());
    QCOMPARE(0, int(multiThreadData.concurrentDouble.get() * 1000));
}

QTEST_APPLESS_MAIN(QExtConcurrentTest)

#include <tst_qextConcurrent.moc>
