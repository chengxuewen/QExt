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

#include <qextLogAppenderSkeleton.h>
#include <qextLoggingEvent.h>
#include <qextLogManager.h>
#include <qextLogFilter.h>
#include <qextLogLayout.h>
#include <qextLogger.h>

/*!
 * \brief The class RecursionGuardLocker controls a boolean flag.
 *
 * It is a helper class to control a boolean flag. The class sets the flag
 * on creation and resets it on destruction.
 */
class RecursionGuardLocker
{
public:
    explicit RecursionGuardLocker(bool *guard);
    ~RecursionGuardLocker();
private:
    QEXT_DISABLE_COPY_MOVE(RecursionGuardLocker)
private:
    bool *mGuard;
};

inline RecursionGuardLocker::RecursionGuardLocker(bool *guard)
{
    Q_ASSERT_X(guard != nullptr, "RecursionGuardLocker::RecursionGuardLocker()", "Pointer to guard bool must not be null");

    mGuard = guard;
    *mGuard = true;
}

inline RecursionGuardLocker::~RecursionGuardLocker()
{
    *mGuard = false;
}

QExtLogAppenderSkeleton::QExtLogAppenderSkeleton(QObject *parent) :
    QExtLogAppender(parent),
#if QT_VERSION < 0x050E00
    mObjectGuard(QMutex::Recursive), // Recursive for doAppend()
#endif
    mAppendRecursionGuard(false),
    mIsActive(true),
    mIsClosed(false),
    mThreshold(QExtLogLevel::Null)
{
}

QExtLogAppenderSkeleton::QExtLogAppenderSkeleton(bool isActive,
                                   QObject *parent) :
    QExtLogAppender(parent),
#if QT_VERSION < 0x050E00
    mObjectGuard(QMutex::Recursive), // Recursive for doAppend()
#endif
    mAppendRecursionGuard(false),
    mIsActive(isActive),
    mIsClosed(false),
    mThreshold(QExtLogLevel::Null)
{
}

QExtLogAppenderSkeleton::QExtLogAppenderSkeleton(bool isActive,
                                   const QExtLogLayoutSharedPtr &layout,
                                   QObject *parent) :
    QExtLogAppender(parent),
#if QT_VERSION < 0x050E00
    mObjectGuard(QMutex::Recursive), // Recursive for doAppend()
#endif
    mAppendRecursionGuard(false),
    mIsActive(isActive),
    mIsClosed(false),
    mpLayout(layout),
    mThreshold(QExtLogLevel::Null)
{
}

QExtLogAppenderSkeleton::~QExtLogAppenderSkeleton()
{
    closeInternal();
}

void QExtLogAppenderSkeleton::activateOptions()
{
    QMutexLocker locker(&mObjectGuard);

    if (requiresLayout() && !layout())
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Activation of appender '%1' that requires layout and has no layout set"),
                                         QExtLogError::Error_AppenderActivateMissingLayout);
        e << name();
        logger()->error(e);
        return;
    }
    mIsActive = true;
}

void QExtLogAppenderSkeleton::addFilter(const QExtLogFilterSharedPtr &filter)
{
    if (!filter)
    {
        logger()->warn(QStringLiteral("Adding null QExtLogFilter to QExtLogAppender '%1'"), name());
        return;
    }

    QMutexLocker locker(&mObjectGuard);

    if (!mpTailFilter)
    {
        // filter list empty
        mpHeadFilter = filter;
        mpTailFilter = filter;
    }
    else
    {
        // append filter to the end of the filter list
        mpTailFilter->setNext(filter);
        mpTailFilter = filter;
    }
}

void QExtLogAppenderSkeleton::clearFilters()
{
    QMutexLocker locker(&mObjectGuard);

    mpHeadFilter.reset();
}

void QExtLogAppenderSkeleton::close()
{
    closeInternal();
}

void QExtLogAppenderSkeleton::closeInternal()
{
    QMutexLocker locker(&mObjectGuard);

    mIsClosed = true;
    mIsActive = false;
}

void QExtLogAppenderSkeleton::customEvent(QEvent *event)
{
    if (event->type() == QExtLoggingEvent::eventId)
    {
        const auto logEvent = static_cast<QExtLoggingEvent *>(event);
        doAppend(*logEvent);
        return ;
    }
    QObject::customEvent(event);
}

void QExtLogAppenderSkeleton::doAppend(const QExtLoggingEvent &event)
{
    // The mutex serialises concurrent access from multiple threads.
    // - e.g. two threads using the same logger
    // - e.g. two threads using different logger with the same appender
    //
    // A call from the same thread will pass the mutex (QMutex::Recursive)
    // and get to the recursion guard. The recursion guard blocks recursive
    // invocation and prevents a possible endless loop.
    // - e.g. an appender logs an error with a logger that uses it

    QMutexLocker locker(&mObjectGuard);

    if (mAppendRecursionGuard)
        return;

    RecursionGuardLocker recursion_locker(&mAppendRecursionGuard);

    if (!checkEntryConditions())
        return;
    if (!isAsSevereAsThreshold(event.level()))
        return;

    const auto  *filter = mpHeadFilter.data();
    while (filter)
    {
        QExtLogFilter::Decision decision = filter->decide(event);
        if (decision == QExtLogFilter::ACCEPT)
            break;
        else if (decision == QExtLogFilter::DENY)
            return;
        else
            filter = filter->next().data();
    }

    append(event);
}

bool QExtLogAppenderSkeleton::checkEntryConditions() const
{
    if (!isActive())
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of non activated appender '%1'"),
                                         QExtLogError::Error_AppenderNotActivated);
        e << name();
        logger()->error(e);
        return false;
    }
    if (isClosed())
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of closed appender '%1'"),
                                         QExtLogError::Error_AppenderClosedFailed);
        e << name();
        logger()->error(e);
        return false;
    }
    if (requiresLayout() && !layout())
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of appender '%1' that requires layout and has no layout set"),
                                         QExtLogError::Error_AppenderUseMissingLayout);
        e << name();
        logger()->error(e);
        return false;
    }

    return true;
}

void QExtLogAppenderSkeleton::setLayout(const QExtLogLayoutSharedPtr &layout)
{
    QMutexLocker locker(&mObjectGuard);
    mpLayout = layout;
}

QExtLogLayoutSharedPtr QExtLogAppenderSkeleton::layout() const
{
    QMutexLocker locker(&mObjectGuard);
    return mpLayout;
}

// #include "moc_appenderskeleton.cpp"
