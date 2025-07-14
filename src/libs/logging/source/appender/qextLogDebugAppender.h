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

#ifndef _QEXTLOGDEBUGAPPENDER_H
#define _QEXTLOGDEBUGAPPENDER_H

#include <qextLogAppenderSkeleton.h>

/*!
 * \brief The class QExtLogDebugAppender appends logging events to the platform
 *        specific debug output.
 *
 * A QExtLogDebugAppender appends to the Debugger on Windows and to stderr on all
 * other systems.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogDebugAppender : public QExtLogAppenderSkeleton
{
    Q_OBJECT

public:
    /*!
     * Creates a QExtLogDebugAppender.
     */
    QExtLogDebugAppender(QObject *parent = QEXT_NULLPTR);

    /*!
     * Creates a QExtLogDebugAppender with the specified layout \a pLayout
     */
    QExtLogDebugAppender(const QExtLogLayoutSharedPtr &layout,
                  QObject *parent = QEXT_NULLPTR);

private:
    QEXT_DISABLE_COPY_MOVE(QExtLogDebugAppender)

public:
    /*!
     * The DebugAppended requires a layout. The function returns true.
     *
     * \sa setLayout()
     */
    bool requiresLayout() const QEXT_OVERRIDE;

protected:
    /*!
     * Appends the specified logging event \a event to the debug output.
     * The output is formatted using the appender's layout.
     *
     * The method is called by the QExtLogAppenderSkeleton::doAppend() after it
     * the entry conditions have been tested and it has been found that the
     * logging event needs to be appended.
     *
     * \sa setLayout(), QExtLogAppenderSkeleton::doAppend(), checkEntryConditions()
     */
    void append(const QExtLoggingEvent &event) QEXT_OVERRIDE;

};

inline QExtLogDebugAppender::QExtLogDebugAppender(QObject *parent) :
    QExtLogAppenderSkeleton(parent)
{}

#endif // _QEXTLOGDEBUGAPPENDER_H
