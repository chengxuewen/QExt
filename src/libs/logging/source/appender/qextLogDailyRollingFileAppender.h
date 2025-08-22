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

#ifndef _QEXTLOGDAILYROLLINGFILEAPPENDER_H
#define _QEXTLOGDAILYROLLINGFILEAPPENDER_H

#include <qextLogFileAppender.h>

#include <QDateTime>

/*!
 * \brief The class QExtLogDailyRollingFileAppender extends QExtLogFileAppender so that the
 *        underlying file is rolled over at a specified frequency.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \note The ownership and lifetime of objects of this class are managed. See
 *       \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogDailyRollingFileAppender : public QExtLogFileAppender
{
    Q_OBJECT

    /*!
     * The property holds the date pattern used by the appender.
     *
     * The default is DAILY_ROLLOVER for rollover at midnight each day.
     *
     * \sa datePattern(), setDatePattern()
     */
    Q_PROPERTY(QString datePattern READ datePattern WRITE setDatePattern)

public:
    /*!
     * The enum DatePattern defines constants for date patterns.
     *
     * \sa setDatePattern(DatePattern)
     */
    enum DatePattern
    {
        /*! The minutely date pattern string is "'.'yyyy-MM-dd-hh-mm". */
        MINUTELY_ROLLOVER = 0,
        /*! The hourly date pattern string is "'.'yyyy-MM-dd-hh". */
        HOURLY_ROLLOVER,
        /*! The half-daily date pattern string is "'.'yyyy-MM-dd-a". */
        HALFDAILY_ROLLOVER,
        /*! The daily date pattern string is "'.'yyyy-MM-dd". */
        DAILY_ROLLOVER,
        /*! The weekly date pattern string is "'.'yyyy-ww". */
        WEEKLY_ROLLOVER,
        /*! The monthly date pattern string is "'.'yyyy-MM". */
        MONTHLY_ROLLOVER
    };
    Q_ENUM(DatePattern)

    QExtLogDailyRollingFileAppender(QObject *parent = QEXT_NULLPTR);
    QExtLogDailyRollingFileAppender(const QExtLogLayoutSharedPtr &layout,
                             const QString &fileName,
                             const QString &datePattern,
                             QObject *parent = QEXT_NULLPTR);

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtLogDailyRollingFileAppender)
public:
    QString datePattern() const;

    /*!
    * Sets the datePattern to the value specified by the \a datePattern
    * constant.
    */
    void setDatePattern(DatePattern datePattern);

    void setDatePattern(const QString &datePattern);

    void activateOptions() QEXT_OVERRIDE;

protected:
    void append(const QExtLoggingEvent &event) QEXT_OVERRIDE;

    /*!
     * Tests if all entry conditions for using append() in this class are
     * met.
     *
     * If a conditions is not met, an error is logged and the function
     * returns false. Otherwise the result of
     * QExtLogFileAppender::checkEntryConditions() is returned.
     *
     * The checked conditions are:
     * - A valid pattern has been set (QExtLogError::Error_AppenderUseInvalidPattern)
     *
     * The function is called as part of the checkEntryConditions() chain
     * started by QExtLogAppenderSkeleton::doAppend().
     *
     * \sa QExtLogAppenderSkeleton::doAppend(),
     *     QExtLogAppenderSkeleton::checkEntryConditions()
     */
    bool checkEntryConditions() const QEXT_OVERRIDE;

private:
    void computeFrequency();
    void computeRollOvetime();
    QString frequencyToString() const;
    void rollOver();

private:
    QString mDatePattern;
    DatePattern mFrequency;
    QString mActiveDatePattern;
    QDateTime mRollOvetime;
    QString mRollOverSuffix;
};

inline QString QExtLogDailyRollingFileAppender::datePattern() const
{
    QMutexLocker locker(&mObjectGuard);
    return mDatePattern;
}

inline void QExtLogDailyRollingFileAppender::setDatePattern(const QString &datePattern)
{
    QMutexLocker locker(&mObjectGuard);
    mDatePattern = datePattern;
}

#endif // _QEXTLOGDAILYROLLINGFILEAPPENDER_H
