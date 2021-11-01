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

#ifndef QTKPLUGINSTORAGE_P_H
#define QTKPLUGINSTORAGE_P_H

#include "qtkpluginframework_global.h"

#include <QUrl>
#include <QObject>
#include <QStringList>
#include <QSharedPointer>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginArchive;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginStorage class
 * Interface for managing all plugin meta-data and resources
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginStorage : public QObject
{
    Q_OBJECT

public:
    virtual ~QTKPluginStorage() {}

    /**
     * @brief insertPlugin
     * Insert a plugin (shared library) into the persistent storage
     *
     * @param location Location of the plugin.
     * @param strLocalPath Path to the plugin on the local file system
     * @return Plugin archive object.
     */
    virtual QSharedPointer<QTKPluginArchive> insertPlugin(const QUrl &location, const QString &strLocalPath) = 0;

    /**
     * @brief updatePluginArchive
     * Insert a new plugin (shared library) into the persistent
     * storagedata as an update
     * to an existing plugin archive. To commit this data a call to
     * <code>replacePluginArchive</code> is needed.
     *
     * @param pOldPluginArchive QTKPluginArchive to be replaced.
     * @param updateLocation Location of the updated plugin.
     * @param strLocalPath Path to a plugin on the local file system.
     * @return Plugin archive object.
     */
    virtual QSharedPointer<QTKPluginArchive> updatePluginArchive(QSharedPointer<QTKPluginArchive> pOldPluginArchive,
                                                                 const QUrl &updateLocation, const QString &strLocalPath) = 0;

    /**
     * @brief replacePluginArchive
     * Replace old plugin archive with a new updated plugin archive, that
     * was created with updatePluginArchive.
     *
     * @param pOldPluginArchive QTKPluginArchive to be replaced.
     * @param pNewPluginArchive new QTKPluginArchive.
     */
    virtual void replacePluginArchive(QSharedPointer<QTKPluginArchive> pOldPluginArchive,
                                      QSharedPointer<QTKPluginArchive> pNewPluginArchive) = 0;

    /**
     * @brief removeArchive
     * Remove plugin archive from archives list and persistent storage.
     * The plugin archive is deleted and must not be used afterwards, if
     * this method returns \a true.
     *
     * @param pPluginArchive Plugin archive to remove.
     * @return true if element was removed.
     */
    virtual bool removeArchive(QSharedPointer<QTKPluginArchive> pPluginArchive) = 0;

    /**
     * @brief getAllPluginArchives
     * Get all plugin archive objects.
     *
     * @return QList of all PluginArchives.
     */
    virtual QList<QSharedPointer<QTKPluginArchive> > getAllPluginArchives() const = 0;

    /**
     * @brief getStartOnLaunchPlugins
     * @return
     * Get all plugins to start at next launch of framework.
     * This list is sorted in increasing plugin id order.
     *
     * @return A List with plugin locations.
     */
    virtual QList<QString> getStartOnLaunchPlugins() const = 0;

    /**
     * @brief close
     * Close this plugin storage and all bundles in it.
     */
    virtual void close() = 0;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINSTORAGE_P_H
