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

#ifndef _QEXTLOGCONSOLEAPPENDER_H
#define _QEXTLOGCONSOLEAPPENDER_H

#include <qextLogWriterAppender.h>

class QTextStream;

/*!
 * \brief The class QExtLogConsoleAppender appends to stdout or stderr.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogConsoleAppender : public QExtLogWriterAppender
{
    Q_OBJECT

    /*!
     * The property holds the target used by the appender.
     *
     * The default is Target_Stdout for the standard output.
     *
     * \sa Target, target(), setTarget()
     */
    Q_PROPERTY(QString target READ target WRITE setTarget)

public:
    /*!
     * The enum defines the possible output targets
     *
     * \sa target(), setTarget()
     */
    enum TargetEnum
    {
        /*! The output target is standard out. */
        Target_Stdout,
        /*! The output target is standard error. */
        Target_Stderr
    };
    Q_ENUM(TargetEnum)


    QExtLogConsoleAppender(QObject *parent = QEXT_NULLPTR);
    QExtLogConsoleAppender(const QExtLogLayoutSharedPtr &layout, QObject *parent = QEXT_NULLPTR);
    QExtLogConsoleAppender(const QExtLogLayoutSharedPtr &layout, TargetEnum target, QObject *parent = QEXT_NULLPTR);
    QExtLogConsoleAppender(const QExtLogLayoutSharedPtr &layout, const QString &target, QObject *parent = QEXT_NULLPTR);
    ~QExtLogConsoleAppender() QEXT_OVERRIDE;

    QString target() const;
    void setTarget(const QString &target);

    /*!
     * Sets the target to the value specified by the \a target constant.
     */
    void setTarget(TargetEnum target);

    virtual void activateOptions() QEXT_OVERRIDE;
    virtual void close() QEXT_OVERRIDE;

protected:
    void closeStream();
    void append(const QExtLoggingEvent &event) QEXT_OVERRIDE;

private:
    volatile TargetEnum mTarget;
    QTextStream *mtextStream;
    void closeInternal();

    QEXT_DISABLE_COPY_MOVE(QExtLogConsoleAppender)
};

inline void QExtLogConsoleAppender::setTarget(TargetEnum target)
{
    mTarget = target;
}

#endif // _QEXTLOGCONSOLEAPPENDER_H
