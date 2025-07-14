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

#ifndef _QEXTLOGCOLORCONSOLEAPPENDER_H
#define _QEXTLOGCOLORCONSOLEAPPENDER_H

#include <qextLogConsoleAppender.h>

// if we are in WIN*
#ifdef Q_OS_WIN
#   define WIN32_LEAN_AND_MEAN
#   define NOGDI
#   include <windows.h>
#endif

class QFile;
class QTextStream;

/*!
 * \brief The class QExtLogColorConsoleAppender appends to stdout or stderr with color formatting.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogColorConsoleAppender : public QExtLogConsoleAppender
{
    Q_OBJECT

public:
    QExtLogColorConsoleAppender(QObject *parent = QEXT_NULLPTR);
    QExtLogColorConsoleAppender(const QExtLogLayoutSharedPtr &layout,
                                QObject *parent = QEXT_NULLPTR);
    QExtLogColorConsoleAppender(const QExtLogLayoutSharedPtr &layout,
                                const QString &target,
                                QObject *parent = QEXT_NULLPTR);
    /*!
     * Creates a ConsoleAppender with the layout \a pLayout, the target
     * value specified by the \a target constant and the parent
     * \a parent.
     */
    QExtLogColorConsoleAppender(const QExtLogLayoutSharedPtr &layout,
                                Target target,
                                QObject *parent = QEXT_NULLPTR);

    ~QExtLogColorConsoleAppender() QEXT_OVERRIDE;
    // if we are in WIN*
#ifdef Q_OS_WIN
    void activateOptions() QEXT_OVERRIDE;
    void close() QEXT_OVERRIDE;

protected:
    void append(const QExtLoggingEvent &event) QEXT_OVERRIDE;

private:
    HANDLE mConsoleHandle;
#endif
    void closeInternal();
};

#endif // _QEXTLOGCOLORCONSOLEAPPENDER_H
