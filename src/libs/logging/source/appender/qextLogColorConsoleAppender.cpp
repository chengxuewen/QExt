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

#include <qextLogColorConsoleAppender.h>
#include <qextLoggingEvent.h>
#include <qextLogLayout.h>

#include <QTextStream>

#if (__cplusplus >= 201703L) // C++17 or later
#   include <utility>
#endif

#define NIX_BACK_BLACK      40
#define NIX_BACK_RED        41
#define NIX_BACK_GREEN      42
#define NIX_BACK_YELLOW     43
#define NIX_BACK_BLUE       44
#define NIX_BACK_MAGNETTA   45
#define NIX_BACK_CYAN       46
#define NIX_BACK_GRAY       47

#define NIX_FORE_BLACK      30
#define NIX_FORE_RED        31
#define NIX_FORE_GREEN      2
#define NIX_FORE_YELLOW     33
#define NIX_FORE_BLUE       34
#define NIX_FORE_MAGNETTA   35
#define NIX_FORE_CYAN       36
#define NIX_FORE_GRAY       37

#define NIX_FORE_BOLD       1

#define NIX_DEFAULT         0

#ifdef Q_OS_WIN
#define WIN_BACK_BLACK                  0
#define WIN_BACK_RED                    BACKGROUND_RED
#define WIN_BACK_LIGHT_RED              BACKGROUND_RED | BACKGROUND_INTENSITY
#define WIN_BACK_GREEN                  BACKGROUND_GREEN
#define WIN_BACK_LIGHT_GREEN            BACKGROUND_GREEN | BACKGROUND_INTENSITY
#define WIN_BACK_YELLOW                 BACKGROUND_GREEN | BACKGROUND_RED
#define WIN_BACK_LIGHT_YELLOW           BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
#define WIN_BACK_BLUE                   BACKGROUND_BLUE
#define WIN_BACK_LIGHT_BLUE             BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define WIN_BACK_MAGNETTA               BACKGROUND_RED | BACKGROUND_BLUE
#define WIN_BACK_LIGHT_MAGNETTA         BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY
#define WIN_BACK_CYAN                   BACKGROUND_BLUE | BACKGROUND_GREEN
#define WIN_BACK_LIGHT_CYAN             BACKGROUND_BLUE | BACKGROUND_GREEN
#define WIN_BACK_GRAY                   BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED
#define WIN_BACK_WHITE                  BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY

#define WIN_FORE_BLACK                  0
#define WIN_FORE_RED                    FOREGROUND_RED
#define WIN_FORE_LIGHT_RED              FOREGROUND_RED | FOREGROUND_INTENSITY
#define WIN_FORE_GREEN                  FOREGROUND_GREEN
#define WIN_FORE_LIGHT_GREEN            FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define WIN_FORE_YELLOW                 FOREGROUND_GREEN | FOREGROUND_RED
#define WIN_FORE_LIGHT_YELLOW           FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
#define WIN_FORE_BLUE                   FOREGROUND_BLUE
#define WIN_FORE_LIGHT_BLUE             FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define WIN_FORE_MAGNETTA               FOREGROUND_RED | FOREGROUND_BLUE
#define WIN_FORE_LIGHT_MAGNETTA         FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define WIN_FORE_CYAN                   FOREGROUND_BLUE | FOREGROUND_GREEN
#define WIN_FORE_LIGHT_CYAN             FOREGROUND_BLUE | FOREGROUND_GREEN
#define WIN_FORE_GRAY                   FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
#define WIN_FORE_WHITE                  FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY

#define WIN_FORE_BOLD                   FOREGROUND_INTENSITY

#define WIN_DEFAULT                     FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED

