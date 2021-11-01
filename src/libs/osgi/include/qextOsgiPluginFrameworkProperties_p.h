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

#ifndef QTKPLUGINFRAMEWORKPROPERTIES_P_H
#define QTKPLUGINFRAMEWORKPROPERTIES_P_H

#include "qtkpluginframework_global.h"

#include <QMutex>
#include <QMutexLocker>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginFrameworkProperties class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginFrameworkProperties
{
public:
    static QTKProperties &getProperties();
    static QVariant getProperty(const QString &strKey);
    static QVariant getProperty(const QString &strKey, const QVariant &defaultValue);
    static QVariant setProperty(const QString &strKey, const QVariant &value);
    static QVariant clearProperty(const QString &strKey);
    static void setProperties(const QTKProperties &input);
    static void initializeProperties();

private:
  static QMutex sm_lock;
  static QTKProperties sm_properties;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINFRAMEWORKPROPERTIES_P_H
