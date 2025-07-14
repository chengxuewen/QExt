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

#ifndef _QEXTLOGBINARYWRITTERAPPENDER_H
#define _QEXTLOGBINARYWRITTERAPPENDER_H

#include <qextLogAppenderSkeleton.h>

class QDataStream;

class QExtLogBinaryLayout;

class QEXT_LOGGING_API QExtLogBinaryWriterAppender : public QExtLogAppenderSkeleton
{
    Q_OBJECT
    Q_PROPERTY(QDataStream *writer READ writer WRITE setWriter)
public:
    QExtLogBinaryWriterAppender(QObject *parent = QEXT_NULLPTR);
    QExtLogBinaryWriterAppender(QDataStream *dataStream, QObject *parent = QEXT_NULLPTR);
    ~QExtLogBinaryWriterAppender() QEXT_OVERRIDE;

    bool requiresLayout() const QEXT_OVERRIDE;
    QDataStream *writer() const;

    void setWriter(QDataStream *dataStream);

    void activateOptions() QEXT_OVERRIDE;
    void close() QEXT_OVERRIDE;

protected:
    void append(const QExtLoggingEvent &event) QEXT_OVERRIDE;
    bool checkEntryConditions() const QEXT_OVERRIDE;

    void closeWriter();

    virtual bool handleIoErrors() const;
    void writeFooter() const;
    void writeHeader() const;

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogBinaryWriterAppender)
    void writeRawData(const QByteArray &data) const;
    void closeInternal();
    QExtLogBinaryLayout *binaryLayout() const;

    QDataStream *mWriter;
};

inline QDataStream *QExtLogBinaryWriterAppender::writer() const
{
    return mWriter;
}

#endif // _QEXTLOGBINARYWRITTERAPPENDER_H
