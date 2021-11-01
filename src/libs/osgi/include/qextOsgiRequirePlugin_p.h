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

#ifndef QTKREQUIREPLUGIN_P_H
#define QTKREQUIREPLUGIN_P_H

#include "qtkversionrange_p.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginPrivate;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKRequirePlugin class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKRequirePlugin
{
public:
    QTKRequirePlugin(QTKPluginPrivate *pRequestor,
                     const QString &strName, const QString &strRes,
                     const QString &strRange);
    bool overlap(const QTKRequirePlugin &requirePlugin) const;

    const QString m_strName;
    const QString m_strResolution;
    const QTKVersionRange m_pluginRange;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKREQUIREPLUGIN_P_H
