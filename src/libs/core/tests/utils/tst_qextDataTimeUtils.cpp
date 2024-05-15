#include <QtTest>
#include <qextDateTimeUtils.h>

#include <QElapsedTimer>
#include <QDateTime>
#include <QAtomicPointer>
#include <limits>

class QExtDateTimeUtilsTest: public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void sleep1msTest();
    void sleep2msTest();
    void sleep5msTest();
    void sleep10msTest();
    void sleep20msTest();
    void sleep500msTest();
};

void QExtDateTimeUtilsTest::sleep1msTest()
{
#ifndef Q_OS_WIN
    QElapsedTimer timer;
    timer.start();
    QExtDateTimeUtils::mSleep(1);
    qint64 elapse = timer.elapsed();
    QVERIFY2(qAbs(timer.elapsed() - 1) <= 1, QString::number(elapse).toLatin1().data());
#endif
}

void QExtDateTimeUtilsTest::sleep2msTest()
{
#ifndef Q_OS_WIN
    QElapsedTimer timer;
    timer.start();
    QExtDateTimeUtils::mSleep(2);
    qint64 elapse = timer.elapsed();
    QVERIFY2(qAbs(timer.elapsed() - 2) <= 1, QString::number(elapse).toLatin1().data());
#endif
}

void QExtDateTimeUtilsTest::sleep5msTest()
{
#ifndef Q_OS_WIN
    QElapsedTimer timer;
    timer.start();
    QExtDateTimeUtils::mSleep(5);
    qint64 elapse = timer.elapsed();
    QVERIFY2(qAbs(timer.elapsed() - 5) <= 1, QString::number(elapse).toLatin1().data());
#endif
}

void QExtDateTimeUtilsTest::sleep10msTest()
{
#ifndef Q_OS_WIN
    QElapsedTimer timer;
    timer.start();
    QExtDateTimeUtils::mSleep(10);
    qint64 elapse = timer.elapsed();
    QVERIFY2(qAbs(elapse - 10) <= 2, QString::number(elapse).toLatin1().data());
#endif
}

void QExtDateTimeUtilsTest::sleep20msTest()
{
#ifndef Q_OS_WIN
    QElapsedTimer timer;
    timer.start();
    QExtDateTimeUtils::mSleep(20);
    qint64 elapse = timer.elapsed();
    QVERIFY2(qAbs(elapse - 20) <= 2, QString::number(elapse).toLatin1().data());
#endif
}

void QExtDateTimeUtilsTest::sleep500msTest()
{
#ifndef Q_OS_WIN
    QElapsedTimer timer;
    timer.start();
    QExtDateTimeUtils::mSleep(500);
    qint64 elapse = timer.elapsed();
    QVERIFY2(qAbs(elapse - 500) <= 1, QString::number(elapse).toLatin1().data());
#endif
}

QTEST_APPLESS_MAIN(QExtDateTimeUtilsTest)

#include <tst_qextDataTimeUtils.moc>
