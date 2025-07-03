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

#include <qextQMLLogger.h>
#include <qextLogLevel.h>
#include <qextLogger.h>

#include <QStringBuilder>
#include <QTimer>

QExtQmlLogger::QExtQmlLogger(QObject *parent) :
    QObject(parent)
    , mContext(QStringLiteral("Qml"))
    , mLogger(nullptr)
{
}

void QExtQmlLogger::trace(const QString &message) const
{
    logger()->trace(message);
}

void QExtQmlLogger::debug(const QString &message) const
{
    logger()->debug(message);
}

void QExtQmlLogger::info(const QString &message) const
{
    logger()->info(message);
}

void QExtQmlLogger::error(const QString &message) const
{
    logger()->error(message);
}

void QExtQmlLogger::fatal(const QString &message) const
{
    logger()->fatal(message);
}

void QExtQmlLogger::log(LevelEnum level, const QString &message) const
{
    QExtLogLevel loglevel(static_cast<QExtLogLevel::LevelEnum>(level));
    logger()->log(loglevel, message);
}

QString QExtQmlLogger::name() const
{
    return mName;
}

void QExtQmlLogger::setName(const QString &name)
{
    if (mName != name)
    {
        mName = name;
        Q_EMIT nameChanged(name);
    }
}

QString QExtQmlLogger::context() const
{
    return mContext;
}

QExtQmlLogger::LevelEnum QExtQmlLogger::level() const
{
    return static_cast<QExtQmlLogger::LevelEnum>(mLogger->level().toInt());
}

void QExtQmlLogger::setContext(const QString &context)
{
    if (mContext != context)
    {
        mContext = context;
        Q_EMIT contextChanged(context);
    }
}

void QExtQmlLogger::setLevel(QExtQmlLogger::LevelEnum level)
{
    if (this->level() != level)
    {
        mLogger->setLevel(QExtLogLevel(static_cast<QExtLogLevel::LevelEnum>(level)));
        Q_EMIT levelChanged(level);
    }
}

QString QExtQmlLogger::loggename() const
{
    if (mName.isEmpty() && (parent() != nullptr))
        mName = parent()->objectName();

    if (!mContext.isEmpty())
        return mContext % "." % mName;
    return mName;
}

QExtLogger *QExtQmlLogger::logger() const
{
    if (mLogger == nullptr)
        mLogger = QExtLogger::logger(loggename());

    return  mLogger;
}

// #include "moc_qmllogger.cpp"
