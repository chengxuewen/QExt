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

#include <qextLogAsyncAppender.h>
#include <qextLogDispatcher.h>
#include <qextLoggingEvent.h>

#include <QCoreApplication>
#include <QReadLocker>
#include <QThread>

#if (__cplusplus >= 201703L) // C++17 or later
#include <utility>
#endif

QExtLogAsyncAppender::QExtLogAsyncAppender(QObject *parent) : QExtLogAppenderSkeleton(parent)
    , mThread(nullptr)
    , mDispatcher(nullptr)
{
}

QExtLogAsyncAppender::~QExtLogAsyncAppender()
{
    closeInternal();
}

bool QExtLogAsyncAppender::requiresLayout() const
{
    return false;
}

void QExtLogAsyncAppender::activateOptions()
{
    if (mThread != nullptr)
        return;

    mThread = new QThread();
    mDispatcher = new QExtLogDispatcher();
    mDispatcher->setAsyncAppender(this);

    mDispatcher->moveToThread(mThread);
    mThread->start();
}

void QExtLogAsyncAppender::close()
{
    closeInternal();
    QExtLogAppenderSkeleton::close();
}

void QExtLogAsyncAppender::closeInternal()
{
    QMutexLocker locker(&mObjectGuard);

    if (isClosed())
        return;

    if (mThread != nullptr)
    {
        mDispatcher->setAsyncAppender(nullptr);
        mThread->quit();
        mThread->wait();
        delete mThread;
        mThread = nullptr;
        delete mDispatcher;
        mDispatcher = nullptr;
    }
}

void QExtLogAsyncAppender::callAppenders(const QExtLoggingEvent &event) const
{
    Q_UNUSED(event)
    QReadLocker locker(&mAppenderGuard);

#if (__cplusplus >= 201703L)
    for (auto &&pAppender : std::as_const(mAppenders))
#else
    for (auto &&pAppender : qAsConst(mAppenders))
#endif
        pAppender->doAppend(event);
}

void QExtLogAsyncAppender::append(const QExtLoggingEvent &event)
{
    // Post to the event loop of the dispatcher
    qApp->postEvent(mDispatcher, new QExtLoggingEvent(event));
}

bool QExtLogAsyncAppender::checkEntryConditions() const
{
    if ((mThread != nullptr) && !mThread->isRunning())
    {
        QExtLogError e =
            QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of appender '%1' without a running dispatcher thread"),
                                QExtLogError::Error_AppenderAsyncDispatcherNotRunning);
        e << name();
        logger()->error(e);
        return false;
    }

    return QExtLogAppenderSkeleton::checkEntryConditions();
}

// #include "moc_asyncappender.cpp"
