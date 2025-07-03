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

#include <qextLogLevel.h>
#include <qextOnceFlag.h>
#include <qextLogger.h>

#include <QCoreApplication>
#include <QDataStream>

QEXT_DECLARE_STATIC_LOGGER(qextLogLevelLogger, QExtLogLevel)

int QExtLogLevel::syslogEquivalent() const
{
    switch (mValue)
    {
    case Null:
    case All:
    case Trace:
    case Debug:
        return 7;
    case Info:
        return 6;
    case Warn:
        return 4;
    case Error:
        return 3;
    case Fatal:
    case Off:
        return 0;
    default:
        Q_ASSERT_X(false, "QExtLogLevel::syslogEquivalent()", "Unknown level value");
        return 7;
    }
}

QString QExtLogLevel::toString() const
{
    static const char *context = "QExtLogLevel";

    switch (mValue)
    {
    case Null:
    case All:
    case Trace:
    case Debug:
    case Info:
    case Warn:
    case Error:
    case Fatal:
    case Off:
        return QCoreApplication::translate(context, this->levelEnumString(mValue));
    default:
        Q_ASSERT_X(false, "QExtLogLevel::toString()", "Unknown level value");
        return QCoreApplication::translate(context, "NULL");
    }
}

const QList<int> &QExtLogLevel::levelEnumList()
{
    static QExtOnceFlag onceFlag;
    static QList<int> enumList;
    if (onceFlag.enter())
    {
        enumList.append(Null);
        enumList.append(All);
        enumList.append(Trace);
        enumList.append(Debug);
        enumList.append(Info);
        enumList.append(Warn);
        enumList.append(Error);
        enumList.append(Fatal);
        enumList.append(Off);
        onceFlag.leave();
    }
    return enumList;
}

const char *QExtLogLevel::levelEnumString(int level)
{
    switch (level)
    {
    case Null:
        return "NULL";
    case All:
        return "ALL";
    case Trace:
        return "TRACE";
    case Debug:
        return "DEBUG";
    case Info:
        return "INFO";
    case Warn:
        return "WARN";
    case Error:
        return "ERROR";
    case Fatal:
        return "FATAL";
    case Off:
        return "OFF";
    default:
        Q_ASSERT_X(false, "QExtLogLevel::levelEnumString()", "Unknown level value");
        break;
    }
    return "";
}

QExtLogLevel QExtLogLevel::fromString(const QString &level, bool *ok)
{
    const char *context = "QExtLogLevel";

    if (QEXT_NULLPTR != ok)
    {
        *ok = true;
    }
    const QList<int> &enumList = QExtLogLevel::levelEnumList();
    for (QList<int>::ConstIterator iter = enumList.cbegin(); iter < enumList.cend(); ++iter)
    {
        const char *levelString = QExtLogLevel::levelEnumString(*iter);
        if (level == levelString || level == QCoreApplication::translate(context, levelString))
        {
            return LevelEnum(*iter);
        }
    }
    if (QEXT_NULLPTR != ok)
    {
        *ok = false;
    }

    qextLogLevelLogger()->warn(QStringLiteral("Use of invalid level string '%1'. Using 'QExtLogLevel::Null' instead."),
                               level);
    return Null;
}

#ifndef QT_NO_DATASTREAM
QDataStream &operator<<(QDataStream &out, QExtLogLevel level)
{
    quint8 l = level.mValue;
    out << l;
    return out;
}

QDataStream &operator>>(QDataStream &in, QExtLogLevel &level)
{
    quint8 l;
    in >> l;
    level.mValue = static_cast<QExtLogLevel::LevelEnum>(l);
    return in;
}
#endif // QT_NO_DATASTREAM
