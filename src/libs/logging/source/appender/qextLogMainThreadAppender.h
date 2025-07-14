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

#ifndef _QEXTLOGMAINTHREADAPPENDER_H
#define _QEXTLOGMAINTHREADAPPENDER_H

#include <qextLogAppenderSkeleton.h>
#include <qextLogAppenderAttachable.h>

/*!
 * \brief The class QExtLogMainThreadAppender uses the QEvent system to write
 *        log from not main threads within the main thread.
 *
 *
 * \note All the functions declared in this class are thread-safe.
 * &nbsp;
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogMainThreadAppender : public QExtLogAppenderSkeleton, public QExtLogAppenderAttachable
{
    Q_OBJECT

public:
    QExtLogMainThreadAppender(QObject *parent = QEXT_NULLPTR);

    bool requiresLayout() const QEXT_OVERRIDE;

    void activateOptions() QEXT_OVERRIDE;

    /*!
     * Tests if all entry conditions for using append() in this class are
     * met.
     *
     * If a conditions is not met, an error is logged and the function
     * returns false. Otherwise the result of
     * QExtLogAppenderSkeleton::checkEntryConditions() is returned.
     *
     * The checked conditions are:
     * - none
     *
     * The function is called as part of the checkEntryConditions() chain
     * started by QExtLogAppenderSkeleton::doAppend().
     *
     * \sa QExtLogAppenderSkeleton::doAppend(),
     *     QExtLogAppenderSkeleton::checkEntryConditions()
     */
    bool checkEntryConditions() const QEXT_OVERRIDE;

protected:
    void append(const QExtLoggingEvent &event) QEXT_OVERRIDE;

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogMainThreadAppender)

};

#endif // _QEXTLOGMAINTHREADAPPENDER_H
