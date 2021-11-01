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

#include "qtkldapexpr_p.h"

#include <QTKCore/QTKException>

#include <QSet>
#include <QVariant>
#include <QStringList>
#include <stdexcept>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const int QTKLDAPExpr::sm_iAnd =  0;
const int QTKLDAPExpr::sm_iOr =  1;
const int QTKLDAPExpr::sm_iNot =  2;
const int QTKLDAPExpr::sm_iEqual =  4;
const int QTKLDAPExpr::sm_iLess =  8;
const int QTKLDAPExpr::sm_iGreater = 16;
const int QTKLDAPExpr::sm_iApprox = 32;
const int QTKLDAPExpr::sm_iComplex = QTKLDAPExpr::sm_iAnd | QTKLDAPExpr::sm_iOr | QTKLDAPExpr::sm_iNot;
const int QTKLDAPExpr::sm_iSimple = QTKLDAPExpr::sm_iEqual | QTKLDAPExpr::sm_iLess | QTKLDAPExpr::sm_iGreater | QTKLDAPExpr::sm_iApprox;

const QChar QTKLDAPExpr::sm_wildCard = 65535;
const QString QTKLDAPExpr::sm_strWildCard = QString(QTKLDAPExpr::sm_wildCard);
const char *QTKLDAPExpr::nullptr_QUERY = "Null query";
const char *QTKLDAPExpr::TRAILING_GARBAGE = "Trailing garbage";
const char *QTKLDAPExpr::UNEXPECTED_END_OF_QUERY = "Unexpected end of query";
const char *QTKLDAPExpr::MALFORMED_QUERY = "Malformed query";
const char *QTKLDAPExpr::UNDEFINED_OPERATOR = "Undefined operator";

class QTKLDAPExpr::ParseState
{
public:
    ParseState(const QString &str);
    bool prefix(const QString &pre);
    QChar peek();
    void skip(int n);
    QString rest() const;
    void skipWhite();
    QString getAttributeName();
    QString getAttributeValue();
    void error(const QString &strMsg) const;

private:
    int m_pos;
    QString m_str;
};

QTKLDAPExpr::ParseState::ParseState(const QString &str)
{
    if (str.isEmpty()) {
        this->error(nullptr_QUERY);
    }
    m_str = str;
    m_pos = 0;
}

bool QTKLDAPExpr::ParseState::prefix(const QString &pre)
{
    if (!m_str.mid(m_pos).startsWith(pre)) {
        return false;
    }
    m_pos += pre.length();
    return true;
}

QChar QTKLDAPExpr::ParseState::peek()
{
    if (m_pos >= m_str.size()) {
        throw std::out_of_range( "LDAPExpr" );
    }
    return m_str.at(m_pos);
}

void QTKLDAPExpr::ParseState::skip(int n)
{
    m_pos += n;
}

QString QTKLDAPExpr::ParseState::rest() const
{
    return m_str.mid(m_pos);
}

void QTKLDAPExpr::ParseState::skipWhite()
{
    while (this->peek().isSpace()) {
        m_pos++;
    }
}

QString QTKLDAPExpr::ParseState::getAttributeName()
{
    int start = m_pos;
    int n = -1;
    for(;; m_pos++) {
        QChar c = peek();
        if (c == '(' || c == ')' || c == '<' || c == '>' || c == '=' || c == '~') {
            break;
        } else if (!c.isSpace()) {
            n = m_pos - start + 1;
        }
    }
    if (n == -1) {
        return QString::Null();
    }
    return m_str.mid(start, n);
}

QString QTKLDAPExpr::ParseState::getAttributeValue()
{
    QString sb;
    bool exit = false;
    while( !exit ) {
        QChar c = peek( );
        switch(c.toLatin1()) {
        case '(':
        case ')':
        {
            exit = true;
            break;
        }
        case '*':
        {
            sb.append(sm_wildCard);
            break;
        }
        case '\\':
        {
            sb.append(m_str.at(++m_pos));
            break;
        }
        default:
        {
            sb.append(c);
            break;
        }
        }

        if (!exit) {
            m_pos++;
        }
    }
    return sb;
}

void QTKLDAPExpr::ParseState::error(const QString &strMsg) const
{
    QString strError = strMsg + ": " + (m_str.isNull() ? "" : m_str.mid(m_pos) );
    throw QTKInvalidArgumentException(strError);
}

/**
 * @brief The QTKLDAPExprData class
 */
class QTKLDAPExprData : public QSharedData
{
public:
    QTKLDAPExprData(int iOperator, QList<QTKLDAPExpr> listArgs)
        : m_iOperator(iOperator),
          m_listArgs(listArgs)
    {
    }

