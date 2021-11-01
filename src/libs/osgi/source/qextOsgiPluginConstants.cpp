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

#include "qtkpluginconstants.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const char *QTKPluginConstants::SYSTEM_PLUGIN_LOCATION = "System Plugin";
const char *QTKPluginConstants::SYSTEM_PLUGIN_SYMBOLIC_NAME = "org.qtk.system.runtime";

const char *QTKPluginConstants::FRAMEWORK_VERSION = "org.qtk.pluginfw.version";
const char *QTKPluginConstants::FRAMEWORK_VENDOR = "org.qtk.pluginfw.vendor";
const char *QTKPluginConstants::FRAMEWORK_STORAGE = "org.qtk.pluginfw.storage";
const char *QTKPluginConstants::FRAMEWORK_STORAGE_CLEAN = "org.qtk.pluginfw.storage.clean";
const char *QTKPluginConstants::FRAMEWORK_STORAGE_CLEAN_ON_FIRST_INIT = "onFirstInit";
const char *QTKPluginConstants::FRAMEWORK_LOAD_HINTS = "org.qtk.pluginfw.loadhints";
const char *QTKPluginConstants::FRAMEWORK_PRE_LOADLIBS = "org.qtk.pluginfw.preloadlibs";

const char *QTKPluginConstants::PLUGIN_SYMBOLIC_NAME = "Plugin-SymbolicName";
const char *QTKPluginConstants::PLUGIN_COPYRIGHT = "Plugin-Copyright";
const char *QTKPluginConstants::PLUGIN_DESCRIPTION = "Plugin-Description";
const char *QTKPluginConstants::PLUGIN_NAME = "Plugin-Name";
const char *QTKPluginConstants::PLUGIN_VENDOR = "Plugin-Vendor";
const char *QTKPluginConstants::PLUGIN_LOCALIZATION = "Plugin-Localization";
const char *QTKPluginConstants::PLUGIN_LOCALIZATION_DEFAULT_BASENAME = "QTK-INF/l10n/plugin";
const char *QTKPluginConstants::PLUGIN_VERSION_ATTRIBUTE = "plugin-version";
const char *QTKPluginConstants::PLUGIN_VERSION = "Plugin-Version";
const char *QTKPluginConstants::PLUGIN_ACTIVATION_POLICY = "Plugin-ActivationPolicy";
const char *QTKPluginConstants::PLUGIN_UPDATE_LOCATION = "Plugin-UpdateLocation";
const char *QTKPluginConstants::REQUIRE_PLUGIN = "Require-Plugin";

const char *QTKPluginConstants::ACTIVATION_EAGER = "eager";
const char *QTKPluginConstants::ACTIVATION_LAZY = "lazy";

const char *QTKPluginConstants::RESOLUTION_DIRECTIVE = "resolution";
const char *QTKPluginConstants::RESOLUTION_MANDATORY = "mandatory";
const char *QTKPluginConstants::RESOLUTION_OPTIONAL = "optional";


const char *QTKPluginConstants::OBJECT_CLASS = "objectclass";

// ATTENTION!!! If the value is changed, change also QTKEventConstants::SERVICE_ID
const char *QTKPluginConstants::SERVICE_ID = "service.id";

// ATTENTION!!! If the value is changed, change also QTKEventConstants::SERVICE_PID
const char *QTKPluginConstants::SERVICE_PID = "service.pid";

const char *QTKPluginConstants::SERVICE_RANKING = "service.ranking";
const char *QTKPluginConstants::SERVICE_VENDOR = "service.vendor";
const char *QTKPluginConstants::SERVICE_DESCRIPTION = "service.description";

QTK_PLUGINFRAMEWORK_END_NAMESPACE
