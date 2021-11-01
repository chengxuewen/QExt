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

#ifndef QTKPLUGINARCHIVESQL_P_H
#define QTKPLUGINARCHIVESQL_P_H

#include "qtkpluginarchive_p.h"
#include "qtkpluginmanifest_p.h"

#include <QObject>
#include <QDateTime>
#include <QHash>
#include <QSharedPointer>
#include <QString>
#include <QUrl>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginStorageSQL;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginArchiveSQL class
 * Class for managing plugin data.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginArchiveSQL : public QTKPluginArchive
{
public:
    /**
     * @brief QTKPluginArchiveSQL
     * Construct new plugin archive.
     *
     * @param pPluginStorage
     * @param pluginLocation
     * @param strLocalPluginPath
     * @param iPluginId
     * @param iStartLevel
     * @param lastModified
     * @param iAutostartSetting
     */
    QTKPluginArchiveSQL(QTKPluginStorageSQL *pPluginStorage, const QUrl &pluginLocation,
                        const QString &strLocalPluginPath, int iPluginId,
                        int iStartLevel = -1, const QDateTime &lastModified = QDateTime(),
                        int iAutostartSetting = -1);

    /**
     * @brief QTKPluginArchiveSQL
     * Construct new bundle archive in an existing bundle archive.
     *
     * @param pOldObj
     * @param iGeneration
     * @param pluginLocation
     * @param strLocalPluginPath
     */
    QTKPluginArchiveSQL(QSharedPointer<QTKPluginArchiveSQL> pOldObj, int iGeneration,
                        const QUrl &pluginLocation, const QString &strLocalPluginPath);

    /**
     * @brief getAttribute
     * Get an attribute from the manifest of a plugin.
     *
     * Not localized
     *
     * @param strKey Name of attribute to get.
     * @return A string with result or null if the entry doesn't exists.
     */
    QString getAttribute(const QString &strKey) const;

    /**
     * @brief getUnlocalizedAttributes
     * @returns the (raw/unlocalized) attributes
     */
    QHash<QString,QString> getUnlocalizedAttributes() const;

    /**
     * @brief getPluginGeneration
     * Get the plugin generation associated with this plugin archive.
     *
     * @return A integer representing the generation.
     */
    int getPluginGeneration() const;

    /**
     * @brief getPluginId
     * Get plugin identifier for this plugin archive.
     *
     * @return QTKPlugin identifier.
     */
    int getPluginId() const;

    /**
     * @brief getPluginLocation
     * Get plugin location for this plugin archive.
     *
     * @return Bundle location.
     */
    QUrl getPluginLocation() const;

    /**
     * @brief getLibLocation
     * Get the path to the plugin library on the local
     * file system
     *
     * @return Path to the plugin library
     */
    QString getLibLocation() const;

    /**
     * @brief getPluginResource
     * Get a Qt resource as a byte array from a plugin. The resource
     * is cached and may be aquired even if the plugin is not active.
     *
     * @param strComponent Resource to get the byte array from.
     * @return QByteArray to the entry (empty if it doesn't exist).
     */
    QByteArray getPluginResource(const QString &strComponent) const;

    /**
     * @brief findResourcesPath
     * Returns a QStringList of all the paths
     * to entries within the plugin whose longest sub-path matches the supplied
     * path argument.
     *
     * @param strPath
     * @return
     */
    QStringList findResourcesPath(const QString &strPath) const;

    /**
     * @brief getStartLevel
     * Get stored plugin start level.
     *
     * @return
     */
    int getStartLevel() const;

    /**
     * @brief setStartLevel
     * Set stored plugin start level.
     *
     * @param iLevel
     */
    void setStartLevel(int iLevel);

    /**
     * @brief getLastModified
     * Get last modified timestamp.
     *
     * @return
     */
    QDateTime getLastModified() const;

    /**
     * @brief setLastModified
     * Set stored last modified timestamp.
     *
     * @param timemillisecs
     */
    void setLastModified(const QDateTime &timemillisecs);

    /**
     * @brief getAutostartSetting
     * Get auto-start setting.
     *
     * @return the autostart setting. "-1" if the plugin is not started.
     */
    int getAutostartSetting() const;

    /**
     * @brief setAutostartSetting
     * Set the auto-start setting.
     *
     * @param setting the autostart setting to use.
     */
    void setAutostartSetting(int iSetting);

    /**
     * @brief purge
     * Remove plugin from persistent storage.
     * This will delete the current QTKPluginArchiveSQL instance.
     */
    void purge();

    /**
     * @brief close
     * Close archive and all its open files.
     */
    void close();

    /**
     * @brief readManifest
     * Create a QTKPluginManifest using the Qt resource under META-INF/MANIFEST.MF
     *
     * @param manifestResource
     */
    void readManifest(const QByteArray &manifestResource = QByteArray());

    int m_iKey;

private:
    int m_iAutostartSetting;
    int m_iId;
    int m_iGeneration;
    int m_iStartLevel;
    QDateTime m_lastModified;
    QUrl m_location;
    QString m_strLocalPluginPath;
    QTKPluginManifest m_manifest;
    QTKPluginStorageSQL *m_pStorage;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINARCHIVESQL_P_H
