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

#include "qtkpluginframeworkproperties_p.h"
#include "qtkpluginframeworklauncher.h"

#include <QDir>
#include <QCoreApplication>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QMutex QTKPluginFrameworkProperties::sm_lock;
QTKProperties QTKPluginFrameworkProperties::sm_properties;

QTKProperties &QTKPluginFrameworkProperties::getProperties()
{
    return sm_properties;
}

QVariant QTKPluginFrameworkProperties::getProperty(const QString &strKey)
{
    return QTKPluginFrameworkProperties::getProperty(strKey, QVariant());
}

QVariant QTKPluginFrameworkProperties::getProperty(const QString &strKey, const QVariant &defaultValue)
{
    QMutexLocker locker(&sm_lock);
    QTKProperties::iterator iter = sm_properties.find(strKey);
    if (iter != sm_properties.end()) {
        return iter.value();
    }
    return defaultValue;
}

QVariant QTKPluginFrameworkProperties::setProperty(const QString &strKey, const QVariant &value)
{
    QMutexLocker locker(&sm_lock);
    QVariant oldVal = sm_properties[strKey];
    sm_properties[strKey] = value;
    return oldVal;
}

QVariant QTKPluginFrameworkProperties::clearProperty(const QString &strKey)
{
    QMutexLocker locker(&sm_lock);
    return sm_properties.take(strKey);
}

void QTKPluginFrameworkProperties::setProperties(const QTKProperties &input)
{
    QMutexLocker locker(&sm_lock);
    sm_properties = input;
}

void QTKPluginFrameworkProperties::initializeProperties()
{
    QTKPluginFrameworkProperties::setProperty(QTKPluginFrameworkLauncher::PROPERTIE_USER_HOME, QDir::homePath());
    QTKPluginFrameworkProperties::setProperty(QTKPluginFrameworkLauncher::PROPERTIE_USER_DIR, QDir::currentPath());

    if (QTKPluginFrameworkProperties::getProperty(QTKPluginFrameworkLauncher::PROPERTIE_INSTALL_AREA).isNull()) {
        QTKPluginFrameworkProperties::setProperty(QTKPluginFrameworkLauncher::PROPERTIE_INSTALL_AREA, QCoreApplication::applicationDirPath());
    }
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
