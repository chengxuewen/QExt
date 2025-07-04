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

#include <qextLogBinaryFileAppender.h>
#include <qextBinaryLoggingEvent.h>
#include <qextLogLayout.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>

// if we are in WIN*
#ifdef Q_OS_WIN
#   include <windows.h>
#endif

QExtLogBinaryFileAppender::QExtLogBinaryFileAppender(QObject *parent) :
    QExtLogBinaryWriterAppender(parent),
    mAppendFile(false),
    mBufferedIo(true),
    mFileName(),
    mFile(QEXT_NULLPTR),
    mDataStream(QEXT_NULLPTR),
    mByteOrder(QDataStream::LittleEndian),
    mFloatingPointPrecision(QDataStream::DoublePrecision),
    mStreamVersion(QDataStream::Qt_5_3)
{
}

QExtLogBinaryFileAppender::QExtLogBinaryFileAppender(const QString &fileName, QObject *parent) :
    QExtLogBinaryWriterAppender(parent),
    mAppendFile(false),
    mBufferedIo(true),
    mFileName(fileName),
    mFile(QEXT_NULLPTR),
    mDataStream(QEXT_NULLPTR),
    mByteOrder(QDataStream::LittleEndian),
    mFloatingPointPrecision(QDataStream::DoublePrecision),
    mStreamVersion(QDataStream::Qt_5_3)
{
}

QExtLogBinaryFileAppender::QExtLogBinaryFileAppender(const QString &fileName, bool append, QObject *parent) :
    QExtLogBinaryWriterAppender(parent),
    mAppendFile(append),
    mBufferedIo(true),
    mFileName(fileName),
    mFile(QEXT_NULLPTR),
    mDataStream(QEXT_NULLPTR),
    mByteOrder(QDataStream::LittleEndian),
    mFloatingPointPrecision(QDataStream::DoublePrecision),
    mStreamVersion(QDataStream::Qt_5_3)
{
}

QExtLogBinaryFileAppender::QExtLogBinaryFileAppender(const QString &fileName, bool append, bool buffered,
                                                     QObject *parent) :
    QExtLogBinaryWriterAppender(parent),
    mAppendFile(append),
    mBufferedIo(buffered),
    mFileName(fileName),
    mFile(QEXT_NULLPTR),
    mDataStream(QEXT_NULLPTR),
    mByteOrder(QDataStream::LittleEndian),
    mFloatingPointPrecision(QDataStream::DoublePrecision),
    mStreamVersion(QDataStream::Qt_5_3)
{
}

QExtLogBinaryFileAppender::~QExtLogBinaryFileAppender()
{
    closeInternal();
}

void QExtLogBinaryFileAppender::activateOptions()
{
    QMutexLocker locker(&mObjectGuard);

    if (mFileName.isEmpty())
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Activation of QExtLogAppender '%1' that requires file "
                                                          "and has no file set"),
                                               QExtLogError::Error_AppenderActivateMissingFile);
        e << name();
        logger()->error(e);
        return;
    }
    closeFile();
    openFile();
    QExtLogBinaryWriterAppender::activateOptions();
}

void QExtLogBinaryFileAppender::close()
{
    closeInternal();
    QExtLogBinaryWriterAppender::close();
}

void QExtLogBinaryFileAppender::closeInternal()
{
    QMutexLocker locker(&mObjectGuard);

    if (isClosed())
    {
        return;
    }

    closeFile();
}

bool QExtLogBinaryFileAppender::checkEntryConditions() const
{
    if ((mFile == QEXT_NULLPTR) || (mDataStream == QEXT_NULLPTR))
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Use of appender '%1' without open file"),
                                               QExtLogError::Error_AppenderNoOpenFile);
        e << name();
        logger()->error(e);
        return false;
    }

    return QExtLogBinaryWriterAppender::checkEntryConditions();
}


