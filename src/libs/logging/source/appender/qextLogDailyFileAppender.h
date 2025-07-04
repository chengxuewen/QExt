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

#ifndef _QEXTLOGDAILYFILEAPPENDER_H
#define _QEXTLOGDAILYFILEAPPENDER_H

#include <qextLogFileAppender.h>

#include <QFutureSynchronizer>
#include <QSharedPointer>
#include <QString>
#include <QDate>

class QEXT_LOGGING_API QExtLogDateRetrieverInterface
{
public:
    virtual ~QExtLogDateRetrieverInterface();
    virtual QDate currentDate() const = 0;
};

class QEXT_LOGGING_API QExtLogDefaultDateRetriever final : public QExtLogDateRetrieverInterface
{
public:

    /**
     * Return the current date, as reported by the system clock.
     */
    QDate currentDate() const override;
};

/*!
 * \brief The class QExtLogDailyFileAppender extends QExtLogFileAppender so that the
 * a log file is created for each day
 */
class QEXT_LOGGING_API QExtLogDailyFileAppender : public QExtLogFileAppender
{
    Q_OBJECT

    //! The property holds the date pattern used by the appender.
    Q_PROPERTY(QString datePattern READ datePattern WRITE setDatePattern)

    /**
     * Number of days that old log files will be kept on disk.
     * Set to a positive value to enable automatic deletion. Per default, all files are kept. Check
     * for obsolete files happens once a day.
     */
    Q_PROPERTY(int keepDays READ keepDays WRITE setKeepDays)

public:
    explicit QExtLogDailyFileAppender(QObject *parent = QEXT_NULLPTR);
    QExtLogDailyFileAppender(const QExtLogLayoutSharedPtr &layout, const QString &fileName, const QString &datePattern = QString(), int keepDays = 0, QObject *parent = QEXT_NULLPTR);

    QString datePattern() const;
    void setDatePattern(const QString &datePattern);

    int keepDays() const;
    void setKeepDays(int keepDays);

    void activateOptions() override;

    void append(const QExtLoggingEvent &event) override;

    void setDateRetriever(const QSharedPointer<const QExtLogDateRetrieverInterface> &dateRetriever);

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogDailyFileAppender)

    void setLogFileForCurrentDay();
    void rollOver();
    QString appendDateToFilename() const;

    QSharedPointer<const QExtLogDateRetrieverInterface> mDateRetriever;

    QString mDatePattern;
    QDate mLastDate;
    int mKeepDays;
    QString mOriginalFilename;

    QFutureSynchronizer<void> mDeleteObsoleteFilesExecutors;
};

#endif // _QEXTLOGDAILYFILEAPPENDER_H
