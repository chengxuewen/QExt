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

#include <private/qextOsgiPluginStorageSQL_p.h>
#include <private/qextOsgiPluginArchiveSQL_p.h>
#include <private/qextOsgiPluginStorage_p.h>
#include <private/qextOsgiPluginFrameworkUtil_p.h>
#include <private/qextOsgiPluginFrameworkContext_p.h>
#include <qextOsgiPluginDatabaseException.h>
#include <qextOsgiPlugin.h>
#include <qextOsgiPluginConstants.h>
#include <qextOsgiPluginException.h>
#include <qextOsgiServiceException.h>
#include <qextUtils.h>

#include <QFileInfo>
#include <QUrl>
#include <QThread>

//database table names
#define PLUGINS_TABLE "Plugins"
#define PLUGIN_RESOURCES_TABLE "PluginResources"

//----------------------------------------------------------------------------
enum TBindIndexes
{
    EBindIndex=0,
    EBindIndex1,
    EBindIndex2,
    EBindIndex3,
    EBindIndex4,
    EBindIndex5,
    EBindIndex6,
    EBindIndex7
};

//----------------------------------------------------------------------------
QExtOsgiPluginStorageSQL::QExtOsgiPluginStorageSQL(QExtOsgiPluginFrameworkContext *framework)
    : m_framework(framework)
    , m_nextFreeId(-1)
{
    // See if we have a storage database
    setDatabasePath(QExtOsgiPluginFrameworkUtil::getFileStorage(framework, "").absoluteFilePath("plugins.db"));

    this->open();
    restorePluginArchives();
}

//----------------------------------------------------------------------------
QExtOsgiPluginStorageSQL::~QExtOsgiPluginStorageSQL()
{
    close();
}

//----------------------------------------------------------------------------
QSqlDatabase QExtOsgiPluginStorageSQL::getConnection(bool create) const
{
    if (m_connectionNames.hasLocalData() && QSqlDatabase::contains(m_connectionNames.localData()))
    {
        return QSqlDatabase::database(m_connectionNames.localData());
    }

    if (!create)
    {
        throw QExtOsgiPluginDatabaseException(QString("No database connection."),
                                              QExtOsgiPluginDatabaseException::DB_NOT_OPEN_ERROR);
    }

    m_connectionNames.setLocalData(getConnectionName());

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", m_connectionNames.localData());
    database.setDatabaseName(getDatabasePath());

    if (!database.isValid())
    {
        close();
        throw QExtOsgiPluginDatabaseException(QString("Invalid database connection: %1").arg(m_connectionNames.localData()),
                                              QExtOsgiPluginDatabaseException::DB_CONNECTION_INVALID);
    }

    if (!database.open())
    {
        close();
        throw QExtOsgiPluginDatabaseException(QString("Could not open database connection: %1 (%2)").arg(m_connectionNames.localData()).arg(database.lastError().text()),
                                              QExtOsgiPluginDatabaseException::DB_SQL_ERROR);
    }

    return database;
}

