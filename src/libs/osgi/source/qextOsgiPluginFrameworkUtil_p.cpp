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

#include "qtkpluginframeworkutil_p.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtklocationmanager_p.h"
#include "qtkbasiclocation_p.h"

#include <QTKCore/QTKException>

#include <QString>
#include <QCoreApplication>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class AttributeTokenizer
{
public:
    QString m_str;
    int m_iLength;
    int m_iPos;

    AttributeTokenizer(const QString &strInput)
        : m_str(strInput),
          m_iLength(strInput.size()),
          m_iPos(0)
    {

    }

    QString getWord() {
        this->skipWhite();
        bool bBackslash = false;
        bool bQuote = false;
        QString strVal;
        int iEnd = 0;
        for (; m_iPos < m_iLength; m_iPos++) {
            bool bBreakLoop = false;
            if (bBackslash) {
                bBackslash = false;
                strVal.append(m_str.at(m_iPos));
            } else {
                QChar c = m_str.at(m_iPos);
                switch (c.toLatin1())
                {
                case '"':
                {
                    bQuote = !bQuote;
                    iEnd = strVal.length();
                    break;
                }
                case '\\':
                {
                    bBackslash = true;
                    break;
                }
                case ',':
                case ':':
                case ';':
                case '=':
                {
                    if (!bQuote) {
                        bBreakLoop = true;
                        break;
                    }
                }
                default:
                {
                    strVal.append(c);
                    if (!c.isSpace()) {
                        iEnd = strVal.length();
                    }
                    break;
                }
                }
                if (bBreakLoop) {
                    break;
                }
            }
        }

        if (bQuote || bBackslash || iEnd == 0) {
            return QString();
        }
        return strVal.left(iEnd);
    }

    QString getKey() {
        if (m_iPos >= m_iLength) {
            return QString();
        }
        int iSave = m_iPos;
        if (m_str.at(m_iPos) == ';') {
            m_iPos++;
        }
        QString strRes = getWord();
        if (!strRes.isNull()) {
            if (m_iPos == m_iLength) {
                return strRes;
            }
            QChar c = m_str.at(m_iPos);
            if (c == ';' || c == ',') {
                return strRes;
            }
        }
        m_iPos = iSave;
        return QString();
    }

    QString getParam() {
        if (m_iPos == m_iLength || m_str.at(m_iPos) != ';') {
            return QString();
        }
        int iSave = m_iPos++;
        QString strRes = getWord();
        if (!strRes.isNull()) {
            if (m_iPos < m_iLength && m_str.at(m_iPos) == '=') {
                return strRes;
            }
            if (m_iPos + 1 < m_iLength && m_str.at(m_iPos) == ':' && m_str.at(m_iPos+1) == '=') {
                return strRes;
            }
        }
        m_iPos = iSave;
        return QString();
    }

    bool isDirective() {
        if (m_iPos + 1 < m_iLength && m_str.at(m_iPos) == ':') {
            m_iPos++;
            return true;
        } else {
            return false;
        }
    }

    QString getValue() {
        if (m_str.at(m_iPos) != '=') {
            return QString();
        }
        int iSave = m_iPos++;
        this->skipWhite();
        QString strVal = this->getWord();
        if (strVal.isNull()) {
            m_iPos = iSave;
            return QString();
        }
        return strVal;
    }

    bool getEntryEnd() {
        int iSave = m_iPos;
        this->skipWhite();
        if (m_iPos == m_iLength) {
            return true;
        } else if (m_str.at(m_iPos) == ',') {
            m_iPos++;
            return true;
        } else {
            m_iPos = iSave;
            return false;
        }
    }

    bool getEnd() {
        int iSave = m_iPos;
        this->skipWhite();
        if (m_iPos == m_iLength) {
            return true;
        } else {
            m_iPos = iSave;
            return false;
        }
    }

    QString getRest() {
        QString strRes = m_str.mid(m_iPos).trimmed();
        return strRes.length() == 0 ? "<END OF LINE>" : strRes;
    }

private:
    void skipWhite() {
        for (; m_iPos < m_iLength; m_iPos++) {
            if (!m_str.at(m_iPos).isSpace()) {
                break;
            }
        }
    }
};

