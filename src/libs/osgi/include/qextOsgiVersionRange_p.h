/****************************************************************************
** Library: QTK
**
** Copyright (c) German Cancer Research Center,
**     Division of Medical and Biological Informatics
** Copyright (c) chengxuewen <1398831004@qq.com>
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
** http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
****************************************************************************/

#ifndef QTKVERSIONRANGE_P_H
#define QTKVERSIONRANGE_P_H

#include "qtkversion.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 *
 * Class representing QTK version ranges.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKVersionRange
{
public:
    /**
     * @brief QTKVersionRange
     * Construct a ctkVersionRange object.
     * Format for a range:
     *   ( "(" | "[" ) LOW_VERSION ","  HIGH_VERSION ( ")" | "]" )
     * Format for at least a version:
     *   VERSION
     *
     * @param strVersion Input string.
     */
    QTKVersionRange(const QString &strVersion);

    /**
     * @brief QTKVersionRange
     * Construct the default ctkVersionRange object.
     */
    QTKVersionRange();
    ~QTKVersionRange();

    /**
     * @brief defaultVersionRange
     * The empty version range "[0.0.0,inf)".
     * @return
     */
    static QTKVersionRange defaultVersionRange();

    bool isSpecified() const;

    /**
     * @brief withinRange
     * Check if specified version is within our range.
     *
     * @param version ctkVersion to compare to.
     * @return Return true if within range, otherwise false.
     */
    bool withinRange(const QTKVersion &version) const;

    /**
     * @brief withinRange
     * Check if objects range is within another ctkVersionRange.
     *
     * @param range ctkVersionRange to compare to.
     * @return Return true if within range, otherwise false.
     */
    bool withinRange(const QTKVersionRange &range) const;

    /**
     * @brief compare
     * Compare object to another ctkVersionRange. VersionRanges are compared on the
     * lower bound.
     *
     * @param obj ctkVersionRange to compare to.
     * @return Return 0 if equals, negative if this object is less than obj
     *         and positive if this object is larger then obj.
     * @exception ClassCastException if object is not a ctkVersionRange object.
     */
    int compare(const QTKVersionRange &obj) const;

    /**
     * @brief toString
     * String with version number. If version is not specified return
     * an empty string.
     *
     * @return QString.
     */
    QString toString() const;

    /**
     * @brief operator ==
     * Check if object is equal to this object.
     *
     * @param range Package entry to compare to.
     * @return true if equal, otherwise false.
     */
    bool operator==(const QTKVersionRange &range) const;

private:
    QTKVersion m_low;
    QTKVersion m_high;
    bool m_bLowIncluded;
    bool m_bHighIncluded;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKVERSIONRANGE_P_H
