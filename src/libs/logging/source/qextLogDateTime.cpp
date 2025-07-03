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

#include <qextLogDatetime.h>
#include <qextLogInitialisationHelper.h>

QExtLogDateTime::QExtLogDateTime() = default;

QExtLogDateTime::~QExtLogDateTime() = default;

QExtLogDateTime::QExtLogDateTime(const QExtLogDateTime &other) = default;

QString QExtLogDateTime::toString(const QString &format) const
{
    if (format.isEmpty())
        return QString();
    if (!isValid())
        return QString();

    if (format == QStringLiteral("NONE"))
        return QString();
    if (format == QStringLiteral("RELATIVE"))
        return QString::number(toMSecsSinceEpoch() - QExtLogInitialisationHelper::startTime());
    if (format == QStringLiteral("ISO8601"))
        return formatDateTime(QStringLiteral("yyyy-MM-dd hh:mm:ss.zzz"));
    if (format == QStringLiteral("ABSOLUTE"))
        return formatDateTime(QStringLiteral("HH:mm:ss.zzz"));
    if (format == QStringLiteral("DATE"))
        return formatDateTime(QStringLiteral("dd MM yyyy HH:mm:ss.zzz"));

    return formatDateTime(format);
}

QString QExtLogDateTime::formatDateTime(const QString &format) const
{
    return QDateTime::toString(format);
}
