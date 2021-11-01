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

#include "qtkpluginarchivesql_p.h"
#include "qtkpluginexception.h"
#include "qtkpluginstoragesql_p.h"
#include "qtkplugindatabaseexception.h"

#include <QStringList>
#include <QFile>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

QTKPluginArchiveSQL::QTKPluginArchiveSQL(QTKPluginStorageSQL* pPluginStorage,
                                         const QUrl& pluginLocation, const QString& strLocalPluginPath,
                                         int iPluginId, int iStartLevel, const QDateTime& lastModified,
                                         int iAutostartSetting)
    : m_iKey(-1),
      m_iAutostartSetting(iAutostartSetting),
      m_iId(iPluginId),
      m_iGeneration(0),
      m_iStartLevel(iStartLevel),
      m_lastModified(lastModified),
      m_location(pluginLocation),
      m_strLocalPluginPath(strLocalPluginPath),
      m_pStorage(pPluginStorage)
{
}

QTKPluginArchiveSQL::QTKPluginArchiveSQL(QSharedPointer<QTKPluginArchiveSQL> pOldObj, int iGeneration,
                                         const QUrl &pluginLocation, const QString &strLocalPluginPath)
    : m_iKey(-1),
      m_iAutostartSetting(pOldObj->m_iAutostartSetting),
      m_iId(pOldObj->m_iId),
      m_iGeneration(iGeneration),
      m_iStartLevel(0),
      m_location(pluginLocation),
      m_strLocalPluginPath(strLocalPluginPath),
      m_pStorage(pOldObj->m_pStorage)
{
}

void QTKPluginArchiveSQL::readManifest(const QByteArray &manifestResource)
{
    QByteArray manifestRes = manifestResource.isNull() ? this->getPluginResource("META-INF/MANIFEST.MF")
                                                       : manifestResource;
    if (manifestRes.isEmpty()) {
        throw QTKPluginException(QString("QTKPlugin has no MANIFEST.MF resource, location=") + m_strLocalPluginPath);
    }

    m_manifest.read(manifestRes);
}

QString QTKPluginArchiveSQL::getAttribute(const QString &strKey) const
{
    return m_manifest.getAttribute(strKey);
}

QHash<QString,QString> QTKPluginArchiveSQL::getUnlocalizedAttributes() const
{
    return m_manifest.getMainAttributes();
}

int QTKPluginArchiveSQL::getPluginGeneration() const
{
    return m_iGeneration;
}

int QTKPluginArchiveSQL::getPluginId() const
{
    return m_iId;
}

QUrl QTKPluginArchiveSQL::getPluginLocation() const
{
    return m_location;
}

QString QTKPluginArchiveSQL::getLibLocation() const
{
    return m_strLocalPluginPath;
}

QByteArray QTKPluginArchiveSQL::getPluginResource(const QString& strComponent) const
{
    try {
        return m_pStorage->getPluginResource(m_iKey, strComponent);
    } catch (const QTKPluginDatabaseException &exc) {
        qWarning() << QString("Getting plugin resource %1 failed:").arg(strComponent) << exc;
        return QByteArray();
    }
}

QStringList QTKPluginArchiveSQL::findResourcesPath(const QString& strPath) const
{
    try {
        return m_pStorage->findResourcesPath(m_iKey, strPath);
    } catch (const QTKPluginDatabaseException &exc) {
        qWarning() << QString("Getting plugin resource paths for %1 failed:").arg(strPath) << exc;
    }
    return QStringList();
}

int QTKPluginArchiveSQL::getStartLevel() const
{
    return m_iStartLevel;
}

void QTKPluginArchiveSQL::setStartLevel(int iLevel)
{
    if (m_iStartLevel != iLevel) {
        m_iStartLevel = iLevel;
        m_pStorage->setStartLevel(m_iKey, iLevel);
    }
}

QDateTime QTKPluginArchiveSQL::getLastModified() const
{
    return m_lastModified;
}

void QTKPluginArchiveSQL::setLastModified(const QDateTime& dateTime)
{
    m_lastModified = dateTime;
    m_pStorage->setLastModified(m_iKey, dateTime);
}

int QTKPluginArchiveSQL::getAutostartSetting() const
{
    return m_iAutostartSetting;
}

void QTKPluginArchiveSQL::setAutostartSetting(int iSetting)
{
    if (m_iAutostartSetting != iSetting) {
        m_iAutostartSetting = iSetting;
        m_pStorage->setAutostartSetting(m_iKey, iSetting);
    }
}

void QTKPluginArchiveSQL::purge()
{
    m_pStorage->removeArchive(this);
}

void QTKPluginArchiveSQL::close()
{

}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
