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

#ifndef _QEXTLOGBINARYFILEAPPENDER_H
#define _QEXTLOGBINARYFILEAPPENDER_H

#include <qextLogBinaryWriterAppender.h>

#include <QDataStream>

class QFile;

class QEXT_LOGGING_API QExtLogBinaryFileAppender : public QExtLogBinaryWriterAppender
{
    Q_OBJECT
    Q_PROPERTY(bool appendFile READ appendFile WRITE setAppendFile)
    Q_PROPERTY(bool bufferedIo READ bufferedIo WRITE setBufferedIo)
    Q_PROPERTY(QString file READ file WRITE setFile)
    Q_PROPERTY(QDataStream::ByteOrder byteOrder READ byteOrder WRITE setByteOrder)
    Q_PROPERTY(QDataStream::FloatingPointPrecision floatingPointPrecision READ floatingPointPrecision WRITE setFloatingPointPrecision)
    Q_PROPERTY(QDataStream::Version streamVersion READ streamVersion WRITE setStreamVersion)

public:
    explicit QExtLogBinaryFileAppender(QObject *parent = nullptr);
    QExtLogBinaryFileAppender(const QString &fileName,
                       QObject *parent = nullptr);
    QExtLogBinaryFileAppender(const QString &fileName,
                       bool append,
                       QObject *parent = nullptr);
    QExtLogBinaryFileAppender(const QString &fileName,
                       bool append,
                       bool buffered,
                       QObject *parent = nullptr);
    virtual ~QExtLogBinaryFileAppender();

    // properties
    bool appendFile() const;
    void setAppendFile(bool append);
    bool bufferedIo() const;
    void setBufferedIo(bool buffered);
    QString file() const;
    void setFile(const QString &fileName);
    QDataStream::ByteOrder byteOrder() const;
    void setByteOrder(QDataStream::ByteOrder byteorder);
    QDataStream::FloatingPointPrecision floatingPointPrecision() const;
    void setFloatingPointPrecision(QDataStream::FloatingPointPrecision floatingpointprecision);
    QDataStream::Version streamVersion() const;
    void setStreamVersion(QDataStream::Version version);

    // public members
    void activateOptions() override;
    void close() override;

protected:
    bool checkEntryConditions() const override;
    bool handleIoErrors() const override;

    void closeFile();
    void openFile();
    bool removeFile(QFile &file) const;
    bool renameFile(QFile &file, const QString &fileName) const;

private:
    QExtLogBinaryFileAppender(const QExtLogBinaryFileAppender &other); // Not implemented
    QExtLogBinaryFileAppender &operator=(const QExtLogBinaryFileAppender &other); // Not implemented
    void createDataStream();

    volatile bool mAppendFile;
    volatile bool mBufferedIo;
    QString mFileName;
    QFile *mFile;
    QDataStream *mDataStream;
    QDataStream::ByteOrder mByteOrder;
    QDataStream::FloatingPointPrecision mFloatingPointPrecision;
    QDataStream::Version mStreamVersion;
    void closeInternal();
};

inline bool QExtLogBinaryFileAppender::appendFile() const
{
    return mAppendFile;
}

inline QString QExtLogBinaryFileAppender::file() const
{
    QMutexLocker locker(&mObjectGuard);
    return mFileName;
}

inline bool QExtLogBinaryFileAppender::bufferedIo() const
{
    return mBufferedIo;
}

inline void QExtLogBinaryFileAppender::setAppendFile(bool append)
{
    mAppendFile = append;
}

inline void QExtLogBinaryFileAppender::setBufferedIo(bool buffered)
{
    mBufferedIo = buffered;
}

inline void QExtLogBinaryFileAppender::setFile(const QString &fileName)
{
    QMutexLocker locker(&mObjectGuard);
    mFileName = fileName;
}

inline QDataStream::ByteOrder QExtLogBinaryFileAppender::byteOrder() const
{
    return mByteOrder;
}

inline void QExtLogBinaryFileAppender::setByteOrder(QDataStream::ByteOrder byteorder)
{
    mByteOrder = byteorder;
}

inline QDataStream::FloatingPointPrecision QExtLogBinaryFileAppender::floatingPointPrecision() const
{
    return mFloatingPointPrecision;
}

inline void QExtLogBinaryFileAppender::setFloatingPointPrecision(QDataStream::FloatingPointPrecision floatingpointprecision)
{
    mFloatingPointPrecision = floatingpointprecision;
}

inline QDataStream::Version QExtLogBinaryFileAppender::streamVersion() const
{
    return mStreamVersion;
}

inline void QExtLogBinaryFileAppender::setStreamVersion(QDataStream::Version version)
{
    mStreamVersion = version;
}

#endif // _QEXTLOGBINARYFILEAPPENDER_H
