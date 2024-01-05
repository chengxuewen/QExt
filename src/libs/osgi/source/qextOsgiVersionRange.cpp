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

#include <private/qextOsgiVersionRange_p.h>
#include <qextException.h>

//----------------------------------------------------------------------------
QExtOsgiVersionRange QExtOsgiVersionRange::defaultVersionRange()
{
    static QExtOsgiVersionRange defaultVR;
    return defaultVR;
}

//----------------------------------------------------------------------------
QExtOsgiVersionRange::QExtOsgiVersionRange(const QString& vr)
{
    bool op = vr.startsWith("(");
    bool ob = vr.startsWith("[");

    if (op || ob)
    {
        bool cp = vr.endsWith(")");
        bool cb = vr.endsWith("]");
        int comma = vr.indexOf(',');

        if (comma > 0 && (cp || cb))
        {
            low = QExtOsgiVersion(vr.mid(1, comma-1).trimmed());
            high = QExtOsgiVersion(vr.mid(comma+1, vr.length()-comma-2).trimmed());
            lowIncluded = ob;
            highIncluded = cb;
        }
        else
        {
            throw QExtInvalidArgumentException("Illegal version range: " + vr);
        }
    }
    else
    {
        low = QExtOsgiVersion(vr);
        high = QExtOsgiVersion();
        lowIncluded = true;
        highIncluded = false;
    }
}

//----------------------------------------------------------------------------
QExtOsgiVersionRange::QExtOsgiVersionRange()
{
    low = QExtOsgiVersion(QExtOsgiVersion::emptyVersion());
    high = QExtOsgiVersion();
    lowIncluded = true;
    highIncluded = false;
}

//----------------------------------------------------------------------------
QExtOsgiVersionRange::~QExtOsgiVersionRange()
{
}

//----------------------------------------------------------------------------
bool QExtOsgiVersionRange::isSpecified() const
{
    return !(*this == defaultVersionRange());
}

//----------------------------------------------------------------------------
bool QExtOsgiVersionRange::withinRange(const QExtOsgiVersion& ver) const
{
    if (*this == defaultVersionRange())
    {
        return true;
    }
    int c = low.compare(ver);

    if (c < 0 || (c == 0 && lowIncluded))
    {
        if (high.isUndefined())
        {
            return true;
        }
        c = high.compare(ver);
        return c > 0 || (c == 0 && highIncluded);
    }
    return false;
}

//----------------------------------------------------------------------------
bool QExtOsgiVersionRange::withinRange(const QExtOsgiVersionRange& range) const
{
    if (*this == range)
    {
        return true;
    }
    int c = low.compare(range.low);

    if (c < 0 || (c == 0 && lowIncluded == range.lowIncluded))
    {
        if (high.isUndefined())
        {
            return true;
        }
        c = high.compare(range.high);
        return c > 0 || (c == 0 && highIncluded == range.highIncluded);
    }
    return false;
}

//----------------------------------------------------------------------------
int QExtOsgiVersionRange::compare(const QExtOsgiVersionRange& obj) const
{
    return low.compare(obj.low);
}

//----------------------------------------------------------------------------
QString QExtOsgiVersionRange::toString() const
{
    if (!high.isUndefined())
    {
        QString res;
        if (lowIncluded)
        {
            res += '[';
        }
        else
        {
            res += '(';
        }
        res += low.toString() + "," + high.toString();
        if (highIncluded)
        {
            res += ']';
        }
        else
        {
            res += ')';
        }
        return res;
    }
    else
    {
        return low.toString();
    }
}

//----------------------------------------------------------------------------
bool QExtOsgiVersionRange::operator==(const QExtOsgiVersionRange& r) const
{
    if (low == r.low)
    {
        if (!high.isUndefined())
        {
            return (high == r.high)  && (lowIncluded == r.lowIncluded) && (highIncluded == r.highIncluded);
        }
        else
        {
            return true;
        }
    }
    return false;
}
