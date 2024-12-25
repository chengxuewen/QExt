#include <qextDateTimeUtils.h>

#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QProcess>
#include <QTime>

#if QEXT_CC_STD_11
#   include <chrono>
#endif

void QExtDateTimeUtils::loopWait(const int &msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

qint64 QExtDateTimeUtils::secsTimeSinceEpoch()
{
#if QEXT_CC_STD_11
    const auto now = std::chrono::high_resolution_clock::now();
    return (qint64)std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
#else
    return QDateTime::currentSecsSinceEpoch();
#endif
}

qint64 QExtDateTimeUtils::msecsTimeSinceEpoch()
{
#if QEXT_CC_STD_11
    const auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
#else
    return QDateTime::currentMSecsSinceEpoch();
#endif
}

qint64 QExtDateTimeUtils::usecsTimeSinceEpoch()
{
#if QEXT_CC_STD_11
    const auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
#else
    return QDateTime::currentMSecsSinceEpoch() * 1000;
#endif
}

qint64 QExtDateTimeUtils::nsecsTimeSinceEpoch()
{
#if QEXT_CC_STD_11
    const auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
#else
    return QDateTime::currentMSecsSinceEpoch() * 1000000;
#endif
}

QString QExtDateTimeUtils::secsTimeSinceEpochString(qint64 secs)
{
    secs = secs > 0 ? secs : secsTimeSinceEpoch();
#if QEXT_CC_STD_11
    std::chrono::seconds seconds(secs);
    std::chrono::system_clock::time_point timePoint(seconds);
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm *timeInfo = std::localtime(&time);
    char formatBuffer[64] = {0};
    std::strftime(formatBuffer, sizeof(formatBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    return QString(formatBuffer);
#else
    return QDateTime::fromSecsSinceEpoch(secs).toString("yyyy-MM-dd hh:mm:ss");
#endif
}

QString QExtDateTimeUtils::msecsTimeSinceEpochString(qint64 msecs)
{
    msecs = msecs > 0 ? msecs : msecsTimeSinceEpoch();
#if QEXT_CC_STD_11
    std::chrono::milliseconds milliseconds(msecs);
    std::chrono::system_clock::time_point timePoint(milliseconds);
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm *timeInfo = std::localtime(&time);
    char formatBuffer[64] = {0};
    std::strftime(formatBuffer, sizeof(formatBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);
    auto remainderMsecs = milliseconds % std::chrono::seconds(1);
    auto msecsStr = std::to_string(remainderMsecs.count() / 1000);
    auto msecsStrLen = msecsStr.length();
    if (msecsStrLen < 3)
    {
        msecsStr = std::string(3 - msecsStrLen, '0') + msecsStr;
    }
    return QString(formatBuffer) + "." + msecsStr.c_str();
#else
    return QDateTime::fromMSecsSinceEpoch(msecs).toString("yyyy-MM-dd hh:mm:ss.zzz");
#endif
}
