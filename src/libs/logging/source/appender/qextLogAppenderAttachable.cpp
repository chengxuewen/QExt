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

#include <qextLogAppenderAttachable.h>
#include <qextLogListAppender.h>
#include <qextLogAppender.h>

#if (__cplusplus >= 201703L) // C++17 or later
#include <utility>
#endif

QExtLogAppenderAttachable::QExtLogAppenderAttachable() :
    mAppenderGuard(QReadWriteLock::Recursive)
{
}

QExtLogAppenderAttachable::~QExtLogAppenderAttachable() = default;

QList<QExtLogAppenderSharedPtr> QExtLogAppenderAttachable::appenders() const
{
    QReadLocker locker(&mAppenderGuard);
    return mAppenders;
}

QExtLogAppenderSharedPtr QExtLogAppenderAttachable::appender(const QString &name) const
{
    QReadLocker locker(&mAppenderGuard);

#if (__cplusplus >= 201703L)
    for (auto &&pAppender : std::as_const(mAppenders))
#else
    for (auto &&pAppender : qAsConst(mAppenders))
#endif
    {
        if (pAppender->name() == name)
        {
            return pAppender;
        }
    }
    return QExtLogAppenderSharedPtr();
}

void QExtLogAppenderAttachable::addAppender(const QExtLogAppenderSharedPtr &appender)
{
    if (appender.isNull())
    {
        return;
    }
    QWriteLocker locker(&mAppenderGuard);
    if (mAppenders.contains(appender))
    {
        return;
    }
    mAppenders.append(appender);
}

bool QExtLogAppenderAttachable::isAttached(const QExtLogAppenderSharedPtr &appender) const
{
    QReadLocker locker(&mAppenderGuard);
    return mAppenders.contains(appender);
}

void QExtLogAppenderAttachable::removeAllAppenders()
{
    mAppenders.clear();
}

void QExtLogAppenderAttachable::removeAppender(const QExtLogAppenderSharedPtr &appender)
{
    if (appender.isNull())
    {
        return;
    }
    QWriteLocker locker(&mAppenderGuard);
    mAppenders.removeAll(appender);

}

void QExtLogAppenderAttachable::removeAppender(const QString &name)
{
    QExtLogAppenderSharedPtr pAppender = appender(name);
    if (pAppender)
    {
        removeAppender(pAppender);
    }
}
