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

#ifndef QTKPLUGINFRAMEWORKFACTORY_H
#define QTKPLUGINFRAMEWORKFACTORY_H

#include "qtkpluginframework_global.h"

#include <QHash>
#include <QString>
#include <QVariant>
#include <QSharedPointer>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginFramework;
class QTKPluginFrameworkContext;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFrameworkFactory class
 * A factory for creating QTKPluginFramework instances.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFrameworkFactory
{
public:
    /**
     * @brief QTKPluginFrameworkFactory
     * Create a new <code>%QTKPluginFrameworkFactory</code> instance.
     *
     * <p>
     * The QTKProperties map is used to configure the QTKPluginFramework. The
     * plugin framework instance created with #getFramework() must interpret
     * the following properties:
     *
     * <p>
     * <ul><li>QTKPluginConstants::FRAMEWORK_STORAGE</li>
     * </ul>
     *
     * @param initProps The plugin framework configuration properties.
     *        The QTKPluginFramework instance created with #getFramework()
     *        must use some reasonable default configuration if certain
     *        properties are not provided.
     */
    QTKPluginFrameworkFactory(const QTKProperties &initProps = QTKProperties());
    ~QTKPluginFrameworkFactory();

    /**
     * @brief getFramework
     * Create a new QTKPluginFramework instance.
     *
     * @return A new, configured QTKPluginFramework instance. The plugin
     *         framework instance must be in the QTKPlugin::INSTALLED state.
     */
    QSharedPointer<QTKPluginFramework> getFramework();

private:
    QTKPluginFrameworkContext *m_pPFWContext;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINFRAMEWORKFACTORY_H
