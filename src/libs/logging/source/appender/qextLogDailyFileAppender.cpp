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

#include <qextLogDailyFileAppender.h>
#include <qextLoggingEvent.h>
#include <qextLogLayout.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>
#include <QStringList>
#include <QtConcurrentRun>
#include <QStringBuilder>

#if (__cplusplus >= 201703L) // C++17 or later
#include <utility>
#endif

QExtLogDateRetrieverInterface::~QExtLogDateRetrieverInterface() = default;

QDate QExtLogDefaultDateRetriever::currentDate() const
{
    return QDate::currentDate();
}

static const char defaultDatePattern[] = "_yyyy_MM_dd";

QExtLogDailyFileAppender::QExtLogDailyFileAppender(QObject *parent)
    : QExtLogFileAppender(parent)
    , mDateRetriever(new QExtLogDefaultDateRetriever)
    , mDatePattern(defaultDatePattern)
    , mKeepDays(0)
{
}

QExtLogDailyFileAppender::QExtLogDailyFileAppender(const QExtLogLayoutSharedPtr &layout, const QString &fileName, const QString &datePattern, const int keepDays, QObject *parent)
    : QExtLogFileAppender(layout, fileName, parent)
    , mDateRetriever(new QExtLogDefaultDateRetriever)
    , mDatePattern(datePattern.isEmpty() ? defaultDatePattern : datePattern)
    , mKeepDays(keepDays)
{
}

QString QExtLogDailyFileAppender::datePattern() const
{
    QMutexLocker locker(&mObjectGuard);
    return mDatePattern;
}

void QExtLogDailyFileAppender::setDatePattern(const QString &datePattern)
{
    QMutexLocker locker(&mObjectGuard);
    mDatePattern = datePattern;
}

int QExtLogDailyFileAppender::keepDays() const
{
    QMutexLocker locker(&mObjectGuard);
    return mKeepDays;
}

void QExtLogDailyFileAppender::setKeepDays(const int keepDays)
{
    QMutexLocker locker(&mObjectGuard);
    mKeepDays = keepDays;
}

namespace
{

void deleteObsoleteFiles(
        QDate currentDate,
        const QString &datePattern,
        int keepDays,
        const QString &originalFilename)
{
    if (keepDays <= 0) return;
    if (originalFilename.isEmpty()) return;

    const QFileInfo fi(originalFilename);
    const QDir logDir(fi.absolutePath());
    const auto logFileNames(
                logDir.entryList(
                    QStringList(QStringLiteral("*.") + fi.completeSuffix()),
                    QDir::NoSymLinks | QDir::Files));

    const QRegularExpression creationDateExtractor(
                fi.baseName() % QStringLiteral("(.*)") % QStringLiteral(".") % fi.completeSuffix());

    const auto startOfLogging(currentDate.addDays(-keepDays));

    QStringList obsoleteLogFileNames;

    for (const auto &fileName : logFileNames)
    {
        // determine creation date from file name instead of using file attributes, since file might
        // have been moved around, modified by user etc.
        const auto match(creationDateExtractor.match(fileName));
        if (match.hasMatch())
        {
            const auto creationDate(QDate::fromString(match.captured(1), datePattern));

            if (creationDate.isValid() && creationDate < startOfLogging)
            {
                obsoleteLogFileNames += fileName;
            }
        }
    }

#if (__cplusplus >= 201703L)
    for (const auto &fileName : std::as_const(obsoleteLogFileNames))
#else
    for (const auto &fileName : qAsConst(obsoleteLogFileNames))
#endif
    {
        QFile::remove(logDir.filePath(fileName));
    }
}

}

void QExtLogDailyFileAppender::activateOptions()
{
    QMutexLocker locker(&mObjectGuard);

    Q_ASSERT_X(mDateRetriever, "QExtLogDailyFileAppender::append()", "No date retriever set");

    closeFile();
    setLogFileForCurrentDay();
    deleteObsoleteFiles(mDateRetriever->currentDate(), mDatePattern, mKeepDays, mOriginalFilename);
    QExtLogFileAppender::activateOptions();
}

QString QExtLogDailyFileAppender::appendDateToFilename() const
{
    QFileInfo fi(mOriginalFilename);
    return fi.absolutePath() % QStringLiteral("/") % fi.baseName() %  mLastDate.toString(mDatePattern) % QStringLiteral(".") % fi.completeSuffix();
}

void QExtLogDailyFileAppender::append(const QExtLoggingEvent &event)
{
    Q_ASSERT_X(mDateRetriever, "QExtLogDailyFileAppender::append()", "No date retriever set");

    const auto currentDate(mDateRetriever->currentDate());

    if (currentDate != mLastDate)
    {
        rollOver();

        // schedule check for obsolete files for asynchronous execution, destructor will wait for
        // completion of each executor
        mDeleteObsoleteFilesExecutors.addFuture(
                    QtConcurrent::run(
                        deleteObsoleteFiles,
                        currentDate, mDatePattern, mKeepDays, mOriginalFilename));
    }
    QExtLogFileAppender::append(event);
}

void QExtLogDailyFileAppender::setDateRetriever(const QSharedPointer<const QExtLogDateRetrieverInterface> &dateRetriever)
{
    QMutexLocker locker(&mObjectGuard);

    mDateRetriever = dateRetriever;
}

void QExtLogDailyFileAppender::setLogFileForCurrentDay()
{
    if (mOriginalFilename.isEmpty())
        mOriginalFilename = file();

    Q_ASSERT_X(mDateRetriever, "QExtLogDailyFileAppender::setLogFileForCurrentDay()", "No date retriever set");

    mLastDate = mDateRetriever->currentDate();
    setFile(appendDateToFilename());
}

void QExtLogDailyFileAppender::rollOver()
{
    closeFile();
    setLogFileForCurrentDay();
    openFile();
}

// #include "moc_dailyfileappender.cpp"
