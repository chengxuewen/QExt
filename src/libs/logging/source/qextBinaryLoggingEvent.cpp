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

#include <qextBinaryLoggingEvent.h>
#include <qextLogger.h>
#include <qextLogDatetime.h>

#ifndef QT_NO_DATASTREAM
#include <QDataStream>
#endif

static const char binMarker[] = "@@@ binary message @@@";

QExtBinaryLoggingEvent::QExtBinaryLoggingEvent() = default;

QExtBinaryLoggingEvent::QExtBinaryLoggingEvent(const QExtLogger *logger, QExtLogLevel level, const QByteArray &message)
    : QExtLoggingEvent(logger, level, QString(binMarker))
    , mBinaryMessage(message)
{
}

QExtBinaryLoggingEvent::QExtBinaryLoggingEvent(const QExtLogger *logger, QExtLogLevel level, const QByteArray &message, qint64 timeStamp)
    : QExtLoggingEvent(logger, level, QString(binMarker), timeStamp)
    , mBinaryMessage(message)
{
}

QExtBinaryLoggingEvent::QExtBinaryLoggingEvent(const QExtLogger *logger, QExtLogLevel level, const QByteArray &message, const QString &ndc, const QHash<QString, QString> &properties, const QString &threadName, qint64 timeStamp)
    : QExtLoggingEvent(logger, level, QString(binMarker), ndc, properties, threadName, timeStamp)
    , mBinaryMessage(message)
{
}

QByteArray QExtBinaryLoggingEvent::binaryMessage() const
{
    return mBinaryMessage;
}

QString QExtBinaryLoggingEvent::toString() const
{
    return level().toString() + QLatin1Char(':') + mBinaryMessage.toHex();
}

QString QExtBinaryLoggingEvent::binaryMarker()
{
    return binMarker;
}

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &out, const QExtBinaryLoggingEvent &loggingEvent)
{
    out << static_cast<const QExtLoggingEvent &>(loggingEvent);
    out << loggingEvent.mBinaryMessage;
    return out;
}

QDataStream &operator>>(QDataStream &in, QExtBinaryLoggingEvent &loggingEvent)
{
    in >> static_cast<QExtLoggingEvent &>(loggingEvent);
    in >> loggingEvent.mBinaryMessage;
    return in;
}
#endif // QT_NO_DATASTREAM
