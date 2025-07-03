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

#include <qextLogWriterAppender.h>

#include <qextLogLayout.h>
#include <qextLoggingEvent.h>

#if QT_VERSION < 0x060000
#include <QTextCodec>
#endif

QExtLogWriterAppender::QExtLogWriterAppender(QObject *parent) :
    QExtLogAppenderSkeleton(false, parent),
#if QT_VERSION < 0x060000
    mEncoding(nullptr),
#else
    mEncoding(QStringConverter::Encoding::Utf8),
#endif
    mWriter(nullptr),
    mImmediateFlush(true)
{
}

QExtLogWriterAppender::QExtLogWriterAppender(const QExtLogLayoutSharedPtr &layout,
                               QObject *parent) :
    QExtLogAppenderSkeleton(false, layout, parent),
#if QT_VERSION < 0x060000
    mEncoding(nullptr),
#else
    mEncoding(QStringConverter::Encoding::System),
#endif
    mWriter(nullptr),
    mImmediateFlush(true)
{
}


QExtLogWriterAppender::QExtLogWriterAppender(const QExtLogLayoutSharedPtr &layout,
                               QTextStream *textStream,
                               QObject *parent) :
    QExtLogAppenderSkeleton(false, layout, parent),
#if QT_VERSION < 0x060000
    mEncoding(nullptr),
#else
    mEncoding(QStringConverter::Encoding::System),
#endif
    mWriter(textStream),
    mImmediateFlush(true)
{
}

QExtLogWriterAppender::~QExtLogWriterAppender()
{
    closeInternal();
}

#if QT_VERSION < 0x060000
void QExtLogWriterAppender::setEncoding(QTextCodec *encoding)
#else
void QExtLogWriterAppender::setEncoding(QStringConverter::Encoding encoding)
#endif
{
    QMutexLocker locker(&mObjectGuard);
    if (mEncoding == encoding)
        return;

    mEncoding = encoding;
    if (mWriter != nullptr)
    {
#if QT_VERSION < 0x060000
        if (mEncoding != nullptr)
            mWriter->setCodec(mEncoding);
#else
        mWriter->setEncoding(mEncoding);
#endif
    }
}

void QExtLogWriterAppender::setWriter(QTextStream *textStream)
{
    QMutexLocker locker(&mObjectGuard);

    closeWriter();

    mWriter = textStream;
#if QT_VERSION < 0x060000
    if ((mEncoding != nullptr) && (mWriter != nullptr))
        mWriter->setCodec(mEncoding);
#else
    if (mWriter != nullptr)
        mWriter->setEncoding(mEncoding);
#endif
    writeHeader();
}

void QExtLogWriterAppender::activateOptions()
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

void QExtLogWriterAppender::close()
{
    closeInternal();
    QExtLogAppenderSkeleton::close();
}

void QExtLogWriterAppender::closeInternal()
{
    QMutexLocker locker(&mObjectGuard);

    if (isClosed())
        return;

    closeWriter();
}

bool QExtLogWriterAppender::requiresLayout() const
{
    return true;
}

void QExtLogWriterAppender::append(const QExtLoggingEvent &event)
{
    Q_ASSERT_X(layout(), "QExtLogWriterAppender::append()", "QExtLogLayout must not be null");

    QString message(layout()->format(event));

    *mWriter << message;
    if (handleIoErrors())
        return;

    if (immediateFlush())
    {
        mWriter->flush();
        if (handleIoErrors())
            return;
    }
}

bool QExtLogWriterAppender::checkEntryConditions() const
{
    if (writer() == nullptr)
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of appender '%1' without a writer set"),
                                         QExtLogError::Error_AppenderUseMissingWriter);
        e << name();
        logger()->error(e);
        return false;
    }

    return QExtLogAppenderSkeleton::checkEntryConditions();
}

void QExtLogWriterAppender::closeWriter()
{
    if (mWriter == nullptr)
        return;

    writeFooter();
    mWriter = nullptr;
}

bool QExtLogWriterAppender::handleIoErrors() const
{
    return false;
}

void QExtLogWriterAppender::writeFooter() const
{
    if (!layout() || (mWriter == nullptr))
        return;

    QString footer = layout()->footer();
    if (footer.isEmpty())
        return;

    *mWriter << footer << QExtLogLayout::endOfLine();
    if (handleIoErrors())
        return;
}

void QExtLogWriterAppender::writeHeader() const
{
    if (!layout() || (mWriter == nullptr))
        return;

    QString header = layout()->header();
    if (header.isEmpty())
        return;

    *mWriter << header << QExtLogLayout::endOfLine();
    if (handleIoErrors())
        return;
}

// #include "moc_writerappender.cpp"
