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

#ifndef QTKSERVICEPROPERTIES_P_H
#define QTKSERVICEPROPERTIES_P_H

#include "qtkpluginframework_global.h"

#include <QVarLengthArray>
#include <QVariant>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKServiceProperties class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKServiceProperties
{
public:
    QTKServiceProperties(const QTKProperties &properties);

    QVariant value(const QString &strKey) const;
    QVariant value(int iIndex) const;

    int find(const QString &strKey) const;
    int findCaseSensitive(const QString &strKey) const;

    QStringList keys() const;

private:
    QVarLengthArray<QString, 10> m_ks;
    QVarLengthArray<QVariant, 10> m_vs;
    QMap<QString, QVariant> m_map;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKSERVICEPROPERTIES_P_H
