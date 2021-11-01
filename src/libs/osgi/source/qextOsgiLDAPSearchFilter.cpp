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

#include "qtkldapsearchfilter.h"
#include "qtkldapexpr_p.h"
#include "qtkservicereference_p.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKLDAPSearchFilterPrivate : public QSharedData
{
public:
    QTKLDAPSearchFilterPrivate() {}
    QTKLDAPSearchFilterPrivate(const QString &strFilter) : ldapExpr(strFilter) {}
    QTKLDAPSearchFilterPrivate(const QTKLDAPSearchFilterPrivate& other) : QSharedData(other), ldapExpr(other.ldapExpr) {}

    QTKLDAPExpr ldapExpr;
};

QTKLDAPSearchFilter::QTKLDAPSearchFilter() : d_ptr(nullptr)
{

}

QTKLDAPSearchFilter::QTKLDAPSearchFilter(const QString &strFilter) : d_ptr(nullptr)
{
    d_ptr = new QTKLDAPSearchFilterPrivate(strFilter);
}

QTKLDAPSearchFilter::QTKLDAPSearchFilter(const QTKLDAPSearchFilter &other) : d_ptr(other.d_ptr)
{

}

QTKLDAPSearchFilter::~QTKLDAPSearchFilter()
{

}

bool QTKLDAPSearchFilter::match(const QTKServiceReference &reference) const
{
    return d_ptr->ldapExpr.evaluate(reference.d_func()->getProperties(), true);
}

bool QTKLDAPSearchFilter::match(const QTKDictionary &dictionary) const
{
    return d_ptr->ldapExpr.evaluate(dictionary, false);
}

bool QTKLDAPSearchFilter::matchCase(const QTKDictionary &dictionary) const
{
    return d_ptr->ldapExpr.evaluate(dictionary, true);
}

QString QTKLDAPSearchFilter::toString() const
{
    return d_ptr->ldapExpr.toString();
}

bool QTKLDAPSearchFilter::operator==(const QTKLDAPSearchFilter &other) const
{
    return d_ptr->ldapExpr.toString() == other.d_ptr->ldapExpr.toString();
}

QTKLDAPSearchFilter &QTKLDAPSearchFilter::operator=(const QTKLDAPSearchFilter &filter)
{
    d_ptr = filter.d_ptr;
    return *this;
}

QTKLDAPSearchFilter::operator bool() const
{
    return d_ptr;
}

QDebug operator<<(QDebug dbg, const QTKLDAPSearchFilter &filter)
{
    dbg << filter.toString();
    return dbg.maybeSpace();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
