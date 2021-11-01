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

#include "qtkconfiguration.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKConfiguration::~QTKConfiguration()
{
}

bool QTKConfiguration::operator==(const QTKConfiguration& other) const
{
  return this->getPid() == other.getPid();
}

uint qHash(QTKConfigurationPtr configuration)
{
  return qHash(configuration->getPid());
}

bool operator==(const QTKConfigurationPtr& c1, const QTKConfigurationPtr c2)
{
  return (*c1.data()) == (*c2.data());
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
