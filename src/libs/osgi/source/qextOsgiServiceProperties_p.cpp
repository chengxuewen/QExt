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

#include "qtkserviceproperties_p.h"

#include <QTKCore/QTKException>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKServiceProperties::QTKServiceProperties(const QTKProperties &properties)
{
    for(QTKProperties::ConstIterator iter = properties.begin(), end = properties.end(); iter != end; ++iter) {
        if (this->find(iter.key()) != -1) {
            QString strMsg("QTKProperties object contains case variants of the key: ");
            strMsg += iter.key();
            throw QTKInvalidArgumentException(strMsg);
        }
        m_ks.append(iter.key());
        m_vs.append(iter.value());
    }
}

QVariant QTKServiceProperties::value(const QString &strKey) const
{
    int iIndex = find(strKey);
    if (iIndex < 0) {
        return QVariant();
    }
    return m_vs[iIndex];
}

QVariant QTKServiceProperties::value(int iIndex) const
{
    return (iIndex < 0 || iIndex >= m_vs.size()) ? QVariant() : m_vs[iIndex];
}

int QTKServiceProperties::find(const QString &strKey) const
{
    for (int i = 0; i < m_ks.size(); ++i) {
        if (m_ks[i].compare(strKey, Qt::CaseInsensitive) == 0) {
            return i;
        }
    }
    return -1;
}

int QTKServiceProperties::findCaseSensitive(const QString &strKey) const
{
    for (int i = 0; i < m_ks.size(); ++i) {
        if (m_ks[i] == strKey) {
            return i;
        }
    }
    return -1;
}

QStringList QTKServiceProperties::keys() const
{
    QStringList listResult;
    for(int i = 0; i < m_ks.size(); ++i) {
        listResult.append(m_ks[i]);
    }
    return listResult;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