QList<QMap<QString, QStringList> > QTKPluginFrameworkUtil::parseEntries(const QString &strAttribute, const QString &strText,
                                                                        bool bSingle, bool bUnique, bool bSingleEntry)
{
    QList<QMap<QString, QStringList> > listResult;
    if (!strText.isNull()) {
        AttributeTokenizer at(strText);
        do {
            QList<QString> listKeys;
            QMap<QString, QStringList > mapParams;
            QStringList listDirectives;

            QString strKey = at.getKey();
            if (strKey.isNull()) {
                QString strWhat = QString("Definition, ") + strAttribute + ", expected key at: " + at.getRest()
                        + ". Key values are terminated by a ';' or a ',' and may not "
                        + "contain ':', '='.";
                throw QTKInvalidArgumentException(strWhat);
            }
            if (!bSingle) {
                listKeys.push_back(strKey);
                while (!(strKey = at.getKey()).isNull()) {
                    listKeys.push_back(strKey);
                }
            }
            QString strParam;
            while (!(strParam = at.getParam()).isNull()) {
                QStringList &listOld = mapParams[strParam];
                bool bIsDirective = at.isDirective();
                if (!listOld.isEmpty() && bUnique) {
                    QString strWhat = QString("Definition, ") + strAttribute + ", duplicate " +
                            (bIsDirective ? "directive" : "attribute") +
                            ": " + strParam;
                    throw QTKInvalidArgumentException(strWhat);
                }
                QString strValue = at.getValue();
                if (strValue.isNull()) {
                    QString strWhat = QString("Definition, ") + strAttribute + ", expected value at: " + at.getRest();
                    throw QTKInvalidArgumentException(strWhat);
                }
                if (bIsDirective) {
                    // NYI Handle directives and check them
                    listDirectives.push_back(strParam);
                }
                if (bUnique) {
                    mapParams.insert(strParam, QStringList(strValue));
                } else {
                    listOld.push_back(strValue);
                }
            }

            if (at.getEntryEnd()) {
                if (bSingle) {
                    mapParams.insert("$key", QStringList(strKey));
                } else {
                    mapParams.insert("$keys", listKeys);
                }
                listResult.push_back(mapParams);
            } else {
                QString strWhat = QString("Definition, ") + strAttribute + ", expected end of entry at: " + at.getRest();
                throw QTKInvalidArgumentException(strWhat);
            }

            if (bSingleEntry && !at.getEnd()) {
                QString strWhat = QString("Definition, ") + strAttribute + ", expected end of single entry at: " + at.getRest();
                throw QTKInvalidArgumentException(strWhat);
            }

            mapParams.insert("$directives", listDirectives); // $ is not allowed in
            // param names...
        } while (!at.getEnd());
    }
    return listResult;
}

QString QTKPluginFrameworkUtil::getFrameworkDir(QTKPluginFrameworkContext *pPFWContext)
{
    Q_UNUSED(pPFWContext)
    QTKLocation *pLocation = QTKLocationManager::getConfigurationLocation();
    if (pLocation) {
        return pLocation->getUrl().toLocalFile();
    }
    return QString();
}

QDir QTKPluginFrameworkUtil::getFileStorage(QTKPluginFrameworkContext *pPFWContext,
                                            const QString &strName)
{
    // See if we have a storage directory
    QString strPFWDir = QTKPluginFrameworkUtil::getFrameworkDir(pPFWContext);
    if (strPFWDir.isEmpty()) {
        throw QTKRuntimeException("The framework storge directory is empty");
    }
    QDir dir(strPFWDir + "/" + strName);
    if (dir.exists()) {
        if (!QFileInfo(dir.absolutePath()).isDir()) {
            QString strMsg("Not a directory: ");
            strMsg.append(dir.absolutePath());
            throw QTKRuntimeException(strMsg);
        }
    } else {
        if (!dir.mkpath(dir.absolutePath())) {
            QString strMsg("Cannot create directory: ");
            strMsg.append(dir.absolutePath());
            throw QTKRuntimeException(strMsg);
        }
    }
    return dir;
}

bool QTKPluginFrameworkUtil::filterMatch(const QString &strFilter, const QString &str)
{
    return QTKPluginFrameworkUtil::patSubstr(str, 0, strFilter, 0);
}

bool QTKPluginFrameworkUtil::patSubstr(const QString &str, int iSi, const QString &strPat, int iPi)
{
    if (strPat.length() - iPi == 0) {
        return str.length() - iSi == 0;
    }
    if (strPat[iPi] == '*') {
        iPi++;
        for (;;) {
            if (QTKPluginFrameworkUtil::patSubstr(str, iSi, strPat, iPi)) {
                return true;
            }
            if (str.length() - iSi == 0) {
                return false;
            }
            iSi++;
        }
    } else {
        if (str.length() - iSi == 0 ) {
            return false;
        }
        if(str[iSi] != strPat[iPi]) {
            return false;
        }
        return QTKPluginFrameworkUtil::patSubstr(str, ++iSi, strPat, ++iPi);
    }
}

bool pluginIdLessThan(const QSharedPointer<QTKPlugin> &plugin1, const QSharedPointer<QTKPlugin> &plugin2)
{
    return plugin1->getPluginId() < plugin2->getPluginId();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
