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

#include <qextOsgiLDAPSearchFilter.h>
#include <private/qextOsgiLDAPExpr_p.h>
#include <private/qextOsgiServiceReference_p.h>

//----------------------------------------------------------------------------
class QExtLDAPSearchFilterData : public QSharedData
{
public:

    QExtLDAPSearchFilterData()
    {}

    QExtLDAPSearchFilterData(const QString& filter)
        : ldapExpr(filter)
    {}

    QExtLDAPSearchFilterData(const QExtLDAPSearchFilterData& other)
        : QSharedData(other), ldapExpr(other.ldapExpr)
    {}

    QExtOsgiLDAPExpr ldapExpr;
};

//----------------------------------------------------------------------------
QExtOsgiLDAPSearchFilter::QExtOsgiLDAPSearchFilter()
    : d(0)
{
}

//----------------------------------------------------------------------------
QExtOsgiLDAPSearchFilter::QExtOsgiLDAPSearchFilter(const QString& filter)
    : d(0)
{
    d = new QExtLDAPSearchFilterData(filter);
}

//----------------------------------------------------------------------------
QExtOsgiLDAPSearchFilter::QExtOsgiLDAPSearchFilter(const QExtOsgiLDAPSearchFilter& other)
    : d(other.d)
{
}

//----------------------------------------------------------------------------
QExtOsgiLDAPSearchFilter::~QExtOsgiLDAPSearchFilter()
{
}

//----------------------------------------------------------------------------
QExtOsgiLDAPSearchFilter::operator bool() const
{
    return d;
}

//----------------------------------------------------------------------------
bool QExtOsgiLDAPSearchFilter::match(const QExtOsgiServiceReference& reference) const
{
    return d->ldapExpr.evaluate(reference.d_func()->getProperties(), true);
}

//----------------------------------------------------------------------------
bool QExtOsgiLDAPSearchFilter::match(const QExtOsgiDictionary& dictionary) const
{
    return d->ldapExpr.evaluate(dictionary, false);
}

//----------------------------------------------------------------------------
bool QExtOsgiLDAPSearchFilter::matchCase(const QExtOsgiDictionary& dictionary) const
{
    return d->ldapExpr.evaluate(dictionary, true);
}

//----------------------------------------------------------------------------
QString QExtOsgiLDAPSearchFilter::toString() const
{
    return d->ldapExpr.toString();
}

//----------------------------------------------------------------------------
bool QExtOsgiLDAPSearchFilter::operator==(const QExtOsgiLDAPSearchFilter& other) const
{
    return d->ldapExpr.toString() == other.d->ldapExpr.toString();
}

//----------------------------------------------------------------------------
QExtOsgiLDAPSearchFilter& QExtOsgiLDAPSearchFilter::operator=(const QExtOsgiLDAPSearchFilter& filter)
{
    d = filter.d;

    return *this;
}

//----------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const QExtOsgiLDAPSearchFilter& filter)
{
    dbg << filter.toString();
    return dbg.maybeSpace();
}
