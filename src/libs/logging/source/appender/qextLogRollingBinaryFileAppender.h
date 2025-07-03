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

#ifndef _QEXTLOGROLLINGBINARYFILEAPPENDER_H
#define _QEXTLOGROLLINGBINARYFILEAPPENDER_H

#include <qextLogBinaryFileAppender.h>

#include <QDateTime>

class QExtLogRollingBinaryFileAppender : public QExtLogBinaryFileAppender
{
    Q_OBJECT
    Q_PROPERTY(int maxBackupIndex READ maxBackupIndex WRITE setMaxBackupIndex)
    Q_PROPERTY(qint64 maximumFileSize READ maximumFileSize WRITE setMaximumFileSize)
    Q_PROPERTY(QString datePattern READ datePattern WRITE setDatePattern)
public:
    explicit QExtLogRollingBinaryFileAppender(QObject *parent = nullptr);

    enum DatePattern
    {
        MINUTELY_ROLLOVER = 0,  /*! The minutely date pattern string is "'.'yyyy-MM-dd-hh-mm". */
        HOURLY_ROLLOVER,        /*! The hourly date pattern string is "'.'yyyy-MM-dd-hh". */
        HALFDAILY_ROLLOVER,     /*! The half-daily date pattern string is "'.'yyyy-MM-dd-a". */
        DAILY_ROLLOVER,         /*! The daily date pattern string is "'.'yyyy-MM-dd". */
        WEEKLY_ROLLOVER,        /*! The weekly date pattern string is "'.'yyyy-ww". */
        MONTHLY_ROLLOVER        /*! The monthly date pattern string is "'.'yyyy-MM". */
    };
    Q_ENUM(DatePattern)

    int maxBackupIndex() const;
    void setMaxBackupIndex(int maxBackupIndex);
    qint64 maximumFileSize() const;
    void setMaximumFileSize(qint64 maximumFileSize);
    QString datePattern() const;
    void setDatePattern(DatePattern datePattern);
    void setDatePattern(const QString &datePattern);

protected:
    void append(const QExtLoggingEvent &event) override;
    void activateOptions() override;

    bool checkFotimeRollOver() const;
    void rollOvetime();
    bool checkForSizeRollOver() const;
    void rollOverSize();

private:
    void computeFrequency();
    void computeRollOvetime();
    QString frequencyToString() const;

    int mMaxBackupIndex;
    qint64 mMaximumFileSize;

    QString mDatePattern;
    DatePattern mFrequency;
    QString mActiveDatePattern;
    QDateTime mRollOvetime;
    QString mRollOverSuffix;
};


inline int QExtLogRollingBinaryFileAppender::maxBackupIndex() const
{
    return mMaxBackupIndex;
}

inline qint64 QExtLogRollingBinaryFileAppender::maximumFileSize() const
{
    return mMaximumFileSize;
}

inline void QExtLogRollingBinaryFileAppender::setMaxBackupIndex(int maxBackupIndex)
{
    mMaxBackupIndex = maxBackupIndex;
}

inline void QExtLogRollingBinaryFileAppender::setMaximumFileSize(qint64 maximumFileSize)
{
    mMaximumFileSize = maximumFileSize;
}

inline QString QExtLogRollingBinaryFileAppender::datePattern() const
{
    return mDatePattern;
}

inline void QExtLogRollingBinaryFileAppender::setDatePattern(const QString &datePattern)
{
    mDatePattern = datePattern;
}

#endif // _QEXTLOGROLLINGBINARYFILEAPPENDER_H