//----------------------------------------------------------------------------
QString QExtOsgiPluginStorageSQL::getConnectionName() const
{
    QString connectionName = QFileInfo(getDatabasePath()).completeBaseName();
    connectionName += QString("_0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThread()), 2 * QT_POINTER_SIZE, 16, QLatin1Char('0'));
    return connectionName;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::createDatabaseDirectory() const
{
    QString path = getDatabasePath();

    QFileInfo fileInfo(path);
    if (!fileInfo.dir().exists())
    {
        if (!QDir::root().mkpath(fileInfo.path()))
        {
            close();
            throw QExtOsgiPluginDatabaseException(QString("Could not create database directory: %1").arg(fileInfo.path()),
                                                  QExtOsgiPluginDatabaseException::DB_CREATE_DIR_ERROR);
        }
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::open()
{
    createDatabaseDirectory();

    QSqlDatabase database = getConnection();

    //Check if the sqlite version supports foreign key constraints
    QSqlQuery query(database);
    if (!query.exec("PRAGMA foreign_keys"))
    {
        close();
        throw QExtOsgiPluginDatabaseException(QString("Check for foreign key support failed."),
                                              QExtOsgiPluginDatabaseException::DB_SQL_ERROR);
    }

    if (!query.next())
    {
        close();
        throw QExtOsgiPluginDatabaseException(QString("SQLite db does not support foreign keys. It is either older than 3.6.19 or was compiled with SQLITE_OMIT_FOREIGN_KEY or SQLITE_OMIT_TRIGGER"),
                                              QExtOsgiPluginDatabaseException::DB_SQL_ERROR);
    }
    query.finish();
    query.clear();

    //Enable foreign key support
    if (!query.exec("PRAGMA foreign_keys = ON"))
    {
        close();
        throw QExtOsgiPluginDatabaseException(QString("Enabling foreign key support failed."),
                                              QExtOsgiPluginDatabaseException::DB_SQL_ERROR);
    }
    query.finish();


    //Check database structure (tables) and recreate tables if necessary
    //If one of the tables is missing remove all tables and recreate them
    //This operation is required in order to avoid data corruption
    if (!checkTables())
    {
        if (dropTables())
        {
            createTables();
        }
        else
        {
            //dropTables() should've handled error message
            //and warning
            close();
        }
    }

    // silently remove any plugin marked as uninstalled
    cleanupDB();

    //Update database based on the recorded timestamps
    updateDB();

    initNextFreeIds();
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::initNextFreeIds()
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString statement = "SELECT ID,MAX(Generation) FROM " PLUGINS_TABLE " GROUP BY ID";
    executeQuery(&query, statement);

    while (query.next())
    {
        m_generations.insert(query.value(EBindIndex).toInt(),
                             query.value(EBindIndex1).toInt()+1);
    }

    query.finish();
    query.clear();

    statement = "SELECT MAX(ID) FROM " PLUGINS_TABLE;
    executeQuery(&query, statement);
    QVariant id = query.next() ? query.value(EBindIndex) : QVariant();
    if (id.isValid())
    {
        m_nextFreeId = id.toInt() + 1;
    }
    else
    {
        m_nextFreeId = 1;
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::cleanupDB()
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    beginTransaction(&query, Write);

    try
    {
        // remove all plug-ins marked as UNINSTALLED
        QString statement = "DELETE FROM " PLUGINS_TABLE " WHERE StartLevel==-2";
        executeQuery(&query, statement);

        // remove all old plug-in generations
        statement = "DELETE FROM " PLUGINS_TABLE
                    " WHERE K NOT IN (SELECT K FROM (SELECT K, MAX(Generation) FROM " PLUGINS_TABLE " GROUP BY ID))";
    }
    catch (...)
    {
        rollbackTransaction(&query);
        throw;
    }

    commitTransaction(&query);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::updateDB()
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    beginTransaction(&query, Write);

    // 1. Get the state information of all plug-ins (it is assumed that
    //    plug-ins marked as UNINSTALLED (startlevel == -2) are already removed

    QString statement = "SELECT ID,MAX(Generation),Location,LocalPath,Timestamp,StartLevel,AutoStart,K "
                        "FROM " PLUGINS_TABLE " GROUP BY ID";

    QList<int> outdatedIds;
    QList<QSharedPointer<QExtOsgiPluginArchiveSQL> > updatedPluginArchives;
    try
    {
        executeQuery(&query, statement);

        // 2. Check the timestamp for each plug-in

        while (query.next())
        {
            QFileInfo pluginInfo(query.value(EBindIndex3).toString());
            QDateTime pluginLastModified = pluginInfo.lastModified();
            // Make sure the QDateTime has the same accuracy as the one in the database
            pluginLastModified = getQDateTimeFromString(getStringFromQDateTime(pluginLastModified));

            if (pluginLastModified > getQDateTimeFromString(query.value(EBindIndex4).toString()))
            {
                QSharedPointer<QExtOsgiPluginArchiveSQL> updatedPA(
                    new QExtOsgiPluginArchiveSQL(this,
                                                 query.value(EBindIndex2).toUrl(),    // plug-in location url
                                                 query.value(EBindIndex3).toString(), // plugin local path
                                                 query.value(EBindIndex).toInt(),     // plugin id
                                                 query.value(EBindIndex5).toInt(),    // start level
                                                 QDateTime(),                         // last modififed
                                                 query.value(EBindIndex6).toInt())    // auto start setting
                    );
                updatedPA->key = query.value(EBindIndex7).toInt();
                updatedPluginArchives << updatedPA;

                // remember the plug-in ids for deletion
                outdatedIds << query.value(EBindIndex).toInt();
            }
        }
    }
    catch (...)
    {
        rollbackTransaction(&query);
        throw;
    }

    query.finish();
    query.clear();

    if (!outdatedIds.isEmpty())
    {
        // 3. Remove all traces from outdated plug-in data. Due to cascaded delete,
        //    it is sufficient to remove the records from the main table

        statement = "DELETE FROM " PLUGINS_TABLE " WHERE ID IN (%1)";
        QString idStr;
        foreach(int id, outdatedIds)
        {
            idStr += QString::number(id) + ",";
        }
        idStr.chop(1);

        try
        {
            executeQuery(&query, statement.arg(idStr));
        }
        catch (...)
        {
            rollbackTransaction(&query);
            throw;
        }

        query.finish();
        query.clear();

        try
        {
            foreach (QSharedPointer<QExtOsgiPluginArchiveSQL> updatedPA, updatedPluginArchives)
            {
                insertArchive(updatedPA, &query);
            }
        }
        catch (...)
        {
            rollbackTransaction(&query);
            throw;
        }
    }

    commitTransaction(&query);
}

//----------------------------------------------------------------------------
QLibrary::LoadHints QExtOsgiPluginStorageSQL::getPluginLoadHints() const
{
    if (m_framework->props.contains(QExtOsgiPluginConstants::FRAMEWORK_PLUGIN_LOAD_HINTS))
    {
        QVariant loadHintsVariant = m_framework->props[QExtOsgiPluginConstants::FRAMEWORK_PLUGIN_LOAD_HINTS];
        if (loadHintsVariant.isValid())
        {
            return loadHintsVariant.value<QLibrary::LoadHints>();
        }
    }
    return QLibrary::LoadHints();
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPluginArchive> QExtOsgiPluginStorageSQL::insertPlugin(const QUrl &location, const QString &localPath)
{
    QMutexLocker lock(&m_archivesLock);

    QFileInfo fileInfo(localPath);
    if (!fileInfo.exists())
    {
        throw QExtInvalidArgumentException(localPath + " does not exist");
    }

    const QString libTimestamp = getStringFromQDateTime(fileInfo.lastModified());

    QSharedPointer<QExtOsgiPluginArchiveSQL> archive(new QExtOsgiPluginArchiveSQL(this, location, localPath,
                                                                                  m_nextFreeId++));
    try
    {
        insertArchive(archive);
        m_archives << archive;
        return archive;
    }
    catch(...)
    {
        m_nextFreeId--;
        throw;
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::insertArchive(QSharedPointer<QExtOsgiPluginArchiveSQL> pa)
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    beginTransaction(&query, Write);

    try
    {
        insertArchive(pa, &query);
    }
    catch (...)
    {
        rollbackTransaction(&query);
        throw;
    }

    commitTransaction(&query);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::insertArchive(QSharedPointer<QExtOsgiPluginArchiveSQL> pa, QSqlQuery* query)
{

    QFileInfo fileInfo(pa->getLibLocation());
    QString libTimestamp = getStringFromQDateTime(fileInfo.lastModified());

    QString resourcePrefix = fileInfo.baseName();
    if (resourcePrefix.startsWith("lib"))
    {
        resourcePrefix = resourcePrefix.mid(3);
    }
    resourcePrefix.replace("_", ".");
    resourcePrefix = QString(":/") + resourcePrefix + "/";

    // Load the plugin and cache the resources

    QPluginLoader pluginLoader;
    pluginLoader.setLoadHints(getPluginLoadHints());
    pluginLoader.setFileName(pa->getLibLocation());
    if (!pluginLoader.load())
    {
        QExtOsgiPluginException exc(QString("The plugin \"%1\" could not be loaded: %2").arg(pa->getLibLocation())
                                        .arg(pluginLoader.errorString()));
        throw exc;
    }

    QFile manifestResource(resourcePrefix + "META-INF/MANIFEST.MF");
    manifestResource.open(QIODevice::ReadOnly);
    QByteArray manifest = manifestResource.readAll();
    manifestResource.close();

    // Finally, complete the QExtOsgiPluginArchive information by reading the MANIFEST.MF resource
    pa->readManifest(manifest);

    // Assemble the data for the sql records

    QString version = pa->getAttribute(QExtOsgiPluginConstants::PLUGIN_VERSION);
    if (version.isEmpty()) version = "na";

    QString statement = "INSERT INTO " PLUGINS_TABLE " (ID,Generation,Location,LocalPath,SymbolicName,Version,LastModified,Timestamp,StartLevel,AutoStart) "
                        "VALUES (?,?,?,?,?,?,?,?,?,?)";

    QList<QVariant> bindValues;
    bindValues << pa->getPluginId();
    bindValues << pa->getPluginGeneration();
    bindValues << pa->getPluginLocation();
    bindValues << pa->getLibLocation();
    bindValues << pa->getAttribute(QExtOsgiPluginConstants::PLUGIN_SYMBOLICNAME);
    bindValues << version;
    bindValues << "na";
    bindValues << libTimestamp;
    bindValues << pa->getStartLevel();
    bindValues << pa->getAutostartSetting();

    executeQuery(query, statement, bindValues);

    pa->key = query->lastInsertId().toInt();

    // Write the plug-in resource data into the database
    QDirIterator dirIter(resourcePrefix, QDirIterator::Subdirectories);
    while (dirIter.hasNext())
    {
        QString resourcePath = dirIter.next();
        if (QFileInfo(resourcePath).isDir()) continue;

        QFile resourceFile(resourcePath);
        resourceFile.open(QIODevice::ReadOnly);
        QByteArray resourceData = resourceFile.readAll();
        resourceFile.close();

        statement = "INSERT INTO " PLUGIN_RESOURCES_TABLE " (K,ResourcePath,Resource) VALUES(?,?,?)";
        bindValues.clear();
        bindValues << pa->key;
        bindValues << resourcePath.mid(resourcePrefix.size()-1);
        bindValues << resourceData;

        executeQuery(query, statement, bindValues);
    }

    pluginLoader.unload();
}

//----------------------------------------------------------------------------
QSharedPointer<QExtOsgiPluginArchive> QExtOsgiPluginStorageSQL::updatePluginArchive(QSharedPointer<QExtOsgiPluginArchive> old,
                                                                                    const QUrl &updateLocation,
                                                                                    const QString &localPath)
{
    QSharedPointer<QExtOsgiPluginArchive> newPA(new QExtOsgiPluginArchiveSQL(
        qSharedPointerCast<QExtOsgiPluginArchiveSQL>(old),
        m_generations[old->getPluginId()]++,
        updateLocation, localPath)
                                                );
    return newPA;
}

void QExtOsgiPluginStorageSQL::replacePluginArchive(QSharedPointer<QExtOsgiPluginArchive> oldPA, QSharedPointer<QExtOsgiPluginArchive> newPA)
{
    QMutexLocker lock(&m_archivesLock);

    int pos;
    long id = oldPA->getPluginId();
    pos = find(id);
    if (pos >= m_archives.size() || m_archives[pos] != oldPA)
    {
        throw QExtRuntimeException(QString("replacePluginArchive: Old plugin archive not found, pos=").append(pos));
    }

    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    beginTransaction(&query, Write);

    try
    {
        removeArchiveFromDB(static_cast<QExtOsgiPluginArchiveSQL*>(oldPA.data()), &query);
        insertArchive(qSharedPointerCast<QExtOsgiPluginArchiveSQL>(newPA), &query);

        commitTransaction(&query);
        m_archives[pos] = newPA;
    }
    catch (const QExtRuntimeException& re)
    {
        rollbackTransaction(&query);
        qWarning() << "Removing plug-in archive failed:" << re;
        throw;
    }
    catch (...)
    {
        rollbackTransaction(&query);
        throw;
    }
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginStorageSQL::removeArchive(QExtOsgiPluginArchiveSQL* pa)
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    beginTransaction(&query, Write);

    try
    {
        removeArchiveFromDB(pa, &query);
        commitTransaction(&query);

        QMutexLocker lock(&m_archivesLock);
        int idx = find(pa);
        if (idx >= 0 && idx < m_archives.size())
        {
            m_archives.removeAt(idx);
        }
        return true;
    }
    catch (const QExtRuntimeException& re)
    {
        rollbackTransaction(&query);
        qWarning() << "Removing plug-in archive failed:" << re;
    }
    catch (...)
    {
        qWarning() << "Removing plug-in archive failed: Unexpected exception";
        rollbackTransaction(&query);
    }
    return false;
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginStorageSQL::removeArchive(QSharedPointer<QExtOsgiPluginArchive> pa)
{
    return removeArchive(static_cast<QExtOsgiPluginArchiveSQL*>(pa.data()));
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::removeArchiveFromDB(QExtOsgiPluginArchiveSQL* pa, QSqlQuery* query)
{
    QString statement = "DELETE FROM " PLUGINS_TABLE " WHERE K=?";

    QList<QVariant> bindValues;
    bindValues.append(pa->key);

    executeQuery(query, statement, bindValues);
}

QList<QSharedPointer<QExtOsgiPluginArchive> > QExtOsgiPluginStorageSQL::getAllPluginArchives() const
{
    return m_archives;
}

QList<QString> QExtOsgiPluginStorageSQL::getStartOnLaunchPlugins() const
{
    QList<QString> res;
    foreach(QSharedPointer<QExtOsgiPluginArchive> pa, m_archives)
    {
        if (pa->getAutostartSetting() != -1)
        {
            res.push_back(pa->getPluginLocation().toString());
        }
    }
    return res;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::setStartLevel(int key, int startLevel)
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString statement = "UPDATE " PLUGINS_TABLE " SET StartLevel=? WHERE K=?";
    QList<QVariant> bindValues;
    bindValues.append(startLevel);
    bindValues.append(key);

    executeQuery(&query, statement, bindValues);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::setLastModified(int key, const QDateTime& lastModified)
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString statement = "UPDATE " PLUGINS_TABLE " SET LastModified=? WHERE K=?";
    QList<QVariant> bindValues;
    bindValues.append(getStringFromQDateTime(lastModified));
    bindValues.append(key);

    executeQuery(&query, statement, bindValues);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::setAutostartSetting(int key, int autostart)
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString statement = "UPDATE " PLUGINS_TABLE " SET AutoStart=? WHERE K=?";
    QList<QVariant> bindValues;
    bindValues.append(autostart);
    bindValues.append(key);

    executeQuery(&query, statement, bindValues);
}

//----------------------------------------------------------------------------
QStringList QExtOsgiPluginStorageSQL::findResourcesPath(int archiveKey, const QString &path) const
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString statement = "SELECT SUBSTR(ResourcePath,?) FROM PluginResources WHERE K=? AND SUBSTR(ResourcePath,1,?)=?";

    QString resourcePath = path.startsWith('/') ? path : QString("/") + path;
    if (!resourcePath.endsWith('/'))
        resourcePath += "/";

    QList<QVariant> bindValues;
    bindValues.append(resourcePath.size()+1);
    bindValues.append(archiveKey);
    bindValues.append(resourcePath.size());
    bindValues.append(resourcePath);

    executeQuery(&query, statement, bindValues);

    QSet<QString> paths;
    while (query.next())
    {
        QString currPath = query.value(EBindIndex).toString();
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
        QStringList components = currPath.split('/', Qt::SkipEmptyParts);
#else
        QStringList components = currPath.split('/', QString::SkipEmptyParts);
#endif
        if (components.size() == 1)
        {
            paths << components.front();
        }
        else if (components.size() == 2)
        {
            paths << components.front() + "/";
        }
    }

    return qext::qSetToQStringList(paths);
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::executeQuery(QSqlQuery *query, const QString &statement, const QList<QVariant> &bindValues) const
{
    Q_ASSERT(query != 0);

    bool success = false;
    enum {Prepare =0 , Execute=1};

    for (int stage=Prepare; stage <= Execute; ++stage)
    {
        if ( stage == Prepare)
            success = query->prepare(statement);
        else // stage == Execute
            success = query->exec();

        if (!success)
        {
            QString errorText = "Problem: Could not %1 statement: %2\n"
                                "Reason: %3\n"
                                "Parameters: %4\n";
            QString parameters;
            if (bindValues.count() > 0)
            {
                for (int i = 0; i < bindValues.count(); ++i)
                {
                    parameters.append(QString("\n\t[") + QString::number(i) + "]: " + bindValues.at(i).toString());
                }
            }
            else
            {
                parameters = "None";
            }

            QExtOsgiPluginDatabaseException::Type errorType;
#if (QT_VERSION >= QT_VERSION_CHECK(5, 3, 0))
            QString result = query->lastError().nativeErrorCode();
#else
            QString result = QString::number(query->lastError().number());
#endif
            if (result == "26" || result == "11") //SQLILTE_NOTADB || SQLITE_CORRUPT
            {
                qWarning() << "qextOsgiPluginFramework:- Database file is corrupt or invalid:" << getDatabasePath();
                errorType = QExtOsgiPluginDatabaseException::DB_FILE_INVALID;
            }
            else if (result == "8") // SQLITE_READONLY
                errorType = QExtOsgiPluginDatabaseException::DB_WRITE_ERROR;
            else
                errorType = QExtOsgiPluginDatabaseException::DB_SQL_ERROR;

            query->finish();
            query->clear();

            throw QExtOsgiPluginDatabaseException(errorText.arg(stage == Prepare ? "prepare":"execute")
                                                      .arg(statement).arg(query->lastError().text()).arg(parameters), errorType);
        }

        if (stage == Prepare)
        {
            foreach(const QVariant &bindValue, bindValues)
                query->addBindValue(bindValue);
        }
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::close()
{
    const_cast<const QExtOsgiPluginStorageSQL*>(this)->close();
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::close() const
{
    if (isOpen())
    {
        QSqlDatabase database = getConnection(false);
        if (database.isValid())
        {
            if(database.isOpen())
            {
                database.close();
                return;
            }
        }
        else
        {
            throw QExtOsgiPluginDatabaseException(QString("Problem closing database: Invalid connection %1").arg(m_connectionNames.localData()));
        }
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::setDatabasePath(const QString &databasePath)
{
    m_databasePath = QDir::toNativeSeparators(databasePath);
}

//----------------------------------------------------------------------------
QString QExtOsgiPluginStorageSQL::getDatabasePath() const
{
    QString path = m_databasePath;
    if(path.isEmpty())
    {
        path = QDir::homePath() + "/qextpluginfw/plugins.db";
        qWarning() << "No database path set. Using default:" << path;
    }

    path = QDir::toNativeSeparators(path);
    qDebug() << "Using database:" << path;
    return path;
}

//----------------------------------------------------------------------------
QByteArray QExtOsgiPluginStorageSQL::getPluginResource(int key, const QString &res) const
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString statement = "SELECT Resource FROM PluginResources WHERE K=? AND ResourcePath=?";

    QString resourcePath = res.startsWith('/') ? res : QString("/") + res;
    QList<QVariant> bindValues;
    bindValues.append(key);
    bindValues.append(resourcePath);

    executeQuery(&query, statement, bindValues);

    if (query.next())
    {
        return query.value(EBindIndex).toByteArray();
    }

    return QByteArray();
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::createTables()
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    //Begin Transaction
    beginTransaction(&query, Write);

    QString statement("CREATE TABLE " PLUGINS_TABLE " ("
                      "K INTEGER PRIMARY KEY,"
                      "ID INTEGER NOT NULL,"
                      "Generation INTEGER NOT NULL,"
                      "Location TEXT NOT NULL,"
                      "LocalPath TEXT NOT NULL,"
                      "SymbolicName TEXT NOT NULL,"
                      "Version TEXT NOT NULL,"
                      "LastModified TEXT NOT NULL,"
                      "Timestamp TEXT NOT NULL,"
                      "StartLevel INTEGER NOT NULL,"
                      "AutoStart INTEGER NOT NULL)");
    try
    {
        executeQuery(&query, statement);
    }
    catch (...)
    {
        rollbackTransaction(&query);
        throw;
    }

    statement = "CREATE TABLE " PLUGIN_RESOURCES_TABLE " ("
                "K INTEGER NOT NULL,"
                "ResourcePath TEXT NOT NULL,"
                "Resource BLOB NOT NULL,"
                "FOREIGN KEY(K) REFERENCES " PLUGINS_TABLE "(K) ON DELETE CASCADE)";
    try
    {
        executeQuery(&query, statement);
    }
    catch (...)
    {
        rollbackTransaction(&query);
        throw;
    }

    try
    {
        commitTransaction(&query);
    }
    catch (...)
    {
        rollbackTransaction(&query);
        throw;
    }

}

//----------------------------------------------------------------------------
bool QExtOsgiPluginStorageSQL::checkTables() const
{
    QSqlDatabase database = getConnection();

    bool bTables(false);
    QStringList tables = database.tables();
    if (tables.contains(PLUGINS_TABLE) &&
        tables.contains(PLUGIN_RESOURCES_TABLE))
    {
        bTables = true;
    }
    return bTables;
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginStorageSQL::dropTables()
{
    //Execute transaction for deleting the database tables
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);
    QStringList expectedTables;
    expectedTables << PLUGINS_TABLE << PLUGIN_RESOURCES_TABLE;

    if (database.tables().count() > 0)
    {
        beginTransaction(&query, Write);
        QStringList actualTables = database.tables();

        foreach(const QString expectedTable, expectedTables)
        {
            if (actualTables.contains(expectedTable))
            {
                try
                {
                    executeQuery(&query, QString("DROP TABLE ") + expectedTable);
                }
                catch (...)
                {
                    rollbackTransaction(&query);
                    throw;
                }
            }
            try
            {
                commitTransaction(&query);
            }
            catch (...)
            {
                rollbackTransaction(&query);
                throw;
            }
        }
    }
    return true;
}

//----------------------------------------------------------------------------
bool QExtOsgiPluginStorageSQL::isOpen() const
{
    try
    {
        getConnection(false);
    }
    catch (const QExtOsgiPluginDatabaseException&)
    {
        return false;
    }

    return true;
}

int QExtOsgiPluginStorageSQL::find(long id) const
{
    int lb = 0;
    int ub = m_archives.size() - 1;
    int x = 0;
    while (lb < ub)
    {
        x = (lb + ub) / 2;
        long xid = m_archives[x]->getPluginId();
        if (id == xid)
        {
            return x;
        }
        else if (id < xid)
        {
            ub = x;
        }
        else
        {
            lb = x+1;
        }
    }
    if (lb < m_archives.size() && m_archives[lb]->getPluginId() < id)
    {
        return lb + 1;
    }
    return lb;
}

//----------------------------------------------------------------------------
int QExtOsgiPluginStorageSQL::find(QExtOsgiPluginArchive *pa) const
{
    for (int i = 0; i < m_archives.size(); ++i)
    {
        if (m_archives[i].data() == pa) return i;
    }
    return -1;
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::beginTransaction(QSqlQuery *query, TransactionType type)
{
    bool success;
    if (type == Read)
        success = query->exec(QLatin1String("BEGIN"));
    else
        success = query->exec(QLatin1String("BEGIN IMMEDIATE"));

    if (!success) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 3, 0))
        QString result = query->lastError().nativeErrorCode();
#else
        QString result = QString::number(query->lastError().number());
#endif
        if (result == "26" || result == "11") // SQLITE_NOTADB || SQLITE_CORRUPT
        {
            throw QExtOsgiPluginDatabaseException(QString("qextOsgiPluginFramework: Database file is corrupt or invalid: %1").arg(getDatabasePath()),
                                                  QExtOsgiPluginDatabaseException::DB_FILE_INVALID);
        }
        else if (result == "8") // SQLITE_READONLY
        {
            throw QExtOsgiPluginDatabaseException(QString("qextOsgiPluginFramework: Insufficient permissions to write to database: %1").arg(getDatabasePath()),
                                                  QExtOsgiPluginDatabaseException::DB_WRITE_ERROR);
        }
        else
            throw QExtOsgiPluginDatabaseException(QString("qextOsgiPluginFramework: ") + query->lastError().text(),
                                                  QExtOsgiPluginDatabaseException::DB_SQL_ERROR);
    }

}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::commitTransaction(QSqlQuery *query)
{
    Q_ASSERT(query != 0);
    query->finish();
    query->clear();
    if (!query->exec(QLatin1String("COMMIT")))
    {
        throw QExtOsgiPluginDatabaseException(QString("qextOsgiPluginFramework: ") + query->lastError().text(),
                                              QExtOsgiPluginDatabaseException::DB_SQL_ERROR);
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::rollbackTransaction(QSqlQuery *query)
{
    Q_ASSERT(query !=0);
    query->finish();
    query->clear();

    if (!query->exec(QLatin1String("ROLLBACK")))
    {
        throw QExtOsgiPluginDatabaseException(QString("qextOsgiPluginFramework: ") + query->lastError().text(),
                                              QExtOsgiPluginDatabaseException::DB_SQL_ERROR);
    }
}

//----------------------------------------------------------------------------
void QExtOsgiPluginStorageSQL::restorePluginArchives()
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);
    QString statement = "SELECT ID, Location, LocalPath, StartLevel, LastModified, AutoStart, K, MAX(Generation)"
                        " FROM " PLUGINS_TABLE " WHERE StartLevel != -2 GROUP BY ID"
                        " ORDER BY ID";

    executeQuery(&query, statement);

    while (query.next())
    {
        const long id = query.value(EBindIndex).toLongLong();
        const QUrl location(query.value(EBindIndex1).toString());
        const QString localPath(query.value(EBindIndex2).toString());

        if (id <= 0 || location.isEmpty() || localPath.isEmpty())
        {
            throw QExtOsgiPluginDatabaseException(QString("Database integrity corrupted, row %1 contains empty values.").arg(id),
                                                  QExtOsgiPluginDatabaseException::DB_FILE_INVALID);
        }

        const int startLevel = query.value(EBindIndex3).toInt();
        const QDateTime lastModified = getQDateTimeFromString(query.value(EBindIndex4).toString());
        const int autoStart = query.value(EBindIndex5).toInt();

        try
        {
            QSharedPointer<QExtOsgiPluginArchiveSQL> pa(new QExtOsgiPluginArchiveSQL(this, location, localPath, id,
                                                                                     startLevel, lastModified, autoStart));
            pa->key = query.value(EBindIndex6).toInt();
            pa->readManifest();
            m_archives.append(pa);
        }
        catch (const QExtOsgiPluginException& exc)
        {
            qWarning() << exc;
        }
    }
}

//----------------------------------------------------------------------------
QString QExtOsgiPluginStorageSQL::getStringFromQDateTime(const QDateTime& dateTime) const
{
    return dateTime.toString(Qt::ISODate);
}

//----------------------------------------------------------------------------
QDateTime QExtOsgiPluginStorageSQL::getQDateTimeFromString(const QString &dateTimeString) const
{
    return QDateTime::fromString(dateTimeString, Qt::ISODate);
}
