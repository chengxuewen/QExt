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

#ifndef QTKLDAPSEARCHFILTER_H
#define QTKLDAPSEARCHFILTER_H

#include "qtkpluginframework_global.h"
#include "qtkservicereference.h"
#include "qtkdictionary.h"

#include <QSharedDataPointer>
#include <QDebug>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKLDAPSearchFilterPrivate;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKLDAPSearchFilter class
 * An <a href="http://www.ietf.org/rfc/rfc1960.txt">RFC 1960</a>-based Filter.
 *
 * <p>
 * A <code>QTKLDAPSearchFilter</code> can be used numerous times to determine if the match
 * argument matches the filter string that was used to create the <code>QTKLDAPSearchFilter</code>.
 * <p>
 * Some examples of LDAP filters are:
 *
 * @verbatim
 * "(cn=Babs Jensen)"
 * "(!(cn=Tim Howes))"
 * "(&(" + QTKPluginConstants::OBJECTCLASS + "=Person)(|(sn=Jensen)(cn=Babs J*)))"
 * "(o=univ*of*mich*)"
 * @endverbatim
 *
 * @see "QTK Wiki for a description of the filter string syntax." TODO!
 * @remarks This class is thread safe.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKLDAPSearchFilter
{
public:

    /**
     * @brief QTKLDAPSearchFilter::QTKLDAPSearchFilter
     * Creates in invalid <code>QTKLDAPSearchFilter</code> object.
     * Test the validity by using the boolean conversion operator.
     *
     * <p>
     * Calling methods on an invalid <code>QTKLDAPSearchFilter</code>
     * will result in undefined behavior.
     */
    QTKLDAPSearchFilter();

    /**
     * @brief QTKLDAPSearchFilter::QTKLDAPSearchFilter
     * Creates a <code>QTKLDAPSearchFilter</code> object. This <code>QTKLDAPSearchFilter</code>
     * object may be used to match a <code>QTKServiceReference</code> object or a
     * <code>QTKDictionary</code> object.
     *
     * <p>
     * If the filter cannot be parsed, an QTKInvalidArgumentException will be
     * thrown with a human readable message where the filter became unparsable.
     *
     * @param strFilter The filter string.
     * @return A <code>QTKLDAPSearchFilter</code> object encapsulating the filter string.
     * @exception QTKInvalidArgumentException If <code>filter</code> contains an invalid
     * filter string that cannot be parsed.
     * @see "Framework specification for a description of the filter string syntax." TODO!
     */
    QTKLDAPSearchFilter(const QString &strFilter);
    QTKLDAPSearchFilter(const QTKLDAPSearchFilter &other);
    ~QTKLDAPSearchFilter();

    /**
     * @brief QTKLDAPSearchFilter::match
     * Filter using a service's properties.
     * <p>
     * This <code>QTKLDAPSearchFilter</code> is executed using the keys and values of the
     * referenced service's properties. The keys are looked up in a case
     * insensitive manner.
     *
     * @param reference The reference to the service whose properties are used
     *        in the match.
     * @return <code>true</code> if the service's properties match this
     *         <code>QTKLDAPSearchFilter</code> <code>false</code> otherwise.
     */
    bool match(const QTKServiceReference &reference) const;

    /**
     * @brief QTKLDAPSearchFilter::match
     * Filter using a <code>QTKDictionary</code> with case insensitive key lookup. This
     * <code>QTKLDAPSearchFilter</code> is executed using the specified <code>QTKDictionary</code>'s keys
     * and values. The keys are looked up in a case insensitive manner.
     *
     * @param dictionary The <code>QTKDictionary</code> whose key/value pairs are used in the match.
     * @return <code>true</code> if the <code>QTKDictionary</code>'s values match this filter;
     * <code>false</code> otherwise.
     */
    bool match(const QTKDictionary &dictionary) const;

    /**
     * @brief QTKLDAPSearchFilter::matchCase\
     * Filter using a <code>QTKDictionary</code>. This <code>QTKLDAPSearchFilter</code> is executed using
     * the specified <code>QTKDictionary</code>'s keys and values. The keys are looked
     * up in a normal manner respecting case.
     *
     * @param dictionary The <code>QTKDictionary</code> whose key/value pairs are used in the match.
     * @return <code>true</code> if the <code>QTKDictionary</code>'s values match this filter;
     * <code>false</code> otherwise.
     */
    bool matchCase(const QTKDictionary &dictionary) const;

    /**
     * @brief QTKLDAPSearchFilter::toString
     * Returns this <code>QTKLDAPSearchFilter</code>'s filter string.
     * <p>
     * The filter string is normalized by removing whitespace which does not
     * affect the meaning of the filter.
      *
     * @return This <code>QTKLDAPSearchFilter</code>'s filter string.
     */
    QString toString() const;

    operator bool() const;

    /**
     * @brief QTKLDAPSearchFilter::operator ==
     * Compares this <code>QTKLDAPSearchFilter</code> to another <code>QTKLDAPSearchFilter</code>.
     *
     * <p>
     * This implementation returns the result of calling
     * <code>this->toString() == other.toString()</code>.
     *
     * @param other The object to compare against this <code>QTKLDAPSearchFilter</code>.
     * @return Returns the result of calling <code>this->toString() == other.toString()</code>.
     */
    bool operator==(const QTKLDAPSearchFilter &other) const;
    QTKLDAPSearchFilter& operator=(const QTKLDAPSearchFilter &filter);

protected:
    QSharedDataPointer<QTKLDAPSearchFilterPrivate> d_ptr;
};

QTK_PLUGINFRAMEWORK_EXPORT QDebug operator<<(QDebug dbg, const QTKLDAPSearchFilter &filter);

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKLDAPSEARCHFILTER_H
