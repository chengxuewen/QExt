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

#include "qtkrequireplugin_p.h"
#include "qtkpluginconstants.h"
#include "qtkrequireplugin_p.h"
#include "qtkplugin_p.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKRequirePlugin::QTKRequirePlugin(QTKPluginPrivate *pRequestor,
                                   const QString &strName, const QString &strRes,
                                   const QString &strRange)
    : m_strName(strName),
      m_strResolution(strRes.isEmpty() ? QTKPluginConstants::RESOLUTION_MANDATORY : strRes),
      m_pluginRange(strRange.isEmpty() ? QTKVersionRange::defaultVersionRange() : strRange)
{

    if (m_strResolution != QTKPluginConstants::RESOLUTION_MANDATORY &&
            m_strResolution != QTKPluginConstants::RESOLUTION_OPTIONAL ) {
        QString strWhat = QString("Invalid directive : '")
                + QTKPluginConstants::RESOLUTION_DIRECTIVE + ":=" + this->m_strResolution
                + "' in manifest header '"
                + QTKPluginConstants::REQUIRE_PLUGIN + ": " + this->m_strName
                + "' of plugin with id " + pRequestor->m_lId
                + " (" + pRequestor->m_strSymbolicName + ")"
                + ". The value must be either '"
                + QTKPluginConstants::RESOLUTION_MANDATORY + "' or '"
                + QTKPluginConstants::RESOLUTION_OPTIONAL  + "'.";
        throw QTKInvalidArgumentException(strWhat);
    }
}

bool QTKRequirePlugin::overlap(const QTKRequirePlugin &requirePlugin) const
{
    if (m_strResolution == QTKPluginConstants::RESOLUTION_MANDATORY &&
            requirePlugin.m_strResolution != QTKPluginConstants::RESOLUTION_MANDATORY) {
        return false;
    }

    return m_pluginRange.withinRange(requirePlugin.m_pluginRange);
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
