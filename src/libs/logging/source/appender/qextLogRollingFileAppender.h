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

#ifndef _QEXTLOGROLINGFILEAPPENDER_H
#define _QEXTLOGROLINGFILEAPPENDER_H

#include <qextLogFileAppender.h>

/*!
 * \brief The class QExtLogRollingFileAppender extends QExtLogFileAppender to backup
 *        the log files when they reach a certain size.
 *        On application restart the existing log files are rolled
 *        if appendFile is set to false to avoid data loss.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogRollingFileAppender : public QExtLogFileAppender
{
    Q_OBJECT

    /*!
     * The property holds the maximum backup count used by the appender.
     *
     * The default is 1.
     *
     * \sa maxBackupIndex(), setMaxBackupIndex()
     */
    Q_PROPERTY(int maxBackupIndex READ maxBackupIndex WRITE setMaxBackupIndex)

    /*!
     * The property holds the maximum file size used by the appender.
     *
     * The default is 10 MB (10 * 1024 * 1024).
     *
     * \sa maximumFileSize(), setMaximumFileSize()
     */
    Q_PROPERTY(qint64 maximumFileSize READ maximumFileSize WRITE setMaximumFileSize)

    /*!
     * The property sets the maximum file size from a string value.
     *
     * \sa setMaxFileSize(), maximumFileSize()
     */
    Q_PROPERTY(QString maxFileSize READ maxFileSize WRITE setMaxFileSize)

public:
    QExtLogRollingFileAppender(QObject *parent = QEXT_NULLPTR);
    QExtLogRollingFileAppender(const QExtLogLayoutSharedPtr &layout,
                        const QString &fileName,
                        QObject *parent = QEXT_NULLPTR);
    QExtLogRollingFileAppender(const QExtLogLayoutSharedPtr &layout,
                        const QString &fileName,
                        bool append,
                        QObject *parent = QEXT_NULLPTR);

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogRollingFileAppender)

public:
    int maxBackupIndex() const;
    qint64 maximumFileSize() const;
    QString maxFileSize() const;
    void setMaxBackupIndex(int maxBackupIndex);
    void setMaximumFileSize(qint64 maximumFileSize);
    void setMaxFileSize(const QString &maxFileSize);

protected:
    void append(const QExtLoggingEvent &event) QEXT_OVERRIDE;
    void openFile() QEXT_OVERRIDE;

private:
    void rollOver();

private:
    int mMaxBackupIndex;
    qint64 mMaximumFileSize;
};

inline int QExtLogRollingFileAppender::maxBackupIndex() const
{
    QMutexLocker locker(&mObjectGuard);
    return mMaxBackupIndex;
}

inline qint64 QExtLogRollingFileAppender::maximumFileSize() const
{
    QMutexLocker locker(&mObjectGuard);
    return mMaximumFileSize;
}

inline QString QExtLogRollingFileAppender::maxFileSize() const
{
    QMutexLocker locker(&mObjectGuard);
    return QString::number(mMaximumFileSize);
}

inline void QExtLogRollingFileAppender::setMaxBackupIndex(int maxBackupIndex)
{
    QMutexLocker locker(&mObjectGuard);
    mMaxBackupIndex = maxBackupIndex;
}

inline void QExtLogRollingFileAppender::setMaximumFileSize(qint64 maximumFileSize)
{
    QMutexLocker locker(&mObjectGuard);
    mMaximumFileSize = maximumFileSize;
}

#endif // _QEXTLOGROLINGFILEAPPENDER_H
