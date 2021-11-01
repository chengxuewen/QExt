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

#include "qtkapplicationdescriptor.h"
#include "../../qtkpluginconstants.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const char *QTKApplicationDescriptor::APPLICATION_NAME = "application.name";
const char *QTKApplicationDescriptor::APPLICATION_ICON = "application.icon";
const char *QTKApplicationDescriptor::APPLICATION_PID = QTKPluginConstants::SERVICE_PID;
const char *QTKApplicationDescriptor::APPLICATION_VERSION = "application.version";
const char *QTKApplicationDescriptor::APPLICATION_VENDOR = QTKPluginConstants::SERVICE_VENDOR;
const char *QTKApplicationDescriptor::APPLICATION_VISIBLE = "application.visible";
const char *QTKApplicationDescriptor::APPLICATION_LAUNCHABLE = "application.launchable";
const char *QTKApplicationDescriptor::APPLICATION_LOCKED = "application.locked";
const char *QTKApplicationDescriptor::APPLICATION_DESCRIPTION = "application.description";
const char *QTKApplicationDescriptor::APPLICATION_DOCUMENTATION = "application.documentation";
const char *QTKApplicationDescriptor::APPLICATION_COPYRIGHT = "application.copyright";
const char *QTKApplicationDescriptor::APPLICATION_LICENSE = "application.license";
const char *QTKApplicationDescriptor::APPLICATION_CONTAINER = "application.container";
const char *QTKApplicationDescriptor::APPLICATION_LOCATION = "application.location";

QTK_PLUGINFRAMEWORK_END_NAMESPACE
