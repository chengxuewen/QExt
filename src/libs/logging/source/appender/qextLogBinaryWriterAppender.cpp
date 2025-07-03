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

#include <qextLogBinaryWriterAppender.h>
#include <qextBinaryLoggingEvent.h>
#include <qextLogBinaryLayout.h>

#include <QDataStream>

QExtLogBinaryWriterAppender::QExtLogBinaryWriterAppender(QObject *parent) :
    QExtLogAppenderSkeleton(false, parent),
    mWriter(nullptr)
{
}

QExtLogBinaryWriterAppender::QExtLogBinaryWriterAppender(QDataStream *dataStream,
                                           QObject *parent) :
    QExtLogAppenderSkeleton(false, parent),
    mWriter(dataStream)
{
}

QExtLogBinaryWriterAppender::~QExtLogBinaryWriterAppender()
{
    closeInternal();
}

void QExtLogBinaryWriterAppender::setWriter(QDataStream *dataStream)
{
    QMutexLocker locker(&mObjectGuard);

    closeWriter();

    mWriter = dataStream;
    writeHeader();
}


void QExtLogBinaryWriterAppender::activateOptions()
{
    QMutexLocker locker(&mObjectGuard);

    if (writer() == nullptr)
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Activation of QExtLogAppender '%1' that requires writer and has no writer set"),
                                             QExtLogError::Error_AppenderActivateMissingWriter);
        e << name();
        logger()->error(e);
        return;
    }

    QExtLogAppenderSkeleton::activateOptions();
}

void QExtLogBinaryWriterAppender::close()
{
    closeInternal();
    QExtLogAppenderSkeleton::close();
}

void QExtLogBinaryWriterAppender::closeInternal()
{
    QMutexLocker locker(&mObjectGuard);

    if (isClosed())
        return;

    closeWriter();
}

bool QExtLogBinaryWriterAppender::requiresLayout() const
{
    return false;
}

void QExtLogBinaryWriterAppender::append(const QExtLoggingEvent &event)
{
    const auto *binEvent = dynamic_cast<const QExtBinaryLoggingEvent *>(&event);
    const QExtLogLayoutSharedPtr l = layout();
    const QExtLogBinaryLayout *bl = qobject_cast<QExtLogBinaryLayout *>(l.data());

    if (binEvent != nullptr)
    {
        // handle binary events
        if (bl != nullptr)
            *mWriter << bl->binaryFormat(*binEvent);   // if it's a binary message and we have a binary layout output the binary message via the binary layout.
        else
            *mWriter << binEvent->binaryMessage();     // binary message, but no layout or not a binary layout, output the binary message without the layout
    }
    else
    {
        // handle non binary events
        if ((l != nullptr) && (bl == nullptr))
            *mWriter << l->format(event); // if the message and the layout are not binary, output it as in QExtLogWriterAppender
        else
            *mWriter << event.message();  // if the message is not binary and there is no layout or the layout is binary, output it without the layout
    }

    handleIoErrors();
}

bool QExtLogBinaryWriterAppender::checkEntryConditions() const
{
    if (mWriter == nullptr)
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of appender '%1' without a writer set"),
                                             QExtLogError::Error_AppenderUseMissingWriter);
        e << name();
        logger()->error(e);
        return false;
    }

    return QExtLogAppenderSkeleton::checkEntryConditions();
}


void QExtLogBinaryWriterAppender::closeWriter()
{
    if (mWriter == nullptr)
        return;

    writeFooter();
    mWriter = nullptr;
}

bool QExtLogBinaryWriterAppender::handleIoErrors() const
{
    return false;
}

void QExtLogBinaryWriterAppender::writeHeader() const
{
    if ((layout() != nullptr) && (mWriter != nullptr))
        writeRawData(binaryLayout()->binaryHeader());
}

void QExtLogBinaryWriterAppender::writeFooter() const
{
    if ((layout() != nullptr) && (mWriter != nullptr))
        writeRawData(binaryLayout()->binaryFooter());
}

void QExtLogBinaryWriterAppender::writeRawData(const QByteArray &data) const
{
    if (data.isEmpty())
        return;

    mWriter->writeRawData(data.constData(), data.size());

    if (handleIoErrors())
        return;
}

QExtLogBinaryLayout *QExtLogBinaryWriterAppender::binaryLayout() const
{
    return qobject_cast<QExtLogBinaryLayout *>(layout().data());
}

// #include "moc_binarywriterappender.cpp"
