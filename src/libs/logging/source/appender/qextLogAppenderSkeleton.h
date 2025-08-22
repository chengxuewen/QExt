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

#ifndef _QEXTLOGAPPENDERSKELETON_H
#define _QEXTLOGAPPENDERSKELETON_H

#include <qextLogAppender.h>
#include <qextLogLayout.h>
#include <qextLogFilter.h>
#include <qextLogger.h>

#include <QMutex>

class QExtLogger;
class QExtLoggingEvent;

/*!
 * \brief The class QExtLogAppenderSkeleton implements general QExtLogAppender functionality.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \note The ownership and lifetime of objects of this class are managed. See
 *       \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogAppenderSkeleton : public QExtLogAppender
{
    Q_OBJECT

    /*!
     * The property holds if the QExtLogAppender has been activated.
     *
     * \sa isActive()
     */
    Q_PROPERTY(bool isActive READ isActive)

    /*!
     * The property holds if the QExtLogAppender has been closed.
     *
     * \sa isClosed()
     */
    Q_PROPERTY(bool isClosed READ isClosed)

    /*!
     * The property holds the threshold level used by the QExtLogAppender.
     *
     * \sa threshold(), setThreshold()
     */
    Q_PROPERTY(QExtLogLevel threshold READ threshold WRITE setThreshold)

public:
    explicit QExtLogAppenderSkeleton(QObject *parent = QEXT_NULLPTR);

protected:
    explicit QExtLogAppenderSkeleton(bool isActive,
                              QObject *parent = QEXT_NULLPTR);
    explicit QExtLogAppenderSkeleton(bool isActive,
                              const QExtLogLayoutSharedPtr &layout,
                              QObject *parent = QEXT_NULLPTR);
    ~QExtLogAppenderSkeleton() QEXT_OVERRIDE;

public:
    QExtLogFilterSharedPtr filter() const QEXT_OVERRIDE;
    QExtLogLayoutSharedPtr layout() const QEXT_OVERRIDE;
    bool isActive() const;
    bool isClosed() const;
    QString name() const QEXT_OVERRIDE;
    QExtLogLevel threshold() const;
    void setLayout(const QExtLogLayoutSharedPtr &layout) QEXT_OVERRIDE;
    void setName(const QString &name) QEXT_OVERRIDE;
    void setThreshold(QExtLogLevel level);

    virtual void activateOptions();
    void addFilter(const QExtLogFilterSharedPtr &filter) QEXT_OVERRIDE;
    void clearFilters() QEXT_OVERRIDE;
    void close() QEXT_OVERRIDE;

    /*!
     * Performs checks and delegates the actuall appending to the subclass
     * specific append() function.
     *
     * \sa append(), checkEntryConditions(), isAsSevereAsThreshold(), QExtLogFilter
     */
    void doAppend(const QExtLoggingEvent &event) QEXT_OVERRIDE;

    QExtLogFilterSharedPtr firstFilter() const;
    bool isAsSevereAsThreshold(QExtLogLevel level) const;

protected:
    virtual void append(const QExtLoggingEvent &event) = 0;
    void customEvent(QEvent *event) QEXT_OVERRIDE;

    /*!
     * Tests if all entry conditions for using append() in this class are
     * met.
     *
     * If a conditions is not met, an error is logged and the function
     * returns false.
     *
     * The checked conditions are:
     * - That the appender has been activated (QExtLogError::Error_AppenderNotActivated)
     * - That the appender was not closed (QExtLogError::Error_AppenderClosedFailed)
     * - That the appender has a layout set, if it requires one
     *   (logging_error(QExtLogError::Error_AppenderUseMissingLayout)
     *
     * The function is called as part of the checkEntryConditions() chain
     * started by doAppend(). The doAppend() function calls the subclass
     * specific checkEntryConditions() function. The function checks the
     * class specific conditions and calls checkEntryConditions() of
     * it's parent class. The last function called is
     * QExtLogAppenderSkeleton::checkEntryConditions().
     *
     * \sa doAppend()
     */
    virtual bool checkEntryConditions() const;

protected:
#if QT_VERSION < 0x050E00
    mutable QMutex mObjectGuard;
#else
    mutable QRecursiveMutex mObjectGuard;
#endif

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtLogAppenderSkeleton)
    bool mAppendRecursionGuard;
    volatile bool mIsActive;
    volatile bool mIsClosed;
    QExtLogLayoutSharedPtr mpLayout;
    QExtLogLevel mThreshold;
    QExtLogFilterSharedPtr mpHeadFilter;
    QExtLogFilterSharedPtr mpTailFilter;
    void closeInternal();
};

inline QExtLogFilterSharedPtr QExtLogAppenderSkeleton::filter() const
{
    QMutexLocker locker(&mObjectGuard);
    return mpHeadFilter;
}

inline QString QExtLogAppenderSkeleton::name() const
{
    QMutexLocker locker(&mObjectGuard);
    return objectName();
}

inline QExtLogLevel QExtLogAppenderSkeleton::threshold() const
{
    return mThreshold;
}

inline void QExtLogAppenderSkeleton::setName(const QString &name)
{
    QMutexLocker locker(&mObjectGuard);
    setObjectName(name);
}

inline void QExtLogAppenderSkeleton::setThreshold(QExtLogLevel level)
{
    mThreshold = level;
}

inline bool QExtLogAppenderSkeleton::isActive() const
{
    return mIsActive;
}

inline bool QExtLogAppenderSkeleton::isClosed() const
{
    return mIsClosed;
}

inline QExtLogFilterSharedPtr QExtLogAppenderSkeleton::firstFilter() const
{
    QMutexLocker locker(&mObjectGuard);
    return filter();
}

inline bool QExtLogAppenderSkeleton::isAsSevereAsThreshold(QExtLogLevel level) const
{
    return (mThreshold <= level);
}

#endif // _QEXTLOGAPPENDERSKELETON_H
