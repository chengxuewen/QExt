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

#include <private/qextOsgiPlugin_p.h>
#include <private/qextOsgiRequirePlugin_p.h>
#include <qextOsgiPluginConstants.h>

//----------------------------------------------------------------------------
QExtOsgiRequirePlugin::QExtOsgiRequirePlugin(QExtOsgiPluginPrivate *requestor,
                                   const QString &name, const QString &res,
                                   const QString &range)
    : name(name),
    resolution(res.isEmpty() ? QExtOsgiPluginConstants::RESOLUTION_MANDATORY : res),
    pluginRange(range.isEmpty() ? QExtOsgiVersionRange::defaultVersionRange() : range)
{

    if (resolution != QExtOsgiPluginConstants::RESOLUTION_MANDATORY &&
        resolution != QExtOsgiPluginConstants::RESOLUTION_OPTIONAL )
    {
        QString what = QString("Invalid directive : '")
                       + QExtOsgiPluginConstants::RESOLUTION_DIRECTIVE + ":=" + this->resolution
                       + "' in manifest header '"
                       + QExtOsgiPluginConstants::REQUIRE_PLUGIN + ": " + this->name
                       + "' of plugin with id " + requestor->id
                       + " (" + requestor->symbolicName + ")"
                       + ". The value must be either '"
                       + QExtOsgiPluginConstants::RESOLUTION_MANDATORY + "' or '"
                       + QExtOsgiPluginConstants::RESOLUTION_OPTIONAL  + "'.";
        throw QExtInvalidArgumentException(what);
    }


}

//----------------------------------------------------------------------------
bool QExtOsgiRequirePlugin::overlap(const QExtOsgiRequirePlugin& rp) const
{
    if (resolution == QExtOsgiPluginConstants::RESOLUTION_MANDATORY &&
        rp.resolution != QExtOsgiPluginConstants::RESOLUTION_MANDATORY)
    {
        return false;
    }
    return pluginRange.withinRange(rp.pluginRange);

}
