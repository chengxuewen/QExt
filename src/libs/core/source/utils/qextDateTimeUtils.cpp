#include <qextDateTimeUtils.h>

#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QProcess>
#include <QTime>

#if QEXT_CC_CPP11_OR_GREATER
#   include <ctime>
#   include <chrono>
#endif

#include <sstream>
#include <iomanip>

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
#if QEXT_CC_CPP11_OR_GREATER
    const auto now = std::chrono::system_clock::now();
    return (qint64)std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
#else
    return QDateTime::currentSecsSinceEpoch();
#endif
}

qint64 QExtDateTimeUtils::msecsTimeSinceEpoch()
{
#if QEXT_CC_CPP11_OR_GREATER
    const auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
#else
    return QDateTime::currentMSecsSinceEpoch();
#endif
}

qint64 QExtDateTimeUtils::usecsTimeSinceEpoch()
{
#if QEXT_CC_CPP11_OR_GREATER
    const auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
#else
    return QDateTime::currentMSecsSinceEpoch() * 1000;
#endif
}

qint64 QExtDateTimeUtils::nsecsTimeSinceEpoch()
{
#if QEXT_CC_CPP11_OR_GREATER
    const auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
#else
    return QDateTime::currentMSecsSinceEpoch() * 1000000;
#endif
}

QString QExtDateTimeUtils::localTimeStringFromSecsSinceEpoch(qint64 secs)
{
    secs = secs > 0 ? secs : secsTimeSinceEpoch();
#if QEXT_CC_CPP11_OR_GREATER
    std::chrono::seconds seconds(secs);
    std::chrono::system_clock::time_point timePoint(seconds);
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm *localTime = std::localtime(&time);
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return QString::fromStdString(ss.str());
#else
    return QDateTime::fromSecsSinceEpoch(secs).toString("yyyy-MM-dd hh:mm:ss");
#endif
}

QString QExtDateTimeUtils::localTimeStringFromMSecsSinceEpoch(qint64 msecs)
{
    msecs = msecs > 0 ? msecs : msecsTimeSinceEpoch();
#if QEXT_CC_CPP11_OR_GREATER
    std::chrono::milliseconds milliseconds(msecs);
    std::chrono::system_clock::time_point timePoint(milliseconds);
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm *localTime = std::localtime(&time);
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S")
       << '.' << std::setfill('0') << std::setw(3) << (milliseconds.count() % 1000);
    return QString::fromStdString(ss.str());
#else
    return QDateTime::fromMSecsSinceEpoch(msecs).toString("yyyy-MM-dd hh:mm:ss.zzz");
#endif
}