    QTKLDAPExprData(int iOperator, QString strAttrName, QString strAttrValue)
        : m_iOperator(iOperator),
          m_strAttrName(strAttrName),
          m_strAttrValue(strAttrValue)
    {
    }

    QTKLDAPExprData(const QTKLDAPExprData &other) : QSharedData(other),
        m_iOperator(other.m_iOperator),
        m_listArgs(other.m_listArgs),
        m_strAttrName(other.m_strAttrName),
        m_strAttrValue(other.m_strAttrValue)
    {

    }

    int m_iOperator;
    QList<QTKLDAPExpr> m_listArgs;
    QString m_strAttrName;
    QString m_strAttrValue;
};

QTKLDAPExpr::QTKLDAPExpr()
{

}

QTKLDAPExpr::QTKLDAPExpr(const QString &strFilter)
{
    ParseState parseState(strFilter);

    QTKLDAPExpr expr;
    try {
        expr = parseExpr(parseState);
    } catch (const std::out_of_range &) {
        parseState.error(UNEXPECTED_END_OF_QUERY);
    }

    if (!parseState.rest().trimmed().isEmpty()) {
        parseState.error(QLatin1String(TRAILING_GARBAGE) + " '" + parseState.rest() + "'");
    }

    d = expr.d;
}

QTKLDAPExpr::QTKLDAPExpr(const QTKLDAPExpr &other)
    : d(other.d)
{

}

QTKLDAPExpr::~QTKLDAPExpr()
{

}

bool QTKLDAPExpr::getMatchedObjectClasses(QSet<QString> &objClasses) const
{
    if (sm_iEqual == d->m_iOperator) {
        if (d->m_strAttrName.compare(QTKPluginConstants::OBJECT_CLASS, Qt::CaseInsensitive) == 0 &&
                d->m_strAttrValue.indexOf(sm_wildCard) < 0) {
            objClasses.insert( d->m_strAttrValue );
            return true;
        }
        return false;
    } else if (sm_iAnd == d->m_iOperator) {
        bool bResult = false;
        for (int i = 0; i < d->m_listArgs.size( ); i++) {
            QSet<QString> r;
            if(d->m_listArgs[i].getMatchedObjectClasses(r)) {
                bResult = true;
                if (objClasses.empty()) {
                    objClasses = r;
                } else {
                    // if AND op and classes in several operands,
                    // then only the intersection is possible.
                    objClasses.intersect(r);
                }
            }
        }
        return bResult;
    } else if (sm_iOr == d->m_iOperator) {
        for (int i = 0; i < d->m_listArgs.length( ); i++) {
            QSet<QString> r;
            if (d->m_listArgs[i].getMatchedObjectClasses(r)) {
                objClasses += r;
            } else {
                objClasses.clear();
                return false;
            }
        }
        return true;
    }
    return false;
}

bool QTKLDAPExpr::isSimple(const QStringList &listKeywords, QTKLDAPExpr::LocalCache &cache, bool bMatchCase) const
{
    if (cache.isEmpty()) {
        cache.resize(listKeywords.size());
    }

    if (sm_iEqual == d->m_iOperator) {
        int index;
        if ((index = listKeywords.indexOf(bMatchCase ? d->m_strAttrName : d->m_strAttrName.toLower())) >= 0 &&
                d->m_strAttrValue.indexOf(sm_wildCard) < 0) {
            cache[index] = QStringList(d->m_strAttrValue);
            return true;
        }
    } else if (sm_iOr == d->m_iOperator) {
        for (int i = 0; i < d->m_listArgs.size( ); i++) {
            if (!d->m_listArgs[i].isSimple(listKeywords, cache, bMatchCase))
                return false;
        }
        return true;
    }
    return false;
}

bool QTKLDAPExpr::isNull() const
{
    return !d;
}

bool QTKLDAPExpr::query(const QString &strFilter, const QTKDictionary &dictionary)
{
    return QTKLDAPExpr(strFilter).evaluate(dictionary, false);
}

