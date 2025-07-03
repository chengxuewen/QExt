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

#include <qextLogConsoleAppender.h>
#include <qextLogOptionConverter.h>
#include <qextLoggingEvent.h>
#include <qextLogLayout.h>

#include <QTextStream>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

QExtLogConsoleAppender::QExtLogConsoleAppender(QObject *parent) :
    QExtLogWriterAppender(parent),
    mTarget(STDOUT_TARGET),
    mtextStream(nullptr)
{
}


QExtLogConsoleAppender::QExtLogConsoleAppender(const QExtLogLayoutSharedPtr &pLayout,
                                 QObject *parent) :
    QExtLogWriterAppender(pLayout, parent),
    mTarget(STDOUT_TARGET),
    mtextStream(nullptr)
{
}


QExtLogConsoleAppender::QExtLogConsoleAppender(const QExtLogLayoutSharedPtr &pLayout,
                                 const QString &target,
                                 QObject *parent) :
    QExtLogWriterAppender(pLayout, parent),
    mTarget(STDOUT_TARGET),
    mtextStream(nullptr)
{
    setTarget(target);
}


QExtLogConsoleAppender::QExtLogConsoleAppender(const QExtLogLayoutSharedPtr &pLayout,
                                 Target target,
                                 QObject *parent) :
    QExtLogWriterAppender(pLayout, parent),
    mTarget(target),
    mtextStream(nullptr)
{
}


QExtLogConsoleAppender::~QExtLogConsoleAppender()
{
    closeInternal();
}

QString QExtLogConsoleAppender::target() const
{
    if (mTarget == STDOUT_TARGET)
        return QStringLiteral("STDOUT_TARGET");
    return QStringLiteral("STDERR_TARGET");
}

void QExtLogConsoleAppender::setTarget(const QString &target)
{
    bool ok;
    auto targetEnum = static_cast<Target>(QExtLogOptionConverter::toTarget(target, &ok));
    if (ok)
        setTarget(targetEnum);
}

void QExtLogConsoleAppender::activateOptions()
{
    QMutexLocker locker(&mObjectGuard);

    closeStream();

    if (mTarget == STDOUT_TARGET)
        mtextStream = new QTextStream(stdout);
    else
        mtextStream = new QTextStream(stderr);
    setWriter(mtextStream);

    QExtLogWriterAppender::activateOptions();
}

void QExtLogConsoleAppender::close()
{
    closeInternal();
    QExtLogWriterAppender::close();
}

void QExtLogConsoleAppender::closeInternal()
{
    QMutexLocker locker(&mObjectGuard);

    if (isClosed())
        return;

    closeStream();
}

void QExtLogConsoleAppender::closeStream()
{
    setWriter(nullptr);
    delete mtextStream;
    mtextStream = nullptr;
}

void QExtLogConsoleAppender::append(const QExtLoggingEvent &event)
{
#ifdef Q_OS_WIN
    if (GetConsoleWindow() == nullptr &&
        qEnvironmentVariableIntValue("QT_ASSUME_STDERR_HAS_CONSOLE") == 0)
    {
        // if console is blocked by debugger use OutputDebugString
        Q_ASSERT_X(layout(), "QExtLogConsoleAppender::append()", "QExtLogLayout must not be null");

        QString message(layout()->format(event));

        OutputDebugString(message.toStdWString().c_str());
    }
    else
#endif
        QExtLogWriterAppender::append(event);
}

// #include "moc_consoleappender.cpp"
