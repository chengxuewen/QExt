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

#ifndef _QEXTLOGAPPENDERATTACHABLE_H
#define _QEXTLOGAPPENDERATTACHABLE_H

#include <qextLogAppender.h>

#include <QReadWriteLock>
#include <QList>

/*!
 * \brief Implementation for attaching appenders to objects
 */
class QEXT_LOGGING_API QExtLogAppenderAttachable
{

public:
    QExtLogAppenderAttachable();
    virtual ~QExtLogAppenderAttachable();

    /*!
     * Add an appender.
     */
    virtual void addAppender(const QExtLogAppenderSharedPtr &appender);

    /**
     * @brief Get all previously added appenders as an Enumeration.
     */
    virtual QList<QExtLogAppenderSharedPtr> appenders() const;

    /*!
     * Get an appender by name.
     */
    virtual QExtLogAppenderSharedPtr appender(const QString &name) const;

    /*!
     Returns <code>true</code> if the specified appender is in the
     list of attached appenders, <code>false</code> otherwise.
    */
    virtual bool isAttached(const QExtLogAppenderSharedPtr &appender) const;

    /*!
     * Removes all appenders that have been previously added from this
     * QExtLogger.
     *
     * To allow configurators to collect events during the configuration
     * process ListAppenders with the configuratorList property set, will
     * not be removed.
     *
     * \sa LisAppender::setConfiguratorList()
     */
    virtual void removeAllAppenders();

    /*!
     * Remove the appender passed as parameter from the list of appenders.
     */
    virtual void removeAppender(const QExtLogAppenderSharedPtr &appender);

    /*!
     * Remove the appender with the name passed as parameter from the
     * list of appenders.
     */
    virtual void removeAppender(const QString &name);

protected:
    QList<QExtLogAppenderSharedPtr> mAppenders;
    mutable QReadWriteLock mAppenderGuard;
};

#endif // _QEXTLOGAPPENDERATTACHABLE_H
