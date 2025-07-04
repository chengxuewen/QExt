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

#include <qextBinaryLogStream.h>
#include <qextLogBinaryLogger.h>
#include <qextBinaryLoggingEvent.h>

#include <QByteArray>
#include <QPointer>

struct QExtLogBinaryStream::Stream
{
    Stream(const QExtLogger *logger, QExtLogLevel level)
        : logger(logger)
        , level(level)
    {
    }
    ~Stream();

    QByteArray buffer;
    QPointer<const QExtLogger> logger;
    QExtLogLevel level;
};

QExtLogBinaryStream::Stream::~Stream()
{
    if (const QExtBinaryLogger *blogger = qobject_cast<const QExtBinaryLogger *>(logger))
    {
        blogger->log(level, buffer);
    }
    else if (logger->isEnabledFor(level))
    {
        QExtBinaryLoggingEvent event(logger, level, buffer);
        logger->callAppenders(event);
    }
}

QExtLogBinaryStream::QExtLogBinaryStream(const QExtLogger *logger, QExtLogLevel level)
    : mStream(new Stream(logger, level))
{
}

QExtLogBinaryStream &QExtLogBinaryStream::operator<<(const QByteArray &data)
{
    mStream->buffer.append(data);
    return *this;
}
