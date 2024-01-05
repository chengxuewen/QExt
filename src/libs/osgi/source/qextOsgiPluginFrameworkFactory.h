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

#ifndef _QEXTOSGIPLUGINFRAMEWORKFACTORY_H
#define _QEXTOSGIPLUGINFRAMEWORKFACTORY_H

#include <qextOsgiGlobal.h>
#include <qextOsgiPluginFrameworkGlobal.h>


#include <QHash>
#include <QString>
#include <QVariant>
#include <QSharedPointer>

class QExtOsgiPluginFramework;
class QExtOsgiPluginFrameworkContext;

/**
 * \ingroup PluginFramework
 * A factory for creating QExtOsgiPluginFramework instances.
 */
class QEXT_OSGI_API QExtOsgiPluginFrameworkFactory
{

public:

    /**
   * Create a new <code>%QExtOsgiPluginFrameworkFactory</code> instance.
   *
   * <p>
   * The QExtOsgiProperties map is used to configure the QExtOsgiPluginFramework. The
   * plugin framework instance created with #getFramework() must interpret
   * the following properties:
   *
   * <p>
   * <ul><li>QExtOsgiPluginConstants::FRAMEWORK_STORAGE</li>
   * </ul>
   *
   * @param initProps The plugin framework configuration properties.
   *        The QExtOsgiPluginFramework instance created with #getFramework()
   *        must use some reasonable default configuration if certain
   *        properties are not provided.
   */
    QExtOsgiPluginFrameworkFactory(const QExtOsgiProperties& initProps = QExtOsgiProperties());

    ~QExtOsgiPluginFrameworkFactory();

    /**
   * Create a new QExtOsgiPluginFramework instance.
   *
   * @return A new, configured QExtOsgiPluginFramework instance. The plugin
   *         framework instance must be in the QExtOsgiPlugin::INSTALLED state.
   */
    QSharedPointer<QExtOsgiPluginFramework> getFramework();

private:

    QExtOsgiPluginFrameworkContext* fwCtx;

};


#endif // _QEXTOSGIPLUGINFRAMEWORKFACTORY_H
