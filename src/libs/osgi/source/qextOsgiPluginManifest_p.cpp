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

#include "qtkpluginmanifest_p.h"

#include <QTKCore/QTKException>

#include <QStringList>
#include <QIODevice>
#include <QDebug>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKPluginManifest::QTKPluginManifest()
{

}

QTKPluginManifest::QTKPluginManifest(const QByteArray &in)
{
    this->read(in);
}

void QTKPluginManifest::read(const QByteArray &in)
{
    m_mainAttributes.clear();
    m_mapSections.clear();

    QString strKey;
    QString strValue;
    QString strCurrSection;

    QList<QByteArray> listLines = in.split('\n');

    foreach (const QString &strLine, listLines)
    {
        // skip empty lines and comments
        if (strLine.trimmed().isEmpty() | strLine.startsWith('#')) {
            continue;
        }

        // a valid new key/value pair starts with no white-space and contains
        // either a ':' or a '='
        if (!(strLine.startsWith(' ') || strLine.startsWith('\t')) && (strLine.contains(':') || strLine.contains('='))) {

            // see if we found a new section header
            if (strLine.startsWith('[')) {
                strCurrSection = strLine.mid(1, strLine.indexOf(']')-1);
            } else {
                // we found a new key/value pair, save the old one
                if (!strKey.isEmpty()) {
                    if (strCurrSection.isEmpty()) {
                        m_mainAttributes.insert(strKey, strValue);
                    } else {
                        m_mapSections[strCurrSection].insert(strKey, strValue);
                    }
                }

                int iColonIndex = strLine.indexOf(':');
                int iEqualIndex = strLine.indexOf('=');

                int iepIndex = -1;
                if (iColonIndex < 0) {
                    iepIndex = iEqualIndex;
                } else if (iEqualIndex < 0) {
                    iepIndex = iColonIndex;
                } else {
                    iepIndex = iColonIndex < iEqualIndex ? iColonIndex : iEqualIndex;
                }

                strKey = strLine.left(iepIndex);
                strValue = strLine.right(strLine.size()-(iepIndex+1)).trimmed();
            }
        } else {
            // add the line to the value
            strValue += strLine;
        }
    }

    // save the last key/value pair
    if (!strKey.isEmpty()) {
        if (strCurrSection.isEmpty()) {
            m_mainAttributes.insert(strKey, strValue);
        } else {
            m_mapSections[strCurrSection].insert(strKey, strValue);
        }
    }
}

QTKPluginManifest::Attributes QTKPluginManifest::getMainAttributes() const
{
    return m_mainAttributes;
}

QString QTKPluginManifest::getAttribute(const QString &strKey) const
{
    if (!m_mainAttributes.contains(strKey)) {
        return QString();
    }
    return m_mainAttributes[strKey];
}

QTKPluginManifest::Attributes QTKPluginManifest::getAttributes(const QString &strSection) const
{
    if (!m_mapSections.contains(strSection)) {
        throw QTKInvalidArgumentException(QString("Manifest section invalid: ") + strSection);
    }

    return m_mapSections[strSection];
}

QStringList QTKPluginManifest::getSections() const
{
    return m_mapSections.keys();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
