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

#include <qextLogDispatcher.h>
#include <qextLoggingEvent.h>
#include <qextLogAsyncAppender.h>

#include <QCoreApplication>

QExtLogDispatcher::QExtLogDispatcher(QObject *parent) : QObject(parent)
    , mAsyncAppender(nullptr)
{}

void QExtLogDispatcher::customEvent(QEvent *event)
{
    if (event->type() == QExtLoggingEvent::eventId)
    {
        auto *logEvent = static_cast<QExtLoggingEvent *>(event);
        if (mAsyncAppender != nullptr)
            mAsyncAppender->callAppenders(*logEvent);
    }
    QObject::customEvent(event);
}

void QExtLogDispatcher::setAsyncAppender(QExtLogAsyncAppender *asyncAppender)
{
    mAsyncAppender = asyncAppender;
}

// #include "moc_dispatcher.cpp"
