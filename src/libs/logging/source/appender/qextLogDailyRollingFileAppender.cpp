/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025~Present ChengXueWen. Contact: 1398831004@qq.com.
** Copyright (C) 2007 - 2020 Log4Qt contributors
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#include <qextLogDailyRollingFileAppender.h>
#include <qextLoggingEvent.h>
#include <qextLogDatetime.h>
#include <qextLogLayout.h>

#include <QMetaEnum>
#include <QFile>

QExtLogDailyRollingFileAppender::QExtLogDailyRollingFileAppender(QObject *parent) :
    QExtLogFileAppender(parent),
    mDatePattern(),
    mFrequency(DAILY_ROLLOVER)
{
    setDatePattern(DAILY_ROLLOVER);
}


QExtLogDailyRollingFileAppender::QExtLogDailyRollingFileAppender(const QExtLogLayoutSharedPtr &layout,
        const QString &fileName,
        const QString &datePattern,
        QObject *parent) :
    QExtLogFileAppender(layout, fileName, parent),
    mDatePattern(),
    mFrequency(DAILY_ROLLOVER)
{
    setDatePattern(datePattern);
}

void QExtLogDailyRollingFileAppender::setDatePattern(DatePattern datePattern)
{
    switch (datePattern)
    {
    case MINUTELY_ROLLOVER:
        setDatePattern(QStringLiteral("'.'yyyy-MM-dd-hh-mm"));
        break;
    case HOURLY_ROLLOVER:
        setDatePattern(QStringLiteral("'.'yyyy-MM-dd-hh"));
        break;
    case HALFDAILY_ROLLOVER:
        setDatePattern(QStringLiteral("'.'yyyy-MM-dd-a"));
        break;
    case DAILY_ROLLOVER:
        setDatePattern(QStringLiteral("'.'yyyy-MM-dd"));
        break;
    case WEEKLY_ROLLOVER:
        setDatePattern(QStringLiteral("'.'yyyy-ww"));
        break;
    case MONTHLY_ROLLOVER:
        setDatePattern(QStringLiteral("'.'yyyy-MM"));
        break;
    default:
        Q_ASSERT_X(false, "QExtLogDailyRollingFileAppender::setDatePattern()", "Invalid datePattern constant");
        setDatePattern(DAILY_ROLLOVER);
    };
}


void QExtLogDailyRollingFileAppender::activateOptions()
{
    QMutexLocker locker(&mObjectGuard);

    computeFrequency();
    if (!mActiveDatePattern.isEmpty())
    {
        computeRollOvetime();
        QExtLogFileAppender::activateOptions();
    }
}


void QExtLogDailyRollingFileAppender::append(const QExtLoggingEvent &event)
{
    if (QDateTime::currentDateTime() > mRollOvetime)
        rollOver();
    QExtLogFileAppender::append(event);
}


bool QExtLogDailyRollingFileAppender::checkEntryConditions() const
{
    if (mActiveDatePattern.isEmpty())
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of appender '%1' without having a valid date pattern set"),
                                         QExtLogError::Error_AppenderUseInvalidPattern);
        e << name();
        logger()->error(e);
        return false;
    }

    return QExtLogFileAppender::checkEntryConditions();
}

void QExtLogDailyRollingFileAppender::computeFrequency()
{
    const QExtLogDateTime start_time(QDate(1999, 1, 1), QTime(0, 0));
    const QString start_string = start_time.toString(mDatePattern);
    mActiveDatePattern.clear();

    if (start_string != static_cast<QExtLogDateTime>(start_time.addSecs(60)).toString(mDatePattern))
        mFrequency = MINUTELY_ROLLOVER;
    else if (start_string != static_cast<QExtLogDateTime>(start_time.addSecs(60 * 60)).toString(mDatePattern))
        mFrequency = HOURLY_ROLLOVER;
    else if (start_string != static_cast<QExtLogDateTime>(start_time.addSecs(60 * 60 * 12)).toString(mDatePattern))
        mFrequency = HALFDAILY_ROLLOVER;
    else if (start_string != static_cast<QExtLogDateTime>(start_time.addDays(1)).toString(mDatePattern))
        mFrequency = DAILY_ROLLOVER;
    else if (start_string != static_cast<QExtLogDateTime>(start_time.addDays(7)).toString(mDatePattern))
        mFrequency = WEEKLY_ROLLOVER;
    else if (start_string != static_cast<QExtLogDateTime>(start_time.addMonths(1)).toString(mDatePattern))
        mFrequency = MONTHLY_ROLLOVER;
    else
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("The pattern '%1' does not specify a frequency for appender '%2'"),
                                         QExtLogError::Error_AppenderInvalidPattern);
        e << mDatePattern << name();
        logger()->error(e);
        return;
    }

    mActiveDatePattern = mDatePattern;
    logger()->trace(QStringLiteral("Frequency set to %2 using date pattern %1"),
                    mActiveDatePattern,
                    frequencyToString());
}


