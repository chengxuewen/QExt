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

#ifndef _QEXTLOGFILEAPPENDER_H
#define _QEXTLOGFILEAPPENDER_H

#include <qextLogWriterAppender.h>

class QFile;
class QTextStream;

/*!
 * \brief The class QExtLogFileAppender appends log events to a file.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \note The ownership and lifetime of objects of this class are managed. See
 *       \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogFileAppender : public QExtLogWriterAppender
{
    Q_OBJECT

    /*!
     * The property holds, if the output is appended to the file.
     *
     * The default is false for not appending.
     *
     * \sa appendFile(), setAppendFile()
     */
    Q_PROPERTY(bool appendFile READ appendFile WRITE setAppendFile)

    /*!
     * The property holds, if the output is buffered.
     *
     * The default is true for buffering.
     *
     * \sa bufferedIo(), setBufferedIo()
     */
    Q_PROPERTY(bool bufferedIo READ bufferedIo WRITE setBufferedIo)

    /*!
     * The property holds the name of the file.
     *
     * \sa file(), setFile()
     */
    Q_PROPERTY(QString file READ file WRITE setFile)

public:
    explicit QExtLogFileAppender(QObject *parent = QEXT_NULLPTR);
    QExtLogFileAppender(const QExtLogLayoutSharedPtr &layout,
                 const QString &fileName,
                 QObject *parent = QEXT_NULLPTR);
    QExtLogFileAppender(const QExtLogLayoutSharedPtr &layout,
                 const QString &fileName,
                 bool append,
                 QObject *parent = QEXT_NULLPTR);
    QExtLogFileAppender(const QExtLogLayoutSharedPtr &layout,
                 const QString &fileName,
                 bool append,
                 bool buffered,
                 QObject *parent = QEXT_NULLPTR);
    ~QExtLogFileAppender() QEXT_OVERRIDE;

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogFileAppender)

public:
    bool appendFile() const;
    QString file() const;
    bool bufferedIo() const;
    void setAppendFile(bool append);
    void setBufferedIo(bool buffered);
    void setFile(const QString &fileName);

    void activateOptions() QEXT_OVERRIDE;
    void close() QEXT_OVERRIDE;

protected:
    /*!
     * Tests if all entry conditions for using append() in this class are met.
     *
     * If a conditions is not met, an error is logged and the function returns
     * false. Otherwise the result of QExtLogWriterAppender::checkEntryConditions()
     * is returned.
     *
     * The checked conditions are:
     * - That a file is set and open (QExtLogError::Error_AppenderNoOpenFile)
     *
     * The function is called as part of the checkEntryConditions() chain
     * started by QExtLogAppenderSkeleton::doAppend().
     *
     * \sa QExtLogAppenderSkeleton::doAppend(), QExtLogAppenderSkeleton::checkEntryConditions()
     */
    bool checkEntryConditions() const QEXT_OVERRIDE;

    void closeFile();

    /*!
     * Checks for file I/O errrors. If an error is found it is logged and the
     * function returns true. Otherwise false is returned.
     */
    bool handleIoErrors() const QEXT_OVERRIDE;

    /*!
     * Opens the file for the appender based on the specified file name and
     * mode. A text stream is created and passed on to the super class
     * QExtLogWriterAppender.
     *
     * If the parent directory of the specified file does not exists,
     * it is created.
     */
    virtual void openFile();

    /*!
     * Removes the file \a file. If the operation is successful, true is
     * returned. Otherwise an QExtLogError::Error_AppenderRemoveFileFailed error is logged
     * and false is returned.
     */
    bool removeFile(QFile &file) const;

    /*!
     * Renames the file \a file to \a fileName. If the operation is
     * successful, true is returned. Otherwise an
     * QExtLogError::Error_AppenderRenameFileFailed error is logged and false is returned.
     */
    bool renameFile(QFile &file,
                    const QString &fileName) const;

private:
    volatile bool mAppendFile;
    volatile bool mBufferedIo;
    QString mFileName;
    QFile *mFile;
    QTextStream *mTextStream;
    void closeInternal();
};

inline bool QExtLogFileAppender::appendFile() const
{
    return mAppendFile;
}

inline QString QExtLogFileAppender::file() const
{
    QMutexLocker locker(&mObjectGuard);
    return mFileName;
}

inline bool QExtLogFileAppender::bufferedIo() const
{
    return mBufferedIo;
}

inline void QExtLogFileAppender::setAppendFile(bool append)
{
    mAppendFile = append;
}

inline void QExtLogFileAppender::setBufferedIo(bool buffered)
{
    mBufferedIo = buffered;
}

inline void QExtLogFileAppender::setFile(const QString &fileName)
{
    QMutexLocker locker(&mObjectGuard);
    mFileName = fileName;
}

#endif // _QEXTLOGFILEAPPENDER_H
