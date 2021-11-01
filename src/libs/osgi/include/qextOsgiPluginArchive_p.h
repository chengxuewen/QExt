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

#ifndef QTKPLUGINARCHIVE_P_H
#define QTKPLUGINARCHIVE_P_H

#include "qtkpluginframework_global.h"

#include <QDateTime>
#include <QString>
#include <QHash>
#include <QUrl>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginArchive class
 * Interface for managing plugin data.
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginArchive
{
public:
    QTKPluginArchive() {}
    virtual ~QTKPluginArchive() {}

    /**
     * @brief getAttribute
     * Get an attribute from the manifest of a plugin.
     *
     * Not localized
     *
     * @param key Name of attribute to get.
     * @return A string with result or null if the entry doesn't exists.
     */
    virtual QString getAttribute(const QString &strKey) const = 0;

    /**
     * @brief getUnlocalizedAttributes
     * @returns the (raw/unlocalized) attributes
     */
    virtual QHash<QString, QString> getUnlocalizedAttributes() const = 0;

    /**
     * @brief getPluginGeneration
     * Get the plugin generation associated with this plugin archive.
     *
     * @return A integer representing the generation.
     */
    virtual int getPluginGeneration() const = 0;

    /**
     * @brief getPluginId
     * Get plugin identifier for this plugin archive.
     *
     * @return QTKPlugin identifier.
     */
    virtual int getPluginId() const = 0;

    /**
     * @brief getPluginLocation
     * Get plugin location for this plugin archive.
     *
     * @return Bundle location.
     */
    virtual QUrl getPluginLocation() const = 0;

    /**
     * @brief getLibLocation
     * Get the path to the plugin library on the local
     * file system
     *
     * @return Path to the plugin library
     */
    virtual QString getLibLocation() const = 0;

    /**
     * @brief getPluginResource
     * Get a Qt resource as a byte array from a plugin. The resource
     * is cached and may be aquired even if the plugin is not active.
     *
     * @param strComponent Resource to get the byte array from.
     * @return QByteArray to the entry (empty if it doesn't exist).
     */
    virtual QByteArray getPluginResource(const QString &strComponent) const = 0;

    /**
     * @brief findResourcesPath
     * Returns a QStringList of all the paths
     * to entries within the plugin whose longest sub-path matches the supplied
     * path argument.
     *
     * @param strPath
     * @return
     */
    virtual QStringList findResourcesPath(const QString &strPath) const = 0;

    /**
     * @brief getStartLevel
     * Get stored plugin start level.
     *
     * @return
     */
    virtual int getStartLevel() const = 0;

    /**
     * @brief setStartLevel
     * Set stored plugin start level.
     *
     * @param iLevel
     */
    virtual void setStartLevel(int iLevel) = 0;

    /**
     * @brief getLastModified
     * Get last modified timestamp.
     *
     * @return
     */
    virtual QDateTime getLastModified() const = 0;

    /**
     * @brief setLastModified
     * Set stored last modified timestamp.
     *
     * @param timemillisecs
     */
    virtual void setLastModified(const QDateTime &timemillisecs) = 0;

    /**
     * @brief getAutostartSetting
     * Get auto-start setting.
     *
     * @return the autostart setting. "-1" if the plugin is not started.
     */
    virtual int getAutostartSetting() const = 0;

    /**
     * @brief setAutostartSetting
     * Set the auto-start setting.
     *
     * @param iSetting the autostart setting to use.
     */
    virtual void setAutostartSetting(int iSetting) = 0;

    /**
     * @brief purge
     * Remove plugin from persistent storage.
     */
    virtual void purge() = 0;

    /**
     * @brief close
     * Close archive and all its open files.
     */
    virtual void close() = 0;

    /**
     * @brief AUTO_START_SETTING_STOPPED
     * Autostart setting stopped.
     * @see QTKPluginArchive#setAutostartSetting(const QString&)
     */
    static const char *AUTO_START_SETTING_STOPPED; // = "stopped"

    /**
     * @brief AUTO_START_SETTING_EAGER
     * Autostart setting eager.
     * @see QTKPluginArchive#setAutostartSetting(const QString&)
     */
    static const char *AUTO_START_SETTING_EAGER; // = "eager"

    /**
     * @brief AUTO_START_SETTING_ACTIVATION_POLICY
     * Autostart setting declared activation policy.
     * @see QTKPluginArchive#setAutostartSetting(const QString&)
     */
    static const char *AUTO_START_SETTING_ACTIVATION_POLICY; // = "activation_policy"
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINARCHIVE_P_H
