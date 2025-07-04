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

#include <qextLogListAppender.h>

QExtLogListAppender::QExtLogListAppender(QObject *parent) :
    QExtLogAppenderSkeleton(parent),
    mConfiguratorList(false),
    mMaxCount(0)
{
}

QList<QExtLoggingEvent> QExtLogListAppender::list() const
{
    QMutexLocker locker(&mObjectGuard);
    return mList;
}

void QExtLogListAppender::setMaxCount(int n)
{
    QMutexLocker locker(&mObjectGuard);

    if (n < 0)
    {
        logger()->warn(QStringLiteral("Attempt to set maximum count for appender '%1' to %2. Using zero instead"),
                       name(), n);
        n = 0;
    }
    mMaxCount = n;
    ensureMaxCount();
}

QList<QExtLoggingEvent> QExtLogListAppender::clearList()
{
    QMutexLocker locker(&mObjectGuard);

    QList<QExtLoggingEvent> result = mList;
    mList.clear();
    return result;
}

void QExtLogListAppender::append(const QExtLoggingEvent &event)
{
    if ((mMaxCount <= 0) || (mList.size() < mMaxCount))
    {
        mList << event;
    }
}

void QExtLogListAppender::ensureMaxCount()
{
    if (mMaxCount <= 0)
    {
        return;
    }

    while (mList.size() > mMaxCount)
    {
        mList.removeFirst();
    }
}
