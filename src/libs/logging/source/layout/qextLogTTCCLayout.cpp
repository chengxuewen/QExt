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

#include <qextLogTTCCLayout.h>
#include <qextLogPatternFormatter.h>
#include <qextLoggingEvent.h>
#include <qextLogDatetime.h>
#include <qextLogger.h>

#include <QDateTime>

QExtLogTTCCLayout::QExtLogTTCCLayout(QObject *parent) :
    QExtLogLayout(parent),
    mCategoryPrefixing(true),
    mContextPrinting(true),
    mThreadPrinting(true)
{
    setDateFormat(RELATIVE);
}

QExtLogTTCCLayout::QExtLogTTCCLayout(const QString &dateFormat,
                                     QObject *parent) :
    QExtLogLayout(parent),
    mCategoryPrefixing(true),
    mContextPrinting(true),
    mThreadPrinting(true)
{
    setDateFormat(dateFormat);
}

QExtLogTTCCLayout::QExtLogTTCCLayout(DateFormat dateFormat,
                                     QObject *parent) :
    QExtLogLayout(parent),
    mCategoryPrefixing(true),
    mContextPrinting(true),
    mThreadPrinting(true)
{
    setDateFormat(dateFormat);
}

void QExtLogTTCCLayout::setDateFormat(DateFormat dateFormat)
{
    switch (dateFormat)
    {
    case NONE:
        setDateFormat(QStringLiteral("NONE"));
        break;
    case ISO8601:
        setDateFormat(QStringLiteral("ISO8601"));
        break;
    case ABSOLUTE:
        setDateFormat(QStringLiteral("ABSOLUTE"));
        break;
    case DATE:
        setDateFormat(QStringLiteral("DATE"));
        break;
    case RELATIVE:
        setDateFormat(QStringLiteral("RELATIVE"));
        break;
    default:
        Q_ASSERT_X(false, "QExtLogTTCCLayout::setDateFormat", "Unknown DateFormat");
        setDateFormat(QString());
    }
}


QString QExtLogTTCCLayout::format(const QExtLoggingEvent &event)
{
    Q_ASSERT_X(mPatternFormatter, "QExtLogTTCCLayout::format()", "mpPatternConverter must not be null");

    return mPatternFormatter->format(event);
}


void QExtLogTTCCLayout::updatePatternFormatter()
{
    QString pattern;

    pattern += QStringLiteral("%d{") +  mDateFormat + QStringLiteral("}");
    if (mThreadPrinting)
    {
        pattern += QStringLiteral(" [%t]");
    }
    pattern += QStringLiteral(" %-5p");
    if (mCategoryPrefixing)
    {
        pattern += QStringLiteral(" %c");
    }
    if (mContextPrinting)
    {
        pattern += QStringLiteral(" %x");
    }
    pattern += QStringLiteral(" - %m%n");

    mPatternFormatter.reset(new QExtLogPatternFormatter(pattern));
}
