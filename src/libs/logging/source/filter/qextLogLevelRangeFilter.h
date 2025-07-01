/******************************************************************************
 *
 * This file is part of Log4Qt library.
 *
 * Copyright (C) 2007 - 2020 Log4Qt contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef LOG4QT_LEVELRANGEFILTER_H
#define LOG4QT_LEVELRANGEFILTER_H

#include <qextLogFilter.h>
#include <qextLogLevel.h>

namespace Log4Qt
{

/*!
 * \brief The class LevelMatchFilter allows logging events with levels in a
 *        specified range.
 *
 * \note The ownership and lifetime of objects of this class are managed.
 *       See \ref Ownership "Object ownership" for more details.
 */
class QEXT_LOGGING_API LevelRangeFilter : public Filter
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
     * The default is QExtLogLevel::OFF_INT.
     *
     * \sa levelMax(), setLevelMax()
     */
    Q_PROPERTY(QExtLogLevel levelMax READ levelMax WRITE setLevelMax)

    /*!
         * The property holds the minimum level of the range for this filter.
         *
         * The default is QExtLogLevel::NULL_INT.
         *
         * \sa levelMin(), setLevelMin()
         */
    Q_PROPERTY(QExtLogLevel levelMin READ levelMin WRITE setLevelMin)

public:
    LevelRangeFilter(QObject *parent = nullptr);

    bool acceptOnMatch() const;
    QExtLogLevel levelMax() const;
    QExtLogLevel levelMin() const;
    void setAcceptOnMatch(bool accept);
    void setLevelMax(QExtLogLevel level);
    void setLevelMin(QExtLogLevel level);

    Decision decide(const LoggingEvent &event) const override;

private:
    bool mAcceptOnMatch;
    QExtLogLevel mLevelMin;
    QExtLogLevel mLevelMax;
};

inline bool LevelRangeFilter::acceptOnMatch() const
{
    return mAcceptOnMatch;
}

inline QExtLogLevel LevelRangeFilter::levelMax() const
{
    return mLevelMax;
}

inline QExtLogLevel LevelRangeFilter::levelMin() const
{
    return mLevelMin;
}

inline void LevelRangeFilter::setAcceptOnMatch(bool accept)
{
    mAcceptOnMatch = accept;
}

inline void LevelRangeFilter::setLevelMax(QExtLogLevel level)
{
    mLevelMax = level;
}

inline void LevelRangeFilter::setLevelMin(QExtLogLevel level)
{
    mLevelMin = level;
}

} // namespace Log4Qt

#endif // LOG4QT_LEVELRANGEFILTER_H
