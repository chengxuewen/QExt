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

#include "qtkpluginarchive_p.h"
#include "qtkpluginexception.h"
#include "qtkpluginstorage_p.h"

#include <QStringList>
#include <QFile>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

const char *QTKPluginArchive::AUTO_START_SETTING_STOPPED = "stopped";
const char *QTKPluginArchive::AUTO_START_SETTING_EAGER = "eager";
const char *QTKPluginArchive::AUTO_START_SETTING_ACTIVATION_POLICY = "activation_policy";

QTK_PLUGINFRAMEWORK_END_NAMESPACE