bool QTKLDAPExpr::evaluate(const QTKServiceProperties &serviceProperties, bool bMatchCase) const
{
    if ((d->m_iOperator & sm_iSimple) != 0) {
        // try case sensitive match first
        int index = serviceProperties.findCaseSensitive(d->m_strAttrName);
        if (index < 0 && !bMatchCase) {
            index = serviceProperties.find(d->m_strAttrName);
        }
        return index < 0 ? false : this->compare(serviceProperties.value(index), d->m_iOperator, d->m_strAttrValue);
    } else {    // (d->m_operator & COMPLEX) != 0
        switch (d->m_iOperator) {
        case sm_iAnd:
        {
            for (int i = 0; i < d->m_listArgs.length( ); i++) {
                if (!d->m_listArgs[i].evaluate(serviceProperties, bMatchCase)) {
                    return false;
                }
            }
            return true;
        }
        case sm_iOr:
        {
            for (int i = 0; i < d->m_listArgs.length( ); i++) {
                if (d->m_listArgs[i].evaluate(serviceProperties, bMatchCase)) {
                    return true;
                }
            }
            return false;
        }
        case sm_iNot:
        {
            return !d->m_listArgs[0].evaluate(serviceProperties, bMatchCase);
        }
        default:
        {
            return false; // Cannot happen
        }
        }
    }
}

const QString QTKLDAPExpr::toString() const
{
    QString res;
    res.append("(");
    if ((d->m_iOperator & sm_iSimple) != 0) {
        res.append(d->m_strAttrName);
        switch (d->m_iOperator) {
        case sm_iEqual:
        {
            res.append("=");
            break;
        }
        case sm_iLess:
        {
            res.append("<=");
            break;
        }
        case sm_iGreater:
        {
            res.append(">=");
            break;
        }
        case sm_iApprox:
        {
            res.append("~=");
            break;
        }
        }

        for (int i = 0; i < d->m_strAttrValue.length(); i++) {
            QChar c = d->m_strAttrValue.at(i);
            if (c ==  '(' || c == ')' || c == '*' || c == '\\') {
                res.append('\\');
            } else if (c == sm_wildCard) {
                c = '*';
            }
            res.append(c);
        }
    } else {
        switch (d->m_iOperator) {
        case sm_iAnd:
        {
            res.append("&");
            break;
        }
        case sm_iOr:
        {
            res.append("|");
            break;
        }
        case sm_iNot:
        {
            res.append("!");
            break;
        }
        }

        for (int i = 0; i < d->m_listArgs.length( ); i++) {
            res.append(d->m_listArgs[i].toString());
        }
    }
    res.append(")");
    return res;
}

QTKLDAPExpr &QTKLDAPExpr::operator=(const QTKLDAPExpr &other)
{
    d = other.d;
    return *this;
}

QTKLDAPExpr::QTKLDAPExpr(int op, const QList<QTKLDAPExpr> &listArgs)
    : d(new QTKLDAPExprData(op, listArgs))
{

}

QTKLDAPExpr::QTKLDAPExpr(int op, const QString &strAttrName, const QString &strAttrValue)
    : d(new QTKLDAPExprData(op, strAttrName, strAttrValue))
{

}

QTKLDAPExpr QTKLDAPExpr::parseExpr(QTKLDAPExpr::ParseState &ps)
{
    ps.skipWhite();
    if (!ps.prefix("(")) {
        ps.error(MALFORMED_QUERY);
    }

    int iOperator;
    ps.skipWhite();
    QChar c = ps.peek();
    if ('&' == c) {
        iOperator = sm_iAnd;
    }else if ('|' == c){
        iOperator = sm_iOr;
    } else if ('!' == c) {
        iOperator = sm_iNot;
    } else {
        return QTKLDAPExpr::parseSimple(ps);
    }
    ps.skip(1); // Ignore the d->m_operator
    QList<QTKLDAPExpr> v;
    do {
        v.append(parseExpr(ps));
        ps.skipWhite();
    } while (ps.peek() == '(');
    int iSize = v.size();
    if (!ps.prefix(")") || iSize == 0 || (iOperator == sm_iNot && iSize > 1)) {
        ps.error(MALFORMED_QUERY);
    }

    return QTKLDAPExpr(iOperator, v);
}

QTKLDAPExpr QTKLDAPExpr::parseSimple(QTKLDAPExpr::ParseState &ps)
{
    QString strAttrName = ps.getAttributeName();
    if (strAttrName.isNull()) {
        ps.error(MALFORMED_QUERY);
    }
    int iOperator = 0;
    if (ps.prefix("=")) {
        iOperator = sm_iEqual;
    } else if (ps.prefix("<=")) {
        iOperator = sm_iLess;
    } else if(ps.prefix(">=")) {
        iOperator = sm_iGreater;
    } else if(ps.prefix("~=")) {
        iOperator = sm_iApprox;
    } else {
        //      System.out.println("undef op='" + ps.peek() + "'");
        ps.error(UNDEFINED_OPERATOR); // Does not return
    }

    QString strAttrValue = ps.getAttributeValue();
    if (!ps.prefix(")")) {
        ps.error(MALFORMED_QUERY);
    }
    return QTKLDAPExpr(iOperator, strAttrName, strAttrValue);
}

