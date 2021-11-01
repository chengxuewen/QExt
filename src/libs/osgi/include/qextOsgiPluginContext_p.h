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

#ifndef QTKPLUGINCONTEXT_P_H
#define QTKPLUGINCONTEXT_P_H

#include "qtkpluginframework_global.h"

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginPrivate;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginContextPrivate class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginContextPrivate
{
public:
    QTKPluginContextPrivate(QTKPluginPrivate *pPlugin);

    /**
     * @brief isPluginContextValid
     * Check that the plugin is still valid.
     */
    void isPluginContextValid() const; //Check that the plugin is still valid.

    void invalidate();

    QTKPluginPrivate *m_pPlugin;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINCONTEXT_P_H
