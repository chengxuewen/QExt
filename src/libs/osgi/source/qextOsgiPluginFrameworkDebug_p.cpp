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

#include "qtkpluginframeworkdebug_p.h"
#include "qtkpluginframeworkdebugoptions_p.h"
#include "qtkpluginframeworkproperties_p.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

static QString sg_strQTKOSGI = "org.qtk.pluginfw";

const QString QTKPluginFrameworkDebug::OPTION_DEBUG_GENERAL = sg_strQTKOSGI + "/debug";
const QString QTKPluginFrameworkDebug::OPTION_DEBUG_FRAMEWORK = sg_strQTKOSGI + "/debug/framework";
const QString QTKPluginFrameworkDebug::OPTION_DEBUG_ERRORS = sg_strQTKOSGI + "/debug/errors";
const QString QTKPluginFrameworkDebug::OPTION_DEBUG_HOOKS = sg_strQTKOSGI + "/debug/hooks";
const QString QTKPluginFrameworkDebug::OPTION_DEBUG_LAZY_ACTIVATION = sg_strQTKOSGI + "/debug/lazy_activation";
const QString QTKPluginFrameworkDebug::OPTION_DEBUG_LDAP = sg_strQTKOSGI + "/debug/ldap";
const QString QTKPluginFrameworkDebug::OPTION_DEBUG_SERVICE_REFERENCE = sg_strQTKOSGI + "/debug/service_reference";
const QString QTKPluginFrameworkDebug::OPTION_DEBUG_STARTLEVEL = sg_strQTKOSGI + "/debug/startlevel";
const QString QTKPluginFrameworkDebug::OPTION_DEBUG_URL = sg_strQTKOSGI + "/debug/url";
const QString QTKPluginFrameworkDebug::OPTION_DEBUG_RESOLVE = sg_strQTKOSGI + "/debug/resolve";

QTKPluginFrameworkDebug::QTKPluginFrameworkDebug()
{
    QTKPluginFrameworkDebugOptions *pDebugOptions = QTKPluginFrameworkDebugOptions::getDefault();
    if (nullptr != pDebugOptions) {
        bGeneralEnabled = pDebugOptions->isDebugEnabled();
        bErrorsEnabled = pDebugOptions->getBooleanOption(OPTION_DEBUG_ERRORS, false);
        bFrameworkEnabled = pDebugOptions->getBooleanOption(OPTION_DEBUG_FRAMEWORK, false);
        bHooksEnabled = pDebugOptions->getBooleanOption(OPTION_DEBUG_HOOKS, false);
        bLazyActivationEnabled = pDebugOptions->getBooleanOption(OPTION_DEBUG_LAZY_ACTIVATION, false);
        bLdapEnabled = pDebugOptions->getBooleanOption(OPTION_DEBUG_LDAP, false);
        bServiceReferenceEnabled = pDebugOptions->getBooleanOption(OPTION_DEBUG_SERVICE_REFERENCE, false);
        bStartLevelEnabled = pDebugOptions->getBooleanOption(OPTION_DEBUG_STARTLEVEL, false);
        bUrlEnabled = pDebugOptions->getBooleanOption(OPTION_DEBUG_URL, false);
        bResolveEnabled = pDebugOptions->getBooleanOption(OPTION_DEBUG_RESOLVE, false);
    }
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
