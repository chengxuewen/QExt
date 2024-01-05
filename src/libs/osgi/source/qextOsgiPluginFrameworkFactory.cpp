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

#include <qextOsgiPluginFrameworkFactory.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <private/qextOsgiPluginFrameworkProperties_p.h>
#include <private/qextOsgiLocationManager_p.h>

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkFactory::QExtOsgiPluginFrameworkFactory(const QExtOsgiProperties& initProps)
    : fwCtx(NULL)
{
    QExtOsgiPluginFrameworkProperties::setProperties(initProps);
    QExtOsgiPluginFrameworkProperties::initializeProperties();

    QExtOsgiLocationManager::initializeLocations();

    fwCtx = new QExtOsgiPluginFrameworkContext();
}

//----------------------------------------------------------------------------
QExtOsgiPluginFrameworkFactory::~QExtOsgiPluginFrameworkFactory()
{
    fwCtx->uninit();
    delete fwCtx;
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPluginFramework> QExtOsgiPluginFrameworkFactory::getFramework()
{
    return fwCtx->systemPlugin;
}
