#include <QtTest>
#include <qextdatetimeutils.h>

#include <QElapsedTimer>
#include <QDateTime>

class QEXTDateTimeUtilsQTest: public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void sleep1msTest();
    void sleep2msTest();
    void sleep5msTest();
    void sleep10msTest();
    void sleep20msTest();
};

void QEXTDateTimeUtilsQTest::sleep1msTest()
{
    QElapsedTimer timer;
    timer.start();
    QEXTDateTimeUtils::mSleep(1);
    QVERIFY(qAbs(timer.elapsed() - 1) <= 1);
}

void QEXTDateTimeUtilsQTest::sleep2msTest()
{
    QElapsedTimer timer;
    timer.start();
    QEXTDateTimeUtils::mSleep(2);
    QVERIFY(qAbs(timer.elapsed() - 2) <= 1);
}

void QEXTDateTimeUtilsQTest::sleep5msTest()
{
    QElapsedTimer timer;
    timer.start();
    QEXTDateTimeUtils::mSleep(5);
    QVERIFY(qAbs(timer.elapsed() - 5) <= 1);
}

void QEXTDateTimeUtilsQTest::sleep10msTest()
{
    QElapsedTimer timer;
    timer.start();
    QEXTDateTimeUtils::mSleep(10);
    QVERIFY(qAbs(timer.elapsed() - 10) <= 1);
}

void QEXTDateTimeUtilsQTest::sleep20msTest()
{
    QElapsedTimer timer;
    timer.start();
    QEXTDateTimeUtils::mSleep(20);
    QVERIFY(qAbs(timer.elapsed() - 20) <= 1);
}

QTEST_APPLESS_MAIN(QEXTDateTimeUtilsQTest)

#include "qextdatatimeutilsqtest.moc"
