/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#ifndef _QEXTOSGIVERSIONRANGE_H
#define _QEXTOSGIVERSIONRANGE_H

#include <qextOsgiVersion.h>


/**
 * \ingroup PluginFramework
 *
 * Class representing CTK version ranges.
 */
class QEXT_OSGI_API QExtOsgiVersionRange
{

private:

    QExtOsgiVersion low;
    QExtOsgiVersion high;
    bool lowIncluded;
    bool highIncluded;

public:

    /**
   * The empty version range "[0.0.0,inf)".
   */
    static QExtOsgiVersionRange defaultVersionRange();

    /**
   * Construct a QExtOsgiVersionRange object.
   * Format for a range:
   *   ( "(" | "[" ) LOW_VERSION ","  HIGH_VERSION ( ")" | "]" )
   * Format for at least a version:
   *   VERSION
   *
   * @param vr Input string.
   */
    QExtOsgiVersionRange(const QString& vr);


    /**
   * Construct the default QExtOsgiVersionRange object.
   *
   */
    QExtOsgiVersionRange();

    ~QExtOsgiVersionRange();


    bool isSpecified() const;


    /**
   * Check if specified version is within our range.
   *
   * @param ver QExtOsgiVersion to compare to.
   * @return Return true if within range, otherwise false.
   */
    bool withinRange(const QExtOsgiVersion& ver) const;


    /**
   * Check if objects range is within another QExtOsgiVersionRange.
   *
   * @param range QExtOsgiVersionRange to compare to.
   * @return Return true if within range, otherwise false.
   */
    bool withinRange(const QExtOsgiVersionRange& range) const;


    /**
   * Compare object to another QExtOsgiVersionRange. VersionRanges are compared on the
   * lower bound.
   *
   * @param obj QExtOsgiVersionRange to compare to.
   * @return Return 0 if equals, negative if this object is less than obj
   *         and positive if this object is larger then obj.
   * @exception ClassCastException if object is not a QExtOsgiVersionRange object.
   */
    int compare(const QExtOsgiVersionRange& obj) const;


    /**
   * String with version number. If version is not specified return
   * an empty string.
   *
   * @return QString.
   */
    QString toString() const;


    /**
   * Check if object is equal to this object.
   *
   * @param obj Package entry to compare to.
   * @return true if equal, otherwise false.
   */
    bool operator==(const QExtOsgiVersionRange& r) const;

};

#endif // _QEXTOSGIVERSIONRANGE_H
