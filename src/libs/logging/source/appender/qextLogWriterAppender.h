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

#ifndef _QEXTLOGWRITERAPPENDER_H
#define _QEXTLOGWRITERAPPENDER_H

#include <qextLogAppenderSkeleton.h>

#if QT_VERSION >= 0x060000
#include <QStringConverter>
#endif

#if QT_VERSION < 0x060000
class QTextCodec;
#endif

class QTextStream;

/*!
 * \brief The class QExtLogWriterAppender appends log events to a QTextStream.
 *
 * \note All the functions declared in this class are thread-safe.
 * &nbsp;
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogWriterAppender : public QExtLogAppenderSkeleton
{
    Q_OBJECT

    /*!
     * The property holds the codec the appender uses.
     *
     * The default is null to use the codec the writer has set.
     *
     * \sa encoding(), setEncoding()
     */
#if QT_VERSION < 0x060000
    Q_PROPERTY(QTextCodec *encoding READ encoding WRITE setEncoding)
#else
    Q_PROPERTY(QStringConverter::Encoding encoding READ encoding WRITE setEncoding)
#endif

    /*!
     * The property holds the writer the appender uses.
     *
     * \sa writer(), setWriter()
     */
    Q_PROPERTY(QTextStream *writer READ writer WRITE setWriter)

    /*!
     * The property holds, if the writer flushes after all write operations.
     *
     * The default is true for flushing.
     *
     * \sa immediateFlush(), setImmediateFlush()
     */
    Q_PROPERTY(bool immediateFlush READ immediateFlush WRITE setImmediateFlush)

public:
    QExtLogWriterAppender(QObject *parent = QEXT_NULLPTR);
    QExtLogWriterAppender(const QExtLogLayoutSharedPtr &layout,
                   QObject *parent = QEXT_NULLPTR);
    QExtLogWriterAppender(const QExtLogLayoutSharedPtr &layout,
                   QTextStream *textStream,
                   QObject *parent = QEXT_NULLPTR);
    ~QExtLogWriterAppender() override;

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogWriterAppender)

public:
    bool requiresLayout() const override;
#if QT_VERSION < 0x060000
    QTextCodec *encoding() const;
#else
    QStringConverter::Encoding encoding() const;
#endif
    bool immediateFlush() const;
    QTextStream *writer() const;

    /*!
     * Sets the codec used by the writer to \a pTextCoded.
     *
     * If a codec is set with setEncoding, it will overwrite the codec set
     * in the text stream. A subsequent call with \a pTextCoded equals null
     * will resets the codec to the default QTextCodec::codecForLocale().
     *
     * \sa encoding(), QTextSream::setCodec(), QTextCodec::codecForLocale()
     */
#if QT_VERSION < 0x060000
    void setEncoding(QTextCodec *encoding);
#else
    void setEncoding(QStringConverter::Encoding encoding);
#endif
    void setImmediateFlush(bool immediateFlush);
    void setWriter(QTextStream *textStream);

    void activateOptions() override;
    void close() override;

protected:
    void append(const QExtLoggingEvent &event) override;

    /*!
     * Tests if all entry conditions for using append() in this class are
     * met.
     *
     * If a conditions is not met, an error is logged and the function
     * returns false. Otherwise the result of
     * QExtLogAppenderSkeleton::checkEntryConditions() is returned.
     *
     * The checked conditions are:
     * - A writer has been set (QExtLogError::Error_AppenderUseMissingWriter)
     *
     * The function is called as part of the checkEntryConditions() chain
     * started by QExtLogAppenderSkeleton::doAppend().
     *
     * \sa QExtLogAppenderSkeleton::doAppend(),
     *     QExtLogAppenderSkeleton::checkEntryConditions()
     */
    bool checkEntryConditions() const override;

    void closeWriter();

    virtual bool handleIoErrors() const;
    void writeFooter() const;
    void writeHeader() const;

private:
#if QT_VERSION < 0x060000
    QTextCodec *mEncoding;
#else
    QStringConverter::Encoding mEncoding;
#endif
    QTextStream *mWriter;
    volatile bool mImmediateFlush;
    void closeInternal();
};

#if QT_VERSION < 0x060000
inline QTextCodec *QExtLogWriterAppender::encoding() const
{
    QMutexLocker locker(&mObjectGuard);
    return mEncoding;
}
#else
inline QStringConverter::Encoding QExtLogWriterAppender::encoding() const
{
    QMutexLocker locker(&mObjectGuard);
    return mEncoding;
}
#endif

inline bool QExtLogWriterAppender::immediateFlush() const
{
    return mImmediateFlush;
}

inline QTextStream *QExtLogWriterAppender::writer() const
{
    return mWriter;
}

inline void QExtLogWriterAppender::setImmediateFlush(bool immediateFlush)
{
    mImmediateFlush = immediateFlush;
}

#endif // _QEXTLOGWRITERAPPENDER_H