void QExtLogBinaryFileAppender::closeFile()
{
    if (mFile != QEXT_NULLPTR)
    {
        logger()->debug(QStringLiteral("Closing file '%1' for appender '%2'"), mFile->fileName(), name());
    }

    setWriter(QEXT_NULLPTR);
    delete mDataStream;
    mDataStream = QEXT_NULLPTR;
    delete mFile;
    mFile = QEXT_NULLPTR;
}

bool QExtLogBinaryFileAppender::handleIoErrors() const
{
    if (mFile->error() == QFile::NoError)
    {
        return false;
    }

    QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Unable to write to file '%1' for appender '%2'"),
                                           QExtLogError::Error_AppenderWriteFileFailed);
    e << mFileName << name();
    e.addCausingError(QExtLogError(mFile->errorString(), mFile->error()));
    logger()->error(e);
    return true;
}

void QExtLogBinaryFileAppender::createDataStream()
{
    mDataStream = new QDataStream(mFile);
    mDataStream->setByteOrder(mByteOrder);
    mDataStream->setFloatingPointPrecision(mFloatingPointPrecision);
    mDataStream->setVersion(mStreamVersion);
}

void QExtLogBinaryFileAppender::openFile()
{
    Q_ASSERT_X(mFile == QEXT_NULLPTR && mDataStream == QEXT_NULLPTR, "QExtLogBinaryFileAppender::openFile()", "Opening file without closing previous file");

    QFileInfo file_info(mFileName);
    QDir parent_dir = file_info.dir();
    if (!parent_dir.exists())
    {
        logger()->trace(QStringLiteral("Creating missing parent directory for file %1"), mFileName);
        QString name = parent_dir.dirName();
        parent_dir.cdUp();
        parent_dir.mkdir(name);
    }

#ifdef Q_OS_WIN
    // Let windows resolve any environment variables included in the file path
    wchar_t buffer[MAX_PATH];
    if (ExpandEnvironmentStringsW(mFileName.toStdWString().c_str(), buffer, MAX_PATH))
    {
        mFileName = QString::fromWCharArray(buffer);
    }
#endif

    mFile = new QFile(mFileName);
    QFile::OpenMode mode = QIODevice::WriteOnly | QIODevice::Text;
    if (mAppendFile)
    {
        mode |= QIODevice::Append;
    }
    else
    {
        mode |= QIODevice::Truncate;
    }
    if (!mBufferedIo)
    {
        mode |= QIODevice::Unbuffered;
    }
    if (!mFile->open(mode))
    {
        QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Unable to open file '%1' for appender '%2'"),
                                               QExtLogError::Error_AppenderOpenFileFailed);
        e << mFileName << name();
        e.addCausingError(QExtLogError(mFile->errorString(), mFile->error()));
        logger()->error(e);
        return;
    }

    createDataStream();
    setWriter(mDataStream);
    logger()->debug(QStringLiteral("Opened file '%1' for appender '%2'"), mFile->fileName(), name());
}

bool QExtLogBinaryFileAppender::removeFile(QFile &file) const
{
    if (file.remove())
    {
        return true;
    }

    QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Unable to remove file '%1' for appender '%2'"),
                                           QExtLogError::Error_AppenderRemoveFileFailed);
    e << file.fileName() << name();
    e.addCausingError(QExtLogError(file.errorString(), file.error()));
    logger()->error(e);
    return false;
}

bool QExtLogBinaryFileAppender::renameFile(QFile &file,
                                           const QString &fileName) const
{
    logger()->debug(QStringLiteral("Renaming file '%1' to '%2'"), file.fileName(), fileName);
    if (file.rename(fileName))
    {
        return true;
    }

    QExtLogError e = QEXT_LOG_QCLASS_ERROR(QT_TR_NOOP("Unable to rename file '%1' to '%2' for appender '%3'"),
                                           QExtLogError::Error_AppenderRenameFileFailed);
    e << file.fileName() << fileName << name();
    e.addCausingError(QExtLogError(file.errorString(), file.error()));
    logger()->error(e);
    return false;
}
