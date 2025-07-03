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

#include <qextLogDebugAppender.h>
#include <qextLoggingEvent.h>
#include <qextLogLayout.h>

#ifdef Q_OS_WIN
#   include <windows.h>
#endif

#include <iostream>

QExtLogDebugAppender::QExtLogDebugAppender(const QExtLogLayoutSharedPtr &layout,
                             QObject *parent) :
    QExtLogAppenderSkeleton(true, layout, parent)
{
}

bool QExtLogDebugAppender::requiresLayout() const
{
    return true;
}

void QExtLogDebugAppender::append(const QExtLoggingEvent &event)
{
    Q_ASSERT_X(layout(), "QExtLogDebugAppender::append()", "QExtLogLayout must not be null");

    QString message(layout()->format(event));
#ifdef Q_OS_WIN
    OutputDebugStringW(message.toStdWString().c_str());
#else
    std::cerr << message.toLocal8Bit().constData() << std::endl;
    std::cerr << std::flush;
#endif
}

// #include "moc_debugappender.cpp"
