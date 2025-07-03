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

#ifndef _QEXTLOGHIERARCHY_H
#define _QEXTLOGHIERARCHY_H

#include <qextLoggerRepository.h>

#include <QReadWriteLock>
#include <QHash>

/*!
 * \brief The class QExtLogHierarchy implements a logger repository.
 *
 * \note All the functions declared in this class are thread-safe.
 */
class QEXT_LOGGING_API QExtLogHierarchy : public QExtLoggerRepository
{
public:
    QExtLogHierarchy();
    ~QExtLogHierarchy() override;

public:
    bool exists(const QString &name) const override;
    QExtLogger *logger(const QString &name) override;
    QList<QExtLogger *> loggers() const override;
    QExtLogger *rootLogger() const override;
    QExtLogLevel threshold() const override;
    void setThreshold(QExtLogLevel level) override;
    void setThreshold(const QString &threshold) override;

    bool isDisabled(QExtLogLevel level) override;
    void resetConfiguration() override;
    void shutdown() override;

private:
    QExtLogger *createLogger(const QString &name);
    void resetLogger(QExtLogger *logger, QExtLogLevel level) const;

private:
    mutable QReadWriteLock mObjectGuard;
    QHash<QString, QExtLogger *> mLoggers;
    QExtLogLevel mThreshold;
    QExtLogger *mRootLogger;
};

inline QExtLogger *QExtLogHierarchy::rootLogger() const
{
    return mRootLogger;
}

inline QExtLogLevel QExtLogHierarchy::threshold() const
{
    return mThreshold;
}

inline void QExtLogHierarchy::setThreshold(QExtLogLevel level)
{
    mThreshold = level;
}

inline bool QExtLogHierarchy::isDisabled(QExtLogLevel level)
{
    return level < mThreshold;
}

#endif // _QEXTLOGHIERARCHY_H
