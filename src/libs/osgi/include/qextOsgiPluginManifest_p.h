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

#ifndef QTKPLUGINMANIFEST_P_H
#define QTKPLUGINMANIFEST_P_H

#include "qtkpluginframework_global.h"

#include <QHash>
#include <QStringList>

class QIODevice;

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginManifest class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginManifest
{
public:
    typedef QHash<QString,QString> Attributes;

    QTKPluginManifest();
    QTKPluginManifest(const QByteArray &in);

    void read(const QByteArray &in);

    Attributes getMainAttributes() const;
    QString getAttribute(const QString &strKey) const;
    Attributes getAttributes(const QString &strSection) const;
    QStringList getSections() const;

private:
    Attributes m_mainAttributes;
    QHash<QString, Attributes> m_mapSections;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINMANIFEST_P_H
