#include <qextdatetimeutils.h>

#include <gtest/gtest.h>

#include <QElapsedTimer>
#include <QDateTime>

TEST(QEXTDatatimeUtilsGTest, sleep1ms)
{
    QElapsedTimer timer;
    timer.start();
    QEXTDateTimeUtils::mSleep(1);
    ASSERT_TRUE(qAbs(timer.elapsed() - 1) <= 1);
}

TEST(QEXTDatatimeUtilsGTest, sleep2ms)
{
    QElapsedTimer timer;
    timer.start();
    QEXTDateTimeUtils::mSleep(2);
    ASSERT_TRUE(qAbs(timer.elapsed() - 2) <= 1);
}

TEST(QEXTDatatimeUtilsGTest, sleep5ms)
{
    QElapsedTimer timer;
    timer.start();
    QEXTDateTimeUtils::mSleep(5);
    ASSERT_TRUE(qAbs(timer.elapsed() - 5) <= 1);
}

TEST(QEXTDatatimeUtilsGTest, sleep10ms)
{
    QElapsedTimer timer;
    timer.start();
    QEXTDateTimeUtils::mSleep(10);
    ASSERT_TRUE(qAbs(timer.elapsed() - 10) <= 1);
}

TEST(QEXTDatatimeUtilsGTest, sleep20ms)
{
    QElapsedTimer timer;
    timer.start();
    QEXTDateTimeUtils::mSleep(20);
    ASSERT_TRUE(qAbs(timer.elapsed() - 20) <= 1);
}
