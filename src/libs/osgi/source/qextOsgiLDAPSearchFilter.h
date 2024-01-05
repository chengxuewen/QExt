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

#ifndef _QEXTOSGILDAPSEARCHFILTER_H
#define _QEXTOSGILDAPSEARCHFILTER_H

#include <qextOsgiGlobal.h>
#include <qextOsgiDictionary.h>
#include <qextOsgiServiceReference.h>

#include <QDebug>
#include <QSharedDataPointer>

class QExtLDAPSearchFilterData;

/**
 * \ingroup PluginFramework
 *
 * An <a href="http://www.ietf.org/rfc/rfc1960.txt">RFC 1960</a>-based Filter.
 *
 * <p>
 * A <code>QExtOsgiLDAPSearchFilter</code> can be used numerous times to determine if the match
 * argument matches the filter string that was used to create the <code>QExtOsgiLDAPSearchFilter</code>.
 * <p>
 * Some examples of LDAP filters are:
 *
 * \verbatim
 * "(cn=Babs Jensen)"
 * "(!(cn=Tim Howes))"
 * "(&(" + QExtOsgiPluginConstants::OBJECTCLASS + "=Person)(|(sn=Jensen)(cn=Babs J*)))"
 *  "(o=univ*of*mich*)"
 * \endverbatim
 *
 * \see "CTK Wiki for a description of the filter string syntax." TODO!
 * \remarks This class is thread safe.
 */
class QEXT_OSGI_API QExtOsgiLDAPSearchFilter {

public:

    /**
   * Creates in invalid <code>QExtOsgiLDAPSearchFilter</code> object.
   * Test the validity by using the boolean conversion operator.
   *
   * <p>
   * Calling methods on an invalid <code>QExtOsgiLDAPSearchFilter</code>
   * will result in undefined behavior.
   */
    QExtOsgiLDAPSearchFilter();

    /**
   * Creates a <code>QExtOsgiLDAPSearchFilter</code> object. This <code>QExtOsgiLDAPSearchFilter</code>
   * object may be used to match a <code>QExtOsgiServiceReference</code> object or a
   * <code>QExtOsgiDictionary</code> object.
   *
   * <p>
   * If the filter cannot be parsed, an QExtInvalidArgumentException will be
   * thrown with a human readable message where the filter became unparsable.
   *
   * @param filter The filter string.
   * @return A <code>QExtOsgiLDAPSearchFilter</code> object encapsulating the filter string.
   * @throws QExtInvalidArgumentException If <code>filter</code> contains an invalid
   *         filter string that cannot be parsed.
   * @see "Framework specification for a description of the filter string syntax." TODO!
   */
    QExtOsgiLDAPSearchFilter(const QString& filter);

    QExtOsgiLDAPSearchFilter(const QExtOsgiLDAPSearchFilter& other);

    ~QExtOsgiLDAPSearchFilter();

    operator bool() const;

    /**
   * Filter using a service's properties.
   * <p>
   * This <code>QExtOsgiLDAPSearchFilter</code> is executed using the keys and values of the
   * referenced service's properties. The keys are looked up in a case
   * insensitive manner.
   *
   * @param reference The reference to the service whose properties are used
   *        in the match.
   * @return <code>true</code> if the service's properties match this
   *         <code>QExtOsgiLDAPSearchFilter</code> <code>false</code> otherwise.
   */
    bool match(const QExtOsgiServiceReference& reference) const;

    /**
   * Filter using a <code>QExtOsgiDictionary</code> with case insensitive key lookup. This
   * <code>QExtOsgiLDAPSearchFilter</code> is executed using the specified <code>QExtOsgiDictionary</code>'s keys
   * and values. The keys are looked up in a case insensitive manner.
   *
   * @param dictionary The <code>QExtOsgiDictionary</code> whose key/value pairs are used
   *        in the match.
   * @return <code>true</code> if the <code>QExtOsgiDictionary</code>'s values match this
   *         filter; <code>false</code> otherwise.
   */
    bool match(const QExtOsgiDictionary& dictionary) const;

    /**
   * Filter using a <code>QExtOsgiDictionary</code>. This <code>QExtOsgiLDAPSearchFilter</code> is executed using
   * the specified <code>QExtOsgiDictionary</code>'s keys and values. The keys are looked
   * up in a normal manner respecting case.
   *
   * @param dictionary The <code>QExtOsgiDictionary</code> whose key/value pairs are used
   *        in the match.
   * @return <code>true</code> if the <code>QExtOsgiDictionary</code>'s values match this
   *         filter; <code>false</code> otherwise.
   */
    bool matchCase(const QExtOsgiDictionary& dictionary) const;

    /**
   * Returns this <code>QExtOsgiLDAPSearchFilter</code>'s filter string.
   * <p>
   * The filter string is normalized by removing whitespace which does not
   * affect the meaning of the filter.
   *
   * @return This <code>QExtOsgiLDAPSearchFilter</code>'s filter string.
   */
    QString toString() const;

    /**
   * Compares this <code>QExtOsgiLDAPSearchFilter</code> to another <code>QExtOsgiLDAPSearchFilter</code>.
   *
   * <p>
   * This implementation returns the result of calling
   * <code>this->toString() == other.toString()</code>.
   *
   * @param other The object to compare against this <code>QExtOsgiLDAPSearchFilter</code>.
   * @return Returns the result of calling
   *         <code>this->toString() == other.toString()</code>.
   */
    bool operator==(const QExtOsgiLDAPSearchFilter& other) const;

    QExtOsgiLDAPSearchFilter& operator=(const QExtOsgiLDAPSearchFilter& filter);

protected:

    QSharedDataPointer<QExtLDAPSearchFilterData> d;

};

/**
 * \ingroup PluginFramework
 */
QEXT_OSGI_API QDebug operator<<(QDebug dbg, const QExtOsgiLDAPSearchFilter& filter);

#endif // _QEXTOSGILDAPSEARCHFILTER_H
