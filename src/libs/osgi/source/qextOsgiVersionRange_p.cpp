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

#include "qtkversionrange_p.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * Construct a QTKVersionRange object.
 * Format for a range:
 *   ( "(" | "[" ) LOW_VERSION ","  HIGH_VERSION ( ")" | "]" )
 * Format for at least a version:
 *   VERSION
 *
 * @param vr Input string.
 */
QTKVersionRange::QTKVersionRange(const QString &strVersion)
{
    bool bOp = strVersion.startsWith("(");
    bool bOb = strVersion.startsWith("[");

    if (bOp || bOb) {
        bool bCp = strVersion.endsWith(")");
        bool bCb = strVersion.endsWith("]");
        int iComma = strVersion.indexOf(',');

        if (iComma > 0 && (bCp || bCb)) {
            m_low = QTKVersion(strVersion.mid(1, iComma-1).trimmed());
            m_high = QTKVersion(strVersion.mid(iComma+1, strVersion.length()-iComma-2).trimmed());
            m_bLowIncluded = bOb;
            m_bHighIncluded = bCb;
        } else {
            throw QTKInvalidArgumentException("Illegal version range: " + strVersion);
        }
    } else {
        m_low = QTKVersion(strVersion);
        m_high = QTKVersion();
        m_bLowIncluded = true;
        m_bHighIncluded = false;
    }
}

/**
 * Construct the default QTKVersionRange object.
 *
 */
QTKVersionRange::QTKVersionRange()
{
    m_low = QTKVersion(QTKVersion::emptyVersion());
    m_high = QTKVersion();
    m_bLowIncluded = true;
    m_bHighIncluded = false;
}

QTKVersionRange::~QTKVersionRange()
{

}

/**
 * The empty version range "[0.0.0,inf)".
 */
QTKVersionRange QTKVersionRange::defaultVersionRange()
{
    static QTKVersionRange defaultVR;
    return defaultVR;
}

bool QTKVersionRange::isSpecified() const
{
    return !(*this == this->defaultVersionRange());
}

/**
 * Check if specified version is within our range.
 *
 * @param ver QTKVersion to compare to.
 * @return Return true if within range, otherwise false.
 */
bool QTKVersionRange::withinRange(const QTKVersion &version) const
{
    if (*this == defaultVersionRange()) {
        return true;
    }
    int iCmp = m_low.compare(version);

    if (iCmp < 0 || (iCmp == 0 && m_bLowIncluded)) {
        if (m_high.isUndefined()) {
            return true;
        }
        iCmp = m_high.compare(version);
        return iCmp > 0 || (iCmp == 0 && m_bHighIncluded);
    }
    return false;
}

/**
 * Check if objects range is within another QTKVersionRange.
 *
 * @param range QTKVersionRange to compare to.
 * @return Return true if within range, otherwise false.
 */
bool QTKVersionRange::withinRange(const QTKVersionRange &range) const
{
    if (*this == range) {
        return true;
    }
    int iCmp = m_low.compare(range.m_low);

    if (iCmp < 0 || (iCmp == 0 && m_bLowIncluded == range.m_bLowIncluded)) {
        if (m_high.isUndefined()) {
            return true;
        }
        iCmp = m_high.compare(range.m_high);
        return iCmp > 0 || (iCmp == 0 && m_bHighIncluded == range.m_bHighIncluded);
    }
    return false;
}

/**
 * Compare object to another QTKVersionRange. VersionRanges are compared on the
 * lower bound.
 *
 * @param obj QTKVersionRange to compare to.
 * @return Return 0 if equals, negative if this object is less than obj
 *         and positive if this object is larger then obj.
 * @exception ClassCastException if object is not a QTKVersionRange object.
 */
int QTKVersionRange::compare(const QTKVersionRange &obj) const
{
    return m_low.compare(obj.m_low);
}

/**
 * String with version number. If version is not specified return
 * an empty string.
 *
 * @return QString.
 */
QString QTKVersionRange::toString() const
{
    if (!m_high.isUndefined()) {
        QString strRes;
        if (m_bLowIncluded) {
            strRes += '[';
        } else {
            strRes += '(';
        }
        strRes += m_low.toString() + "," + m_high.toString();
        if (m_bHighIncluded) {
            strRes += ']';
        } else {
            strRes += ')';
        }
        return strRes;
    } else {
        return m_low.toString();
    }
}

/**
 * Check if object is equal to this object.
 *
 * @param obj Package entry to compare to.
 * @return true if equal, otherwise false.
 */
bool QTKVersionRange::operator==(const QTKVersionRange &range) const
{
    if (m_low == range.m_low) {
        if (!m_high.isUndefined()) {
            return (m_high == range.m_high)
                    && (m_bLowIncluded == range.m_bLowIncluded)
                    && (m_bHighIncluded == range.m_bHighIncluded);
        } else {
            return true;
        }
    }
    return false;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