bool QTKLDAPExpr::compare(const QVariant &obj, int iOperator, const QString &str) const
{
    if (obj.isNull()) {
        return false;
    }

    if (sm_iEqual == iOperator && sm_strWildCard == str) {
        return true;
    }
    try {
        if (obj.canConvert<QString>()) {
            return QTKLDAPExpr::compareString(obj.toString(), iOperator, str);
        } else if (obj.canConvert<char>()) {
            return QTKLDAPExpr::compareString(obj.toString(), iOperator, str);
        } else if (obj.canConvert<bool>()) {
            if (iOperator==sm_iLess || iOperator==sm_iGreater) {
                return false;
            }
            if (obj.toBool()) {
                return str.compare("true", Qt::CaseInsensitive);
            } else {
                return str.compare("false", Qt::CaseInsensitive);
            }
        } else if (obj.canConvert<Byte>() || obj.canConvert<int>()) {
            switch(iOperator) {
            case sm_iLess:
            {
                return obj.toInt() <= str.toInt();
            }
            case sm_iGreater:
            {
                return obj.toInt() >= str.toInt();
            }
            default: /*APPROX and EQ*/
            {
                return str.toInt( ) == obj.toInt();
            }
            }
        } else if (obj.canConvert<float>()) {
            switch(iOperator) {
            case sm_iLess:
            {
                return obj.toFloat() <= str.toFloat();
            }
            case sm_iGreater:
            {
                return obj.toFloat() >= str.toFloat();
            }
            default: /*APPROX and EQ*/
            {
                return str.toFloat() == obj.toFloat();
            }
            }
        } else if (obj.canConvert<double>()) {
            switch(iOperator) {
            case sm_iLess:
            {
                return obj.toDouble() <= str.toDouble();
            }
            case sm_iGreater:
            {
                return obj.toDouble() >= str.toDouble();
            }
            default: /*APPROX and EQ*/
            {
                return str.toDouble( ) == obj.toDouble();
            }
            }
        } else if (obj.canConvert<qlonglong>()) {
            switch(iOperator) {
            case sm_iLess:
            {
                return obj.toLongLong() <= str.toLongLong();
            }
            case sm_iGreater:
            {
                return obj.toLongLong() >= str.toLongLong();
            }
            default: /*APPROX and EQ*/
            {
                return obj.toLongLong() == str.toLongLong();
            }
            }
        } else if (obj.canConvert< QList<QVariant> >()) {
            QList<QVariant> list = obj.toList();
            QList<QVariant>::Iterator it;
            for (it=list.begin(); it != list.end( ); it++) {
                if (QTKLDAPExpr::compare(*it, iOperator, str)) {
                    return true;
                }
            }
        }
    } catch (...) {
        // This might happen if a QString-to-datatype conversion fails
        // Just consider it a false match and ignore the exception
    }
    return false;
}

bool QTKLDAPExpr::compareString(const QString &str1, int iOperator, const QString &str2)
{
    switch(iOperator) {
    case sm_iLess:
    {
        return str1.compare(str2) <= 0;
    }
    case sm_iGreater:
    {
        return str1.compare(str2) >= 0;
    }
    case sm_iEqual:
    {
        return patSubstr(str1,str2);
    }
    case sm_iApprox:
    {
        return fixupString(str2) == fixupString(str1);
    }
    default:
    {
        return false;
    }
    }
}

QString QTKLDAPExpr::fixupString(const QString &str)
{
    QString sb;
    int iLen = str.length();
    for(int i=0; i<iLen; i++) {
        QChar c = str.at(i);
        if (!c.isSpace()) {
            if (c.isUpper()) {
                c = c.toLower();
            }
            sb.append(c);
        }
    }
    return sb;
}

bool QTKLDAPExpr::patSubstr(const QString &str, const QString &strPat)
{
    return str.isNull() ? false : patSubstr(str,0,strPat,0);
}

bool QTKLDAPExpr::patSubstr(const QString &str, int iSi, const QString &strPat, int iPi)
{
    if (0 == strPat.size( ) - iPi) {
        return 0 == str.size( ) - iSi;
    }
    if (sm_wildCard == QChar(strPat[iPi])) {
        iPi++;
        for (;;) {
            if (QTKLDAPExpr::patSubstr(str, iSi, strPat, iPi)) {
                return true;
            }
            if (str.size( )-iSi == 0) {
                return false;
            }
            iSi++;
        }
    } else {
        if (str.size( ) - iSi == 0){
            return false;
        }
        if(str[iSi] != strPat[iPi]){
            return false;
        }
        return QTKLDAPExpr::patSubstr(str, ++iSi, strPat, ++iPi);
    }
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