void QExtLogDailyRollingFileAppender::computeRollOvetime()
{
    Q_ASSERT_X(!mActiveDatePattern.isEmpty(), "QExtLogDailyRollingFileAppender::computeRollOvetime()", "No active date pattern");

    QDateTime now = QDateTime::currentDateTime();
    QDate now_date = now.date();
    QTime now_time = now.time();
    QDateTime start;

    switch (mFrequency)
    {
    case MINUTELY_ROLLOVER:
    {
        start = QDateTime(now_date,
                          QTime(now_time.hour(),
                                now_time.minute(),
                                0, 0));
        mRollOvetime = start.addSecs(60);
    }
    break;
    case HOURLY_ROLLOVER:
    {
        start = QDateTime(now_date,
                          QTime(now_time.hour(),
                                0, 0, 0));
        mRollOvetime = start.addSecs(60 * 60);
    }
    break;
    case HALFDAILY_ROLLOVER:
    {
        int hour = now_time.hour();
        if (hour >=  12)
            hour = 12;
        else
            hour = 0;
        start = QDateTime(now_date,
                          QTime(hour, 0, 0, 0));
        mRollOvetime = start.addSecs(60 * 60 * 12);
    }
    break;
    case DAILY_ROLLOVER:
    {
        start = QDateTime(now_date,
                          QTime(0, 0, 0, 0));
        mRollOvetime = start.addDays(1);
    }
    break;
    case WEEKLY_ROLLOVER:
    {
        // QT numbers the week days 1..7. The week starts on Monday.
        // Change it to being numbered 0..6, starting with Sunday.
        int day = now_date.dayOfWeek();
        if (day == Qt::Sunday)
            day = 0;
        start = QDateTime(now_date,
                          QTime(0, 0, 0, 0)).addDays(-1 * day);
        mRollOvetime = start.addDays(7);
    }
    break;
    case MONTHLY_ROLLOVER:
    {
        start = QDateTime(QDate(now_date.year(),
                                now_date.month(),
                                1),
                          QTime(0, 0, 0, 0));
        mRollOvetime = start.addMonths(1);
    }
    break;
    default:
        Q_ASSERT_X(false, "QExtLogDailyRollingFileAppender::computeInterval()", "Invalid datePattern constant");
        mRollOvetime = QDateTime::fromSecsSinceEpoch(0);
    }

    mRollOverSuffix = static_cast<QExtLogDateTime>(start).toString(mActiveDatePattern);
    Q_ASSERT_X(static_cast<QExtLogDateTime>(now).toString(mActiveDatePattern) == mRollOverSuffix,
               "QExtLogDailyRollingFileAppender::computeRollOvetime()", "File name changes within interval");
    Q_ASSERT_X(mRollOverSuffix != static_cast<QExtLogDateTime>(mRollOvetime).toString(mActiveDatePattern),
               "QExtLogDailyRollingFileAppender::computeRollOvetime()", "File name does not change with rollover");

    logger()->trace(QStringLiteral("Computing roll over time from %1: The interval start time is %2. The roll over time is %3"),
                    now.toString(),
                    start.toString(),
                    mRollOvetime.toString());
}

QString QExtLogDailyRollingFileAppender::frequencyToString() const
{
    QMetaEnum meta_enum = metaObject()->enumerator(metaObject()->indexOfEnumerator("DatePattern"));
    return QLatin1String(meta_enum.valueToKey(mFrequency));
}

void QExtLogDailyRollingFileAppender::rollOver()
{
    Q_ASSERT_X(!mActiveDatePattern.isEmpty(), "QExtLogDailyRollingFileAppender::rollOver()", "No active date pattern");

    QString roll_over_suffix = mRollOverSuffix;
    computeRollOvetime();
    if (roll_over_suffix == mRollOverSuffix)
        return;

    closeFile();

    QString target_file_name = file() + roll_over_suffix;
    QFile f(target_file_name);
    if (f.exists() && !removeFile(f))
        return;
    f.setFileName(file());
    if (!renameFile(f, target_file_name))
        return;
    openFile();
}

// #include "moc_dailyrollingfileappender.cpp"
