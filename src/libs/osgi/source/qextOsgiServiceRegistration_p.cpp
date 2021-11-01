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

#include "qtkserviceregistration_p.h"
#include "qtkplugin_p.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKServiceRegistrationPrivate::QTKServiceRegistrationPrivate(QTKPluginPrivate *pPlugin, QObject *pService,
                                                             const QTKDictionary &props)
    : m_pPluginPrivate(pPlugin),
      m_reference(this),
      m_properties(props),
      m_bAvailable(true),
      m_bUnregistering(false),
      m_ref(1),
      m_pService(pService)
{

}

QTKServiceRegistrationPrivate::~QTKServiceRegistrationPrivate()
{

}

bool QTKServiceRegistrationPrivate::isUsedByPlugin(QSharedPointer<QTKPlugin> pPluginPrivate)
{
    QHash<QSharedPointer<QTKPlugin>, int> mapDeps = m_mapDependents;
    return mapDeps.contains(pPluginPrivate);
}

QObject *QTKServiceRegistrationPrivate::getService()
{
    return m_pService;
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
