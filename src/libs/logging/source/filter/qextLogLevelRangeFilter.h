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

#ifndef _QEXTLOGLEVELRANGEFILTER_H
#define _QEXTLOGLEVELRANGEFILTER_H

#include <qextLogFilter.h>
#include <qextLogLevel.h>

/*!
 * \brief The class QExtLogLevelMatchFilter allows logging events with levels in a
 *        specified range.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API QExtLogLevelRangeFilter : public QExtLogFilter
{
    Q_OBJECT

    /*!
         * The property holds if an event is accpeted on a match.
         *
         * The default is true.
         *
         * \sa acceptOnMatch(), acceptOnMatch()
         */
    Q_PROPERTY(bool acceptOnMatch READ acceptOnMatch WRITE setAcceptOnMatch)

    /*!
     * The property holds the maximum level of the range for this filter.
     *
     * The default is QExtLogLevel::Off.
     *
     * \sa levelMax(), setLevelMax()
     */
    Q_PROPERTY(QExtLogLevel levelMax READ levelMax WRITE setLevelMax)

    /*!
         * The property holds the minimum level of the range for this filter.
         *
         * The default is QExtLogLevel::Null.
         *
         * \sa levelMin(), setLevelMin()
         */
    Q_PROPERTY(QExtLogLevel levelMin READ levelMin WRITE setLevelMin)

public:
    QExtLogLevelRangeFilter(QObject *parent = nullptr);

    bool acceptOnMatch() const;
    QExtLogLevel levelMax() const;
    QExtLogLevel levelMin() const;
    void setAcceptOnMatch(bool accept);
    void setLevelMax(QExtLogLevel level);
    void setLevelMin(QExtLogLevel level);

    Decision decide(const QExtLoggingEvent &event) const override;

private:
    bool mAcceptOnMatch;
    QExtLogLevel mLevelMin;
    QExtLogLevel mLevelMax;
};

inline bool QExtLogLevelRangeFilter::acceptOnMatch() const
{
    return mAcceptOnMatch;
}

inline QExtLogLevel QExtLogLevelRangeFilter::levelMax() const
{
    return mLevelMax;
}

inline QExtLogLevel QExtLogLevelRangeFilter::levelMin() const
{
    return mLevelMin;
}

inline void QExtLogLevelRangeFilter::setAcceptOnMatch(bool accept)
{
    mAcceptOnMatch = accept;
}

inline void QExtLogLevelRangeFilter::setLevelMax(QExtLogLevel level)
{
    mLevelMax = level;
}

inline void QExtLogLevelRangeFilter::setLevelMin(QExtLogLevel level)
{
    mLevelMin = level;
}

#endif // _QEXTLOGLEVELRANGEFILTER_H
