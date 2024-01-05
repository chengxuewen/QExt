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

#include <private/qextOsgiPluginFrameworkProperties_p.h>
#include <qextOsgiPluginFrameworkLauncher.h>

#include <QDir>
#include <QCoreApplication>

QMutex QExtOsgiPluginFrameworkProperties::lock;
QExtOsgiProperties QExtOsgiPluginFrameworkProperties::properties;

//----------------------------------------------------------------------------
QExtOsgiProperties& QExtOsgiPluginFrameworkProperties::getProperties()
{
    return properties;
}

//----------------------------------------------------------------------------
QVariant QExtOsgiPluginFrameworkProperties::getProperty(const QString& key)
{
    return getProperty(key, QVariant());
}

//----------------------------------------------------------------------------
QVariant QExtOsgiPluginFrameworkProperties::getProperty(const QString& key, const QVariant& defaultValue)
{
    QMutexLocker l(&lock);
    QExtOsgiProperties::iterator iter = properties.find(key);
    if (iter != properties.end()) return iter.value();
    return defaultValue;
}

//----------------------------------------------------------------------------
QVariant QExtOsgiPluginFrameworkProperties::setProperty(const QString& key, const QVariant& value)
{
    QMutexLocker l(&lock);
    QVariant oldVal = properties[key];
    properties[key] = value;
    return oldVal;
}

//----------------------------------------------------------------------------
QVariant QExtOsgiPluginFrameworkProperties::clearProperty(const QString& key)
{
    QMutexLocker l(&lock);
    return properties.take(key);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkProperties::setProperties(const QExtOsgiProperties& input)
{
    QMutexLocker l(&lock);
    properties = input;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginFrameworkProperties::initializeProperties()
{
    // initialize some framework properties that must always be set

    setProperty(QExtOsgiPluginFrameworkLauncher::PROP_USER_HOME, QDir::homePath());
    setProperty(QExtOsgiPluginFrameworkLauncher::PROP_USER_DIR, QDir::currentPath());

    if (getProperty(QExtOsgiPluginFrameworkLauncher::PROP_INSTALL_AREA).isNull())
    {
        setProperty(QExtOsgiPluginFrameworkLauncher::PROP_INSTALL_AREA, QCoreApplication::applicationDirPath());
    }
}
