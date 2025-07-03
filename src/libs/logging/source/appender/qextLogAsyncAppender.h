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

#ifndef _QEXTLOGASYNCAPPENDER_H
#define _QEXTLOGASYNCAPPENDER_H

#include <qextLogAppenderSkeleton.h>
#include <qextLogAppenderAttachable.h>

class QExtLogDispatcher;

/*!
 * \brief The class QExtLogAsyncAppender lets users log events asynchronously.
 *
 * The QExtLogAsyncAppender will collect the events sent to it and then dispatch them to all the
 * appenders that are attached to it. You can attach multiple appenders to an QExtLogAsyncAppender.
 *
 * The QExtLogAsyncAppender uses a separate thread to serve the events fromthe event loop.
 *
 * \note All the functions declared in this class are thread-safe.
 * &nbsp;
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogAsyncAppender : public QExtLogAppenderSkeleton, public QExtLogAppenderAttachable
{
    Q_OBJECT

public:
    QExtLogAsyncAppender(QObject *parent = nullptr);
    ~QExtLogAsyncAppender() override;

    void close() override;
    void activateOptions() override;
    bool requiresLayout() const override;
    void callAppenders(const QExtLoggingEvent &event) const;

    /*!
     * Tests if all entry conditions for using append() in this class are
     * met.
     *
     * If a conditions is not met, an error is logged and the function
     * returns false. Otherwise the result of
     * QExtLogAppenderSkeleton::checkEntryConditions() is returned.
     *
     * The checked conditions are:
     * - dispatcher thread running (QExtLogError::Error_AppenderAsyncDispatcherNotRunning)
     *
     * The function is called as part of the checkEntryConditions() chain
     * started by QExtLogAppenderSkeleton::doAppend().
     *
     * \sa QExtLogAppenderSkeleton::doAppend(),
     *     QExtLogAppenderSkeleton::checkEntryConditions()
     */
    bool checkEntryConditions() const override;

protected:
    void append(const QExtLoggingEvent &event) override;

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogAsyncAppender)

    //! Event dispatcher trhead
    QThread *mThread;
    QExtLogDispatcher *mDispatcher;
    void closeInternal();
};

#endif // _QEXTLOGASYNCAPPENDER_H
