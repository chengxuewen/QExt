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

#ifndef QTKLDAPEXPR_P_H
#define QTKLDAPEXPR_P_H

#include "qtkpluginconstants.h"
#include "qtkserviceproperties_p.h"

#include <QString>
#include <QHash>
#include <QSharedDataPointer>
#include <QVector>
#include <QStringList>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKLDAPExprData;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKLDAPExpr class
 * LDAP Expression
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKLDAPExpr
{
public:
    typedef char Byte;
    typedef QVector<QStringList> LocalCache;

    /**
     * @brief QTKLDAPExpr::QTKLDAPExpr
     * Creates an invalid QTKLDAPExpr object. Use with care.
     *
     * @see isNull()
     */
    QTKLDAPExpr();
    QTKLDAPExpr(const QString &strFilter);
    QTKLDAPExpr(const QTKLDAPExpr &other);
    ~QTKLDAPExpr();

    /**
     * @brief QTKLDAPExpr::getMatchedObjectClasses
     * Get object class set matched by this LDAP expression. This will not work
     * with wildcards and NOT expressions. If a set can not be determined return <code>fasle</code>.
     *
     * @param objClasses The set of matched classes will be added to objClasses.
     * @return If the set cannot be determined, <code>false</code> is returned, <code>true</code> otherwise.
     */
    bool getMatchedObjectClasses(QSet<QString> &objClasses) const;

    /**
     * @brief QTKLDAPExpr::isSimple
     * Checks if this LDAP expression is "simple". The definition of
     * a simple filter is:
     * <ul>
     *  <li><code>(<it>name</it>=<it>value</it>)</code> is simple if
     *      <it>name</it> is a member of the provided <code>keywords</code>,
     *      and <it>value</it> does not contain a wildcard character;</li>
     *  <li><code>(| EXPR+ )</code> is simple if all <code>EXPR</code>
     *      expressions are simple;</li>
     *  <li>No other expressions are simple.</li>
     * </ul>
     * If the filter is found to be simple, the <code>cache</code> is
     * filled with mappings from the provided keywords to lists
     * of attribute values. The keyword-value-pairs are the ones that
     * satisfy this expression, for the given keywords.
     *
     * @param listKeywords The keywords to look for.
     * @param cache An array (indexed by the keyword indexes) of lists to fill
     * in with values saturating this expression.
     * @param bMatchCase
     * @return <code>true</code> if this expression is simple, <code>false</code> otherwise.
     */
    bool isSimple(const QStringList &listKeywords, LocalCache &cache, bool bMatchCase) const;

    /**
     * @brief QTKLDAPExpr::isNull
     * Returns <code>true</code> if this instance is invalid, i.e. it was constructed using QTKLDAPExpr().
     *
     * @return <code>true</code> if the expression is invalid, <code>false</code> otherwise.
     */
    bool isNull() const;
    static bool query(const QString &strFilter, const QTKDictionary &dictionary);

    /**
     * @brief QTKLDAPExpr::evaluate
     * Evaluate this LDAP filter.
     *
     * @param serviceProperties
     * @param bMatchCase
     * @return
     */
    bool evaluate(const QTKServiceProperties &serviceProperties, bool bMatchCase) const;
    const QString toString() const;

    QTKLDAPExpr& operator=(const QTKLDAPExpr &other);

private:
    class ParseState;

    QTKLDAPExpr(int op, const QList<QTKLDAPExpr> &listArgs);
    QTKLDAPExpr(int op, const QString &strAttrName, const QString &strAttrValue);
    static QTKLDAPExpr parseExpr(ParseState &ps);
    static QTKLDAPExpr parseSimple(ParseState &ps);
    bool compare(const QVariant &obj, int iOperator, const QString &str) const;
    static bool compareString(const QString &str1, int iOperator, const QString &str2);
    static QString fixupString(const QString &str);
    static bool patSubstr(const QString &str, const QString &strPat);
    static bool patSubstr(const QString &str, int iSi, const QString &strPat, int iPi);

    QSharedDataPointer<QTKLDAPExprData> d;

    const static QChar sm_wildCard;                 //  = 65535;
    const static QString sm_strWildCard;            //  = QString( WILDCARD );
    const static char *nullptr_QUERY;              //  = "Null query";
    const static char *TRAILING_GARBAGE;        //  = "Trailing garbage";
    const static char *UNEXPECTED_END_OF_QUERY;   //  = "Unexpected end of query";
    const static char *MALFORMED_QUERY;         //  = "Malformed query";
    const static char *UNDEFINED_OPERATOR;      //  = "Undefined m_operator";

    const static int sm_iAnd;       // =  0;
    const static int sm_iOr;        // =  1;
    const static int sm_iNot;       // =  2;
    const static int sm_iEqual;     // =  4;
    const static int sm_iLess;      // =  8;
    const static int sm_iGreater;   // = 16;
    const static int sm_iApprox;    // = 32;
    const static int sm_iComplex;   // = AND | OR | NOT;
    const static int sm_iSimple;    // = EQ | LE | GE | APPROX;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKLDAPEXPR_P_H
