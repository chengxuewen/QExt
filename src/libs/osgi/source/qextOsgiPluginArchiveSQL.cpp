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

#include <private/qextOsgiPluginArchiveSQL_p.h>
#include <private/qextOsgiPluginStorageSQL_p.h>
#include <qextOsgiPluginDatabaseException.h>
#include <qextOsgiPluginException.h>

#include <QStringList>
#include <QFile>


//----------------------------------------------------------------------------
QExtOsgiPluginArchiveSQL::QExtOsgiPluginArchiveSQL(QExtOsgiPluginStorageSQL* pluginStorage,
                                                   const QUrl &pluginLocation, const QString &localPluginPath,
                                                   int pluginId, int startLevel, const QDateTime& lastModified,
                                                   int autostartSetting)
    : key(-1), autostartSetting(autostartSetting), id(pluginId), generation(0)
    , startLevel(startLevel), lastModified(lastModified), location(pluginLocation)
    , localPluginPath(localPluginPath), storage(pluginStorage)
{
}

//----------------------------------------------------------------------------
QExtOsgiPluginArchiveSQL::QExtOsgiPluginArchiveSQL(QSharedPointer<QExtOsgiPluginArchiveSQL> old, int generation,
                                                   const QUrl &pluginLocation, const QString &localPluginPath)
    : key(-1), autostartSetting(old->autostartSetting), id(old->id), generation(generation)
    , startLevel(0), location(pluginLocation), localPluginPath(localPluginPath)
    , storage(old->storage)
{
}

void QExtOsgiPluginArchiveSQL::readManifest(const QByteArray& manifestResource)
{
    QByteArray manifestRes = manifestResource.isNull() ? this->getPluginResource("META-INF/MANIFEST.MF")
                                                       : manifestResource;
    if (manifestRes.isEmpty())
    {
        throw QExtOsgiPluginException(QString("qextOsgiPlugin has no MANIFEST.MF resource, location=") + localPluginPath);
    }

    manifest.read(manifestRes);
}

//----------------------------------------------------------------------------
QString QExtOsgiPluginArchiveSQL::getAttribute(const QString &key) const
{
    return manifest.getAttribute(key);
}

//----------------------------------------------------------------------------
QHash<QString,QString> QExtOsgiPluginArchiveSQL::getUnlocalizedAttributes() const
{
    return manifest.getMainAttributes();
}

int QExtOsgiPluginArchiveSQL::getPluginGeneration() const
{
    return generation;
}

//----------------------------------------------------------------------------
int QExtOsgiPluginArchiveSQL::getPluginId() const
{
    return id;
}

//----------------------------------------------------------------------------
QUrl QExtOsgiPluginArchiveSQL::getPluginLocation() const
{
    return location;
}

//----------------------------------------------------------------------------
QString QExtOsgiPluginArchiveSQL::getLibLocation() const
{
    return localPluginPath;
}

//----------------------------------------------------------------------------
QByteArray QExtOsgiPluginArchiveSQL::getPluginResource(const QString &component) const
{
    try
    {
        return storage->getPluginResource(key, component);
    }
    catch (const QExtOsgiPluginDatabaseException& exc)
    {
        qDebug() << QString("Getting plugin resource %1 failed:").arg(component) << exc;
        return QByteArray();
    }
}

//----------------------------------------------------------------------------
QStringList QExtOsgiPluginArchiveSQL::findResourcesPath(const QString &path) const
{
    try
    {
        return storage->findResourcesPath(key, path);
    }
    catch (const QExtOsgiPluginDatabaseException& exc)
    {
        qDebug() << QString("Getting plugin resource paths for %1 failed:").arg(path) << exc;
    }
    return QStringList();
}

//----------------------------------------------------------------------------
int QExtOsgiPluginArchiveSQL::getStartLevel() const
{
    return startLevel;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginArchiveSQL::setStartLevel(int level)
{
    if (startLevel != level)
    {
        startLevel = level;
        storage->setStartLevel(key, level);
    }
}

//----------------------------------------------------------------------------
QDateTime QExtOsgiPluginArchiveSQL::getLastModified() const
{
    return lastModified;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginArchiveSQL::setLastModified(const QDateTime& dateTime)
{
    lastModified = dateTime;
    storage->setLastModified(key, dateTime);
}

//----------------------------------------------------------------------------
int QExtOsgiPluginArchiveSQL::getAutostartSetting() const
{
    return autostartSetting;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginArchiveSQL::setAutostartSetting(int setting)
{
    if (autostartSetting != setting)
    {
        autostartSetting = setting;
        storage->setAutostartSetting(key, setting);
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginArchiveSQL::purge()
{
    storage->removeArchive(this);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginArchiveSQL::close()
{

}
