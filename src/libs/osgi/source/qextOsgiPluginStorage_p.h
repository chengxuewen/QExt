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

#ifndef _QEXTOSGIPLUGINSTORAGE_P_H
#define _QEXTOSGIPLUGINSTORAGE_P_H

#include <QUrl>
#include <QStringList>
#include <QSharedPointer>

// CTK class forward declarations
class QExtOsgiPluginArchive;

/**
 * \ingroup PluginFramework
 *
 * Interface for managing all plugin meta-data and resources
 */
class QExtOsgiPluginStorage
{

public:

    virtual ~QExtOsgiPluginStorage() {}

    /**
   * Insert a plugin (shared library) into the persistent storage
   *
   * @param location Location of the plugin.
   * @param localPath Path to the plugin on the local file system
   * @return Plugin archive object.
   */
    virtual QSharedPointer<QExtOsgiPluginArchive> insertPlugin(const QUrl &location, const QString &localPath) = 0;

    /**
   * Insert a new plugin (shared library) into the persistent
   * storagedata as an update
   * to an existing plugin archive. To commit this data a call to
   * <code>replacePluginArchive</code> is needed.
   *
   * @param old QExtOsgiPluginArchive to be replaced.
   * @param updateLocation Location of the updated plugin.
   * @param localPath Path to a plugin on the local file system.
   * @return Plugin archive object.
   */
    virtual QSharedPointer<QExtOsgiPluginArchive> updatePluginArchive(QSharedPointer<QExtOsgiPluginArchive> old,
                                                                 const QUrl &updateLocation, const QString &localPath) = 0;

    /**
   * Replace old plugin archive with a new updated plugin archive, that
   * was created with updatePluginArchive.
   *
   * @param oldPA QExtOsgiPluginArchive to be replaced.
   * @param newPA new QExtOsgiPluginArchive.
   */
    virtual void replacePluginArchive(QSharedPointer<QExtOsgiPluginArchive> oldPA, QSharedPointer<QExtOsgiPluginArchive> newPA) = 0;

    /**
   * Remove plugin archive from archives list and persistent storage.
   * The plugin archive is deleted and must not be used afterwards, if
   * this method returns \a true.
   *
   * @param pa Plugin archive to remove.
   * @return true if element was removed.
   */
    virtual bool removeArchive(QSharedPointer<QExtOsgiPluginArchive> pa) = 0;

    /**
   * Get all plugin archive objects.
   *
   * @return QList of all PluginArchives.
   */
    virtual QList<QSharedPointer<QExtOsgiPluginArchive> > getAllPluginArchives() const = 0;

    /**
   * Get all plugins to start at next launch of framework.
   * This list is sorted in increasing plugin id order.
   *
   * @return A List with plugin locations.
   */
    virtual QList<QString> getStartOnLaunchPlugins() const = 0;

    /**
   * Close this plugin storage and all bundles in it.
   */
    virtual void close() = 0;

};


#endif // _QEXTOSGIPLUGINSTORAGE_P_H
