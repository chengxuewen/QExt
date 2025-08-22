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

#ifndef _QEXTLOGAPPENDER_H
#define _QEXTLOGAPPENDER_H

#include <qextLogClassLogger.h>
#include <qextLogLayout.h>
#include <qextLogFilter.h>

class QExtLoggingEvent;

/*!
 * \brief The class QExtLogAppender is the base class for all Appenders.
 *
 * To allow the whole hirarchy to be an ascendant of QObject QExtLogAppender is
 * not an interface.
 *
 * \note All the functions declared in this class are thread-safe.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogAppender : public QObject
{
    Q_OBJECT

    /*!
     * The property holds the QExtLogLayout used by the QExtLogAppender.
     *
     * \sa layout(), setLayout()
     */
    Q_PROPERTY(QExtLogLayoutSharedPtr layout READ layout WRITE setLayout)

    /*!
     * The property holds the name of the QExtLogAppender.
     *
     * \sa name(), setName()
     */
    Q_PROPERTY(QString name READ name WRITE setName)

    /*!
     * The property holds if the QExtLogAppender requires a QExtLogLayout or not.
     *
     * \sa requiresLayout(), setRequiresLayout()
     */
    Q_PROPERTY(bool requiresLayout READ requiresLayout)

public:
    QExtLogAppender(QObject *parent = QEXT_NULLPTR);
    virtual ~QExtLogAppender();

    virtual QExtLogFilterSharedPtr filter() const = 0;
    virtual QString name() const = 0;
    virtual QExtLogLayoutSharedPtr layout() const = 0;
    virtual bool requiresLayout() const = 0;
    virtual void setLayout(const QExtLogLayoutSharedPtr &layout) = 0;
    virtual void setName(const QString &name) = 0;

    virtual void addFilter(const QExtLogFilterSharedPtr &filter) = 0;
    virtual void clearFilters() = 0;
    virtual void close() = 0;
    virtual void doAppend(const QExtLoggingEvent &event) = 0;

protected:
    /*!
     * Returns a pointer to a QExtLogger named after of the object.
     *
     * \sa QExtLogger::logger()
     */
    QExtLogger *logger() const;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtLogAppender)
    mutable QExtClassLogger mClassLogger;
};

using QExtLogAppenderSharedPtr = QExtObjectSharedPointer<QExtLogAppender>;

#endif // _QEXTLOGAPPENDER_H