namespace detail
{
static void colorOutputString(HANDLE hConsole, const QString &output)
{
    QString message = output;

    // save colors
    CONSOLE_SCREEN_BUFFER_INFO cbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &cbi))
    {
        // if console is blocked by debugger use OutputDebugString
        OutputDebugString(message.toStdWString().c_str());
        return;
    }

    wchar_t *wideMessage;

    QStringList colorizedMessage = message.split('\033');

    int actualSize;
    DWORD out;

    QString parsedWordString;
    QStringList escParams;
    int indexOfM;
    // display first part of message
    if (!colorizedMessage.at(0).isEmpty())
    {
        wideMessage = new wchar_t [colorizedMessage.at(0).size()];
        actualSize = colorizedMessage.at(0).toWCharArray(wideMessage);
        WriteConsoleW(hConsole, wideMessage, actualSize, &out, QEXT_NULLPTR);
        delete [] wideMessage;
        colorizedMessage.removeAt(0);
    }
    for (QString it : colorizedMessage)
    {
        // color setted
        if (it.startsWith('['))
        {
            indexOfM = it.indexOf('m');

            // not esc-sequence
            if (indexOfM != -1)
            {
                WORD newColor = 0;
                parsedWordString = it.mid(1, indexOfM - 1);

                escParams = parsedWordString.split(';');
#if (__cplusplus >= 201703L)
                for (const auto &param : std::as_const(escParams))
#else
                for (const auto &param : qAsConst(escParams))
#endif
                {
                    WORD color = param.toUInt();
                    switch (color)
                    {
                    case NIX_DEFAULT:
                        newColor = WIN_DEFAULT;
                        break;
                    case NIX_FORE_BOLD:
                        newColor |= WIN_FORE_BOLD;
                        break;
                    case NIX_BACK_BLACK :
                        newColor = (newColor & 0x0f) | WIN_BACK_BLACK;
                        break;
                    case NIX_BACK_RED :
                        newColor = (newColor & 0x0f) | WIN_BACK_RED;
                        break;
                    case NIX_BACK_GREEN :
                        newColor = (newColor & 0x0f) | WIN_BACK_GREEN;
                        break;
                    case NIX_BACK_YELLOW :
                        newColor = (newColor & 0x0f) | WIN_BACK_YELLOW;
                        break;
                    case NIX_BACK_BLUE :
                        newColor = (newColor & 0x0f) | WIN_BACK_BLUE;
                        break;
                    case NIX_BACK_MAGNETTA :
                        newColor = (newColor & 0x0f) | WIN_BACK_MAGNETTA;
                        break;
                    case NIX_BACK_CYAN :
                        newColor = (newColor & 0x0f) | WIN_BACK_CYAN;
                        break;
                    case NIX_BACK_GRAY :
                        newColor = (newColor & 0x0f) | WIN_BACK_GRAY;
                        break;
                    case NIX_FORE_BLACK :
                        newColor = (newColor & 0xF8) | WIN_FORE_BLACK;
                        break;
                    case NIX_FORE_RED :
                        newColor = (newColor & 0xF8) | WIN_FORE_RED;
                        break;
                    case NIX_FORE_GREEN :
                        newColor = (newColor & 0xF8) | WIN_FORE_GREEN;
                        break;
                    case NIX_FORE_YELLOW :
                        newColor = (newColor & 0xF8) | WIN_FORE_YELLOW;
                        break;
                    case NIX_FORE_BLUE :
                        newColor = (newColor & 0xF8) | WIN_FORE_BLUE;
                        break;
                    case NIX_FORE_MAGNETTA :
                        newColor = (newColor & 0xF8) | WIN_FORE_MAGNETTA;
                        break;
                    case NIX_FORE_CYAN :
                        newColor = (newColor & 0xF8) | WIN_FORE_CYAN;
                        break;
                    case NIX_FORE_GRAY :
                        newColor = (newColor & 0xF8) | WIN_FORE_GRAY;
                        break;
                    default:
                        break;
                    }
                }
                it = it.mid(indexOfM + 1);

                SetConsoleTextAttribute(hConsole, newColor);
            }
        }

        wideMessage = new wchar_t [it.size()];
        actualSize = it.toWCharArray(wideMessage);
        WriteConsoleW(hConsole, wideMessage, actualSize, &out, QEXT_NULLPTR);
        delete [] wideMessage;
    }
    // load old colors
    SetConsoleTextAttribute(hConsole, cbi.wAttributes);
}
#endif
}


QExtLogColorConsoleAppender::QExtLogColorConsoleAppender(QObject *parent) :
    QExtLogConsoleAppender(parent),
    mConsoleHandle(QEXT_NULLPTR)
{
}

QExtLogColorConsoleAppender::QExtLogColorConsoleAppender(const QExtLogLayoutSharedPtr &layout, QObject *parent) :
    QExtLogConsoleAppender(layout, parent),
    mConsoleHandle(QEXT_NULLPTR)
{
}

QExtLogColorConsoleAppender::QExtLogColorConsoleAppender(const QExtLogLayoutSharedPtr &layout,
                                                         const QString &target, QObject *parent) :
    QExtLogConsoleAppender(layout, target, parent),
    mConsoleHandle(QEXT_NULLPTR)
{
}

QExtLogColorConsoleAppender::QExtLogColorConsoleAppender(const QExtLogLayoutSharedPtr &layout, TargetEnum target,
                                                         QObject *parent) :
    QExtLogConsoleAppender(layout, target, parent),
    mConsoleHandle(QEXT_NULLPTR)
{
}

QExtLogColorConsoleAppender::~QExtLogColorConsoleAppender()
{
    this->closeInternal();
}

#ifdef Q_OS_WIN
void QExtLogColorConsoleAppender::append(const QExtLoggingEvent &event)
{
    QString message = this->layout()->format(event);

    detail::colorOutputString(mConsoleHandle, message);

    if (handleIoErrors())
    {
        return;
    }

    if (this->immediateFlush())
    {
        this->writer()->flush();
        if (this->handleIoErrors())
        {
            return;
        }
    }
}

void QExtLogColorConsoleAppender::activateOptions()
{
    QExtLogConsoleAppender::activateOptions();

    if (this->target() == QStringLiteral("Target_Stdout"))
    {
        mConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    else
    {
        mConsoleHandle = GetStdHandle(STD_ERROR_HANDLE);
    }
}

void QExtLogColorConsoleAppender::close()
{
    this->closeInternal();
    QExtLogConsoleAppender::close();
}
#endif

void QExtLogColorConsoleAppender::closeInternal()
{
    QMutexLocker locker(&mObjectGuard);

    if (this->isClosed())
    {
        return;
    }

#ifdef Q_OS_WIN
    CloseHandle(mConsoleHandle);
#endif
}

