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

#include "qtkpluginframeworkfactory.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkpluginframeworkproperties_p.h"
#include "qtklocationmanager_p.h"
#include "qtkpluginframework.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @brief QTKPluginFrameworkFactory::QTKPluginFrameworkFactory
 *        Create a new <code>%QTKPluginFrameworkFactory</code> instance.
 * @param initProps The plugin framework configuration properties.
 *        The QTKPluginFramework instance created with #getFramework()
 *        must use some reasonable default configuration if certain
 *        properties are not provided.
 */
QTKPluginFrameworkFactory::QTKPluginFrameworkFactory(const QTKProperties &initProps)
    : m_pPFWContext(nullptr)
{
    QTKPluginFrameworkProperties::setProperties(initProps);
    QTKPluginFrameworkProperties::initializeProperties();
    QTKLocationManager::initializeLocations();
    m_pPFWContext = new QTKPluginFrameworkContext();
}

QTKPluginFrameworkFactory::~QTKPluginFrameworkFactory()
{
    m_pPFWContext->uninit();
    delete m_pPFWContext;
}

/**
 * @brief QTKPluginFrameworkFactory::getFramework
 * @return A new, configured QTKPluginFramework instance. The plugin
 *         framework instance must be in the QTKPlugin::State_Installed state.
 */
QSharedPointer<QTKPluginFramework> QTKPluginFrameworkFactory::getFramework()
{
    return m_pPFWContext->m_pRunTimePlugin;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
