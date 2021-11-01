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

#include "qtkeventconstants.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const char *QTKEventConstants::EVENT_TOPICS = "event.topics";
const char *QTKEventConstants::EVENT_FILTER = "event.filter";

const char *QTKEventConstants::EVENT_DELIVERY = "event.delivery";
const char *QTKEventConstants::DELIVERY_ASYNC_ORDERED = "async.ordered";
const char *QTKEventConstants::DELIVERY_ASYNC_UNORDERED = "async.unordered";

const char *QTKEventConstants::PLUGIN_SYMBOLIC_NAME = "plugin.symbolicName";
const char *QTKEventConstants::PLUGIN_ID = "plugin.id";
const char *QTKEventConstants::PLUGIN = "plugin";
const char *QTKEventConstants::PLUGIN_VERSION = "plugin.version";

const char *QTKEventConstants::EVENT = "event";
const char *QTKEventConstants::EXCEPTION = "exception";
const char *QTKEventConstants::EXCEPTION_CLASS = "exception.class";
const char *QTKEventConstants::EXCEPTION_MESSAGE = "exception.message";
const char *QTKEventConstants::MESSAGE = "message";
const char *QTKEventConstants::SERVICE = "service";
const char *QTKEventConstants::SERVICE_ID = "service.id";
const char *QTKEventConstants::SERVICE_OBJECT_CLASS = "service.objectClass";
const char *QTKEventConstants::SERVICE_PID = "service.pid";
const char *QTKEventConstants::TIME_STAMP = "timestamp";

QTK_PLUGINFRAMEWORK_END_NAMESPACE
