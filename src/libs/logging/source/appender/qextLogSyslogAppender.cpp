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

#include <qextLogSyslogAppender.h>
#include <qextLoggingEvent.h>
#include <qextLogLayout.h>
#include <qextLogLevel.h>

#include <QCoreApplication>

#ifdef Q_OS_WIN
#ifndef UNICODE
#define UNICODE
#endif
#include <qt_windows.h>

#include <QLibrary>

typedef HANDLE(WINAPI *PDeregisterEventSource)(HANDLE);
static PDeregisterEventSource pDeregisterEventSource = QEXT_NULLPTR;
typedef BOOL(WINAPI *PReportEvent)(HANDLE, WORD, WORD, DWORD, PSID, WORD, DWORD, LPCTSTR *, LPVOID);
static PReportEvent pReportEvent = QEXT_NULLPTR;
typedef HANDLE(WINAPI *PRegisterEventSource)(LPCTSTR, LPCTSTR);
static PRegisterEventSource pRegisterEventSource = QEXT_NULLPTR;

#define RESOLVE(name) p##name = reinterpret_cast<P##name>(lib.resolve(#name));
#define RESOLVEA(name) p##name = reinterpret_cast<P##name>(lib.resolve(#name"A"));
#define RESOLVEW(name) p##name = reinterpret_cast<P##name>(lib.resolve(#name"W"));

static bool winServiceInit()
{
    if (pDeregisterEventSource == QEXT_NULLPTR)
    {
        QLibrary lib(QStringLiteral("advapi32"));

        // only resolve unicode versions
        RESOLVE(DeregisterEventSource);
        RESOLVEW(ReportEvent);
        RESOLVEW(RegisterEventSource);
    }
    return pDeregisterEventSource != QEXT_NULLPTR;
}
#else

#include <pwd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <sys/stat.h>

static QString encodeName(const QString &name, bool allowUpper = false)
{
    QString n = name.toLower();
    QString legal = QStringLiteral("abcdefghijklmnopqrstuvwxyz1234567890");
    if (allowUpper)
    {
        legal += QStringLiteral("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }
    int pos = 0;
    while (pos < n.size())
    {
        if (legal.indexOf(n[pos]) == -1)
        {
            n.remove(pos, 1);
        }
        else
        {
            ++pos;
        }
    }
    return n;
}
#endif

QExtLogSystemLogAppender::QExtLogSystemLogAppender(QObject *parent) :
    QExtLogAppenderSkeleton(parent), ident(QEXT_NULLPTR)
{
    setServiceName(QCoreApplication::applicationName());
}

QExtLogSystemLogAppender::~QExtLogSystemLogAppender()
{
    delete[] ident;
}

void QExtLogSystemLogAppender::append(const QExtLoggingEvent &event)
{
    QString message(layout()->format(event));

#ifdef Q_OS_WIN
    if (!winServiceInit())
        return;
    WORD wType;
    switch (event.level().toInt())
    {
    case QExtLogLevel::Warn:
        wType = EVENTLOG_WARNING_TYPE;
        break;
    case QExtLogLevel::Error:
        wType = EVENTLOG_ERROR_TYPE;
        break;
    case QExtLogLevel::Fatal:
        wType = EVENTLOG_ERROR_TYPE;
        break;
    case QExtLogLevel::Off:
        wType = EVENTLOG_SUCCESS;
        break;
    default:
        wType = EVENTLOG_INFORMATION_TYPE;
        break;
    }

    HANDLE h = pRegisterEventSource(QEXT_NULLPTR, serviceName().toStdWString().c_str());
    if (h != QEXT_NULLPTR)
    {
        int id = 0;
        uint category = 0;
        auto msg = message.toStdWString();
        const wchar_t *msg_wstr = msg.c_str();
        const char *bindata = QEXT_NULLPTR;//data.size() ? data.constData() : 0;
        const int datasize = 0;
        pReportEvent(h, wType, category, id, QEXT_NULLPTR, 1, datasize,
                     &msg_wstr, const_cast<char *> (bindata));
        pDeregisterEventSource(h);
    }
#else

    int st;
    switch (event.level().toInt())
    {
    case QExtLogLevel::Warn:
        st = LOG_WARNING;
        break;
    case QExtLogLevel::Error:
        st = LOG_ERR;
        break;
    case QExtLogLevel::Fatal:
        st = LOG_ERR;
        break;
    default:
        st = LOG_INFO;
    }

    openlog(ident, LOG_PID, LOG_DAEMON);

#if QT_VERSION >= 0x050e00
    for (const auto &line : message.split('\n', Qt::SkipEmptyParts))
#else
    for (const auto &line : message.split('\n', QString::SkipEmptyParts))
#endif
    {
        syslog(st, "%s", line.toLocal8Bit().constData());
    }
    closelog();

#endif
}

QString QExtLogSystemLogAppender::serviceName() const
{
    return mServiceName;
}

void QExtLogSystemLogAppender::setServiceName(const QString &serviceName)
{
    mServiceName = serviceName;

#if !defined(Q_OS_WIN)
    delete[] ident;
    QString tmp = encodeName(mServiceName, true);
    int len = tmp.toLocal8Bit().size();
    ident = new char[len + 1];
    ident[len] = '\0';
    ::memcpy(ident, tmp.toLocal8Bit().constData(), len);
#endif
}
