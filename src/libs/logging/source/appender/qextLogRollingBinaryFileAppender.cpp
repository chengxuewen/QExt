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

#include <qextLogRollingBinaryFileAppender.h>
#include <qextLogDatetime.h>
#include <qextLogLayout.h>

#include <QMetaEnum>
#include <QFile>

QExtLogRollingBinaryFileAppender::QExtLogRollingBinaryFileAppender(QObject *parent)
    : QExtLogBinaryFileAppender(parent)
    , mMaxBackupIndex(1)
    , mMaximumFileSize(10 * 1024 * 1024)
    , mFrequency(DAILY_ROLLOVER)
{
    setDatePattern(DAILY_ROLLOVER);
}

void QExtLogRollingBinaryFileAppender::activateOptions()
{
    QMutexLocker locker(&mObjectGuard);

    computeFrequency();
    if (!mActiveDatePattern.isEmpty())
        computeRollOvetime();

    QExtLogBinaryFileAppender::activateOptions();
}

void QExtLogRollingBinaryFileAppender::computeFrequency()
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
    logger()->trace(QStringLiteral("Frequency set to %2 using date pattern %1"), mActiveDatePattern, frequencyToString());
}

void QExtLogRollingBinaryFileAppender::append(const QExtLoggingEvent &event)
{
    if (checkFotimeRollOver())
        rollOvetime();

    QExtLogBinaryFileAppender::append(event);

    if (checkForSizeRollOver())
        rollOverSize();
}

bool QExtLogRollingBinaryFileAppender::checkFotimeRollOver() const
{
    return QDateTime::currentDateTime() > mRollOvetime;
}

bool QExtLogRollingBinaryFileAppender::checkForSizeRollOver() const
{
    return writer()->device()->size() > mMaximumFileSize;
}

void QExtLogRollingBinaryFileAppender::rollOverSize()
{
    logger()->debug(QStringLiteral("Rolling over with maxBackupIndex = %1"), mMaxBackupIndex);

    // close current file first
    closeFile();

    // remove highest file first, eg. file.log.10
    QFile f;
    f.setFileName(file() + QLatin1Char('.') + QString::number(mMaxBackupIndex));
    if (f.exists() && !removeFile(f))
        return;

    // now move all lower files one step up, e.g. file.log.9 --> file.log.10, file.log.8 --> file.log.9, ..., file.log.1 --> file.log.2
    QString target_file_name;
    int i;
    for (i = mMaxBackupIndex - 1; i >= 1; i--)
    {
        f.setFileName(file() + QLatin1Char('.') + QString::number(i));
        if (f.exists())
        {
            target_file_name = file() + QLatin1Char('.') + QString::number(i + 1);
            if (!renameFile(f, target_file_name))
                return;
        }
    }

    // Now renmae the current file from file.log --> file.log.1
    f.setFileName(file());
    target_file_name = file() + QStringLiteral(".1");
    if (!renameFile(f, target_file_name))
        return;

    // open a new file
    openFile();
}

void QExtLogRollingBinaryFileAppender::rollOvetime()
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

void QExtLogRollingBinaryFileAppender::setDatePattern(DatePattern datePattern)
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
        Q_ASSERT_X(false, "QExtLogBinaryFileAppender::setDatePattern()", "Invalid datePattern constant");
        setDatePattern(DAILY_ROLLOVER);
        break;
    };
}

void QExtLogRollingBinaryFileAppender::computeRollOvetime()
{
    Q_ASSERT_X(!mActiveDatePattern.isEmpty(), "QExtLogBinaryFileAppender::computeRollOvetime()", "No active date pattern");

    QDateTime now = QDateTime::currentDateTime();
    QDate now_date = now.date();
    QTime now_time = now.time();
    QDateTime start;

    switch (mFrequency)
    {
    case MINUTELY_ROLLOVER:
        start = QDateTime(now_date, QTime(now_time.hour(), now_time.minute(), 0, 0));
        mRollOvetime = start.addSecs(60);
        break;
    case HOURLY_ROLLOVER:
        start = QDateTime(now_date, QTime(now_time.hour(), 0, 0, 0));
        mRollOvetime = start.addSecs(60 * 60);
        break;
    case HALFDAILY_ROLLOVER:
    {
        int hour = now_time.hour();
        if (hour >=  12)
            hour = 12;
        else
            hour = 0;
        start = QDateTime(now_date, QTime(hour, 0, 0, 0));
        mRollOvetime = start.addSecs(60 * 60 * 12);
    }
    break;
    case DAILY_ROLLOVER:
        start = QDateTime(now_date, QTime(0, 0, 0, 0));
        mRollOvetime = start.addDays(1);
        break;
    case WEEKLY_ROLLOVER:
    {
        // QT numbers the week days 1..7. The week starts on Monday.
        // Change it to being numbered 0..6, starting with Sunday.
        int day = now_date.dayOfWeek();
        if (day == Qt::Sunday)
            day = 0;
        start = QDateTime(now_date, QTime(0, 0, 0, 0)).addDays(-1 * day);
        mRollOvetime = start.addDays(7);
    }
    break;
    case MONTHLY_ROLLOVER:
        start = QDateTime(QDate(now_date.year(), now_date.month(), 1), QTime(0, 0, 0, 0));
        mRollOvetime = start.addMonths(1);
        break;
    default:
        Q_ASSERT_X(false, "QExtLogBinaryFileAppender::computeInterval()", "Invalid datePattern constant");
        mRollOvetime = QDateTime::fromSecsSinceEpoch(0);
        break;
    }

    mRollOverSuffix = static_cast<QExtLogDateTime>(start).toString(mActiveDatePattern);
    Q_ASSERT_X(static_cast<QExtLogDateTime>(now).toString(mActiveDatePattern) == mRollOverSuffix,
               "QExtLogBinaryFileAppender::computeRollOvetime()", "File name changes within interval");
    Q_ASSERT_X(mRollOverSuffix != static_cast<QExtLogDateTime>(mRollOvetime).toString(mActiveDatePattern),
               "QExtLogBinaryFileAppender::computeRollOvetime()", "File name does not change with rollover");

    logger()->trace(QStringLiteral("Computing roll over time from %1: The interval start time is %2. The roll over time is %3"),
                    now.toString(),
                    start.toString(),
                    mRollOvetime.toString());
}

QString QExtLogRollingBinaryFileAppender::frequencyToString() const
{
    QMetaEnum meta_enum = metaObject()->enumerator(metaObject()->indexOfEnumerator("DatePattern"));
    return QLatin1String(meta_enum.valueToKey(mFrequency));
}

// #include "moc_rollingbinaryfileappender.cpp"
