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

#ifndef _QEXTLOGFILTER_H
#define _QEXTLOGFILTER_H

#include <qextLoggingGlobal.h>
#include <qextObjectSharedPointer.h>

#include <QObject>

class QExtLoggingEvent;
class QExtLogFilter;

using QExtLogFilterSharedPtr = QExtObjectSharedPointer<QExtLogFilter>;

/*!
 * \brief The class QExtLogFilter is the base class for all filters.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogFilter : public QObject
{
    Q_OBJECT

    /*!
     * The property holds the next filter of this filter.
     *
     * The default is 0 for no next filter.
     *
     *
     *
     * \sa next(), setNext()
     */
    Q_PROPERTY(QExtLogFilterSharedPtr next READ next WRITE setNext)

public:
    enum Decision
    {
        ACCEPT, /*!< The log event must be logged immediately without consulting
                     with the remaining filters, if any, in the chain. */
        DENY, /*!< The log event must be dropped immediately without consulting
                   with the remaining filters, if any, in the chain. */
        NEUTRAL /*!< This filter is neutral with respect to the log event. The
                   remaining filters, if any, should be consulted for a final decision. */
    };
    Q_ENUM(Decision)

public:
    QExtLogFilter(QObject *parent = QEXT_NULLPTR);
    virtual ~QExtLogFilter();

    QExtLogFilterSharedPtr next() const;
    void setNext(const QExtLogFilterSharedPtr &filter);

    virtual void activateOptions();
    virtual Decision decide(const QExtLoggingEvent &event) const = 0;

private:
    QExtLogFilterSharedPtr mNext;
};

#endif // _QEXTLOGFILTER_H
