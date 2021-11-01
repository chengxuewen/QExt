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

#ifndef QTKPLUGINSTORAGESQL_P_H
#define QTKPLUGINSTORAGESQL_P_H

#include "qtkpluginstorage_p.h"
#include "qtkpluginframework_global.h"

#include <QMutex>
#include <QHash>
#include <QLibrary>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QPluginLoader>
#include <QDirIterator>
#include <QThreadStorage>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

class QTKPluginFrameworkContext;
class QTKPluginArchiveSQL;

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKPluginStorageSQL class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKPluginStorageSQL : public QTKPluginStorage
{
public:
    /**
     * @brief QTKPluginStorageSQL
     * Create a container for all plugin data in this framework.
     * Try to restore all saved plugin archive state.
     */
    QTKPluginStorageSQL(QTKPluginFrameworkContext *pPFWContext);
    ~QTKPluginStorageSQL();

    /**
     * @brief insertPlugin
     * Inserts a new plugin into the database. This method assumes that
     * the an entry with the same \a location and \a localPath does not
     * yet exist in the database.
     *
     * @param location The URL to the plugin.
     * @param strLocalPath The path to the plugin library on the local file system.
     *
     * @throws QTKPluginDatabaseException
     */
    QSharedPointer<QTKPluginArchive> insertPlugin(const QUrl &location, const QString &strLocalPath);

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
    QSharedPointer<QTKPluginArchive> updatePluginArchive(QSharedPointer<QTKPluginArchive> pOldPluginArchive,
                                                         const QUrl &updateLocation, const QString &strLocalPath);

    /**
     * @brief replacePluginArchive
     * Replace old plugin archive with a new updated plugin archive, that
     * was created with updatePluginArchive.
     *
     * @param pOldPluginArchive QTKPluginArchive to be replaced.
     * @param pNewPluginArchive new QTKPluginArchive.
     */
    void replacePluginArchive(QSharedPointer<QTKPluginArchive> pOldPluginArchive,
                              QSharedPointer<QTKPluginArchive> pNewPluginArchive);

    /**
     * @brief removeArchive
     * Removes all persisted data related to the given QTKPluginArchive.
     *
     * @throws QTKPluginDatabaseException
     */
    bool removeArchive(QSharedPointer<QTKPluginArchive> pPluginArchive);

    /**
     * @brief getAllPluginArchives
     * Get all plugin archive objects.
     *
     * @return QList of all PluginArchives.
     */
    QList<QSharedPointer<QTKPluginArchive> > getAllPluginArchives() const;

    /**
     * @brief getStartOnLaunchPlugins
     * Get all plugins to start at next launch of framework.
     * This list is sorted in increasing plugin id order.
     *
     * @return A List with plugin locations.
     */
    QList<QString> getStartOnLaunchPlugins() const;

    /**
     * @brief close
     * Closes the plugin database. Throws a QTKPluginDatabaseException
     * of type DB_CONNECTION_INVALID if the database is invalid.
     *
     * @throws QTKPluginDatabaseException
     */
    void close(); // Satisfy abstract interface
    void close() const;

    /**
     * @brief setDatabasePath
     * Sets the path of the service database to \a databasePath
     *
     * @param strDatabasePath
     */
    void setDatabasePath(const QString &strDatabasePath);

    /**
     * @brief getDatabasePath
     * Returns the path of the plugin database

     * @return
     */
    QString getDatabasePath() const;

    /**
     * @brief getPluginResource
     * Get a Qt resource cached in the database. The resource path \a res
     * must be relative to the plugin specific resource prefix, but may
     * start with a '/'.
     *
     * @param iKey The id of the plugin from which to get the resource
     * @param strRes The path to the resource in the plugin
     * @return The byte array of the cached resource
     *
     * @throws QTKPluginDatabaseException
     */
    QByteArray getPluginResource(int iKey, const QString &strRes) const;

    /**
     * @brief findResourcesPath
     * Get a list of resource entries under the given path.
     *
     * @param iArchiveKey The id of the plugin from which to get the entries
     * @param strPath A resource path relative to the plugin specific resource prefix.
     * @return A QStringList containing the cached resource entries.
     *
     * @throws QTKPluginDatabaseException
     */
    QStringList findResourcesPath(int iArchiveKey, const QString &strPath) const;

    /**
     * @brief setStartLevel
     * Persist the start level
     *
     * @param iKey The Plugin id
     * @param iStartLevel The new start level
     */
    void setStartLevel(int iKey, int iStartLevel);

    /**
     * @brief setLastModified
     * Persist the last modification (state change) time
     *
     * @param iKey The Plugin id
     * @param lastModified The modification time
     */
    void setLastModified(int iKey, const QDateTime &lastModified);

    /**
     * @brief setAutostartSetting
     * Persist the auto start setting.
     *
     * @param iKey The Plugin id
     * @param iAutostart The new auto start setting
     */
    void setAutostartSetting(int iKey, int iAutostart);

    /**
     * @brief removeArchive
     * Removes all persisted data related to the given QTKPluginArchiveSQL.
     * This is identical to removeArchive(QSharedPointer<QTKPluginArchive>).
     *
     * @throws QTKPluginDatabaseException
     */
    bool removeArchive(QTKPluginArchiveSQL *pPluginArchive);

private:
    enum TransactionType{
        Read,
        Write
    };

    /**
     * @brief open
     * Opens the plugin database. If the database does not
     * yet exist, it is created using the path from getDatabasePath().
     *
     * @see setDatabasePath(const QString&)
     * @see getDatabasePath()
     * @see QTKPluginDatabaseException
     *
     * @throws QTKPluginDatabaseException
     */
    void open();

    /**
     * @brief isOpen
     * Checks if the database is open
     *
     * @return
     */
    bool isOpen() const;

    /**
     * @brief find
     * Find position for QTKPluginArchive with specified id
     *
     * @param lId Plugin archive id to find.
     * @return Position in the m_archives List.
     */
    int find(long lId) const;

    /**
     * @brief find
     * Find position for QTKPluginArchive
     *
     * @param pPluginArchive Plugin archive id to find.
     * @return Position in the m_archives List.
     */
    int find(QTKPluginArchive *pPluginArchive) const;
    void initNextFreeIds();

    /**
     * @brief restorePluginArchives
     * Reads the persisted plugin data and creates a QTKPluginArchive object
     * for each plugin which is not in state UNINSTALLED.
     *
     * @throws QTKPluginDatabaseException
     */
    void restorePluginArchives();

    /**
     * @brief getPluginLoadHints
     * Get load hints from the framework for plugins.
     * @return
     */
    QLibrary::LoadHints getPluginLoadHints() const;

    /**
     * @brief createTables
     * Helper method that creates the database tables:
     *
     * @throws QTKPluginDatabaseException
     */
    void createTables();
    bool dropTables();

    /**
     * @brief cleanupDB
     * Remove all plugins which have been marked as uninstalled
     * (startLevel == -2).
     */
    void cleanupDB();

    /**
     * @brief checkTables
     * Helper method that checks if all the expected tables exist in the database.
     *
     * @return true if they all exist and false if any of them don't
     */
    bool checkTables() const;

    /**
     * @brief getConnection
     * Creates or returns an existing, thread-local database connection.
     *
     * @param bCreate Create and open connection.
     * @return Database connection.
     * @throws QTKPluginDatabaseException
     */
    QSqlDatabase getConnection(bool bCreate = true) const;

    /**
     * @brief getConnectionName
     * Creates a thread-unique database connection name.
     *
     * @return Database connection name.
     */
    QString getConnectionName() const;

    /**
     * @brief createDatabaseDirectory
     * Creates the directory for the database.
     *
     * @throws QTKPluginDatabaseException
     */
    void createDatabaseDirectory() const;

    /**
     * @brief updateDB
     * Compares the persisted plugin modification time with the
     * file system modification time and updates the database
     * if the persisted data is outdated.
     *
     * This should only be called once when the database is initially opened.
     */
    void updateDB();
    void insertArchive(QSharedPointer<QTKPluginArchiveSQL> pPluginArchive);
    void insertArchive(QSharedPointer<QTKPluginArchiveSQL> pPluginArchive, QSqlQuery *pQuery);
    void removeArchiveFromDB(QTKPluginArchiveSQL *pPluginArchive, QSqlQuery *pQuery);

    /**
     * @brief executeQuery
     * Helper function that executes the sql query specified in \a statement.
     * It is assumed that the \a statement uses positional placeholders and
     * corresponding parameters are placed in the list of \a bindValues.
     *
     * Aside: This function may be safely called standalone or within an explicit
     * transaction.  If called standalone, it's single query is implicitly
     * wrapped in it's own transaction.
     *
     * @throws QTKPluginDatabaseException
     */
    void executeQuery(QSqlQuery *pQuery, const QString &strStatement, const QList<QVariant> &listBindValues = QList<QVariant>()) const;

    /**
     * @brief beginTransaction
     * Begins a transcaction based on the \a type which can be Read or Write.
     *
     * @throws QTKPluginDatabaseException
     */
    void beginTransaction(QSqlQuery *pQuery, TransactionType eType);

    /**
     * @brief commitTransaction
     * Commits a transaction
     *
     * @throws QTKPluginDatabaseException
     */
    void commitTransaction(QSqlQuery *pQuery);

    /**
     * @brief rollbackTransaction
     * Rolls back a transaction
     *
     * @throws QTKPluginDatabaseException
     */
    void rollbackTransaction(QSqlQuery *pQuery);

    /**
     * @brief getStringFromQDateTime
     * Returns a string representation of a QDateTime instance.
     *
     * @param dateTime
     * @return
     */
    QString getStringFromQDateTime(const QDateTime &dateTime) const;

    /**
     * @brief getQDateTimeFromString
     * Returns a QDateTime from a string representation.
     *
     * @param strDateTime
     * @return
     */
    QDateTime getQDateTimeFromString(const QString &strDateTime) const;

    mutable QThreadStorage<QString> m_connectionNames;
    QString m_databasePath;
    QMutex m_archivesLock;

    /**
     * @brief m_listArchives
     * Plugin id sorted list of all active plugin archives.
     */
    QList<QSharedPointer<QTKPluginArchive> > m_listArchives;

    /**
     * @brief m_pPFWContext
     * Framework handle.
     */
    QTKPluginFrameworkContext* m_pPFWContext;

    /**
     * @brief m_lNextFreeId
     * Keep track of the next free plug-in id
     */
    long m_lNextFreeId;

    /**
     * @brief m_mapGenerations
     * Keep track of the next free generation for each plugin
     */
    QHash<int, int> m_mapGenerations; /* <plugin id, generation> */
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKPLUGINSTORAGESQL_P_H
