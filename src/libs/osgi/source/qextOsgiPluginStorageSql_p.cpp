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

#include "qtkpluginstoragesql_p.h"
#include "qtkplugindatabaseexception.h"
#include "qtkplugin.h"
#include "qtkpluginconstants.h"
#include "qtkpluginexception.h"
#include "qtkpluginarchivesql_p.h"
#include "qtkpluginstorage_p.h"
#include "qtkpluginframeworkutil_p.h"
#include "qtkpluginframeworkcontext_p.h"
#include "qtkserviceexception.h"

#include <QFileInfo>
#include <QUrl>
#include <QThread>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

//database table names
#define PLUGINS_TABLE "Plugins"
#define PLUGIN_RESOURCES_TABLE "PluginResources"

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

QTKPluginStorageSQL::QTKPluginStorageSQL(QTKPluginFrameworkContext *pPFWContext)
    : m_pPFWContext(pPFWContext)
    , m_lNextFreeId(-1)
{
    // See if we have a storage database
    this->setDatabasePath(QTKPluginFrameworkUtil::getFileStorage(pPFWContext, "").absoluteFilePath("plugins.db"));
    this->open();
    this->restorePluginArchives();
}

QTKPluginStorageSQL::~QTKPluginStorageSQL()
{
    m_pPFWContext = nullptr;
    this->close();
}

QSqlDatabase QTKPluginStorageSQL::getConnection(bool bCreate) const
{
    if (m_connectionNames.hasLocalData() && QSqlDatabase::contains(m_connectionNames.localData())) {
        return QSqlDatabase::database(m_connectionNames.localData());
    }

    if (!bCreate) {
        throw QTKPluginDatabaseException(QString("No database connection."),
                                         QTKPluginDatabaseException::Type_DBNotOpenError);
    }

    m_connectionNames.setLocalData(getConnectionName());

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", m_connectionNames.localData());
    database.setDatabaseName(getDatabasePath());

    if (!database.isValid()) {
        this->close();
        throw QTKPluginDatabaseException(QString("Invalid database connection: %1").arg(m_connectionNames.localData()),
                                         QTKPluginDatabaseException::Type_DBConnectionInvalid);
    }

    if (!database.open()) {
        this->close();
        throw QTKPluginDatabaseException(QString("Could not open database connection: %1 (%2)").arg(m_connectionNames.localData()).arg(database.lastError().text()),
                                         QTKPluginDatabaseException::Type_DBSqlError);
    }

    return database;
}

QString QTKPluginStorageSQL::getConnectionName() const
{
    QString strConnectionName = QFileInfo(getDatabasePath()).completeBaseName();
    strConnectionName += QString("_0x%1").arg(reinterpret_cast<quintptr>(QThread::currentThread()), 2 * QT_POINTER_SIZE, 16, QLatin1Char('0'));
    return strConnectionName;
}

void QTKPluginStorageSQL::createDatabaseDirectory() const
{
    QString strPath = this->getDatabasePath();

    QFileInfo fileInfo(strPath);
    if (!fileInfo.dir().exists()) {
        if (!QDir::root().mkpath(fileInfo.path())) {
            this->close();
            throw QTKPluginDatabaseException(QString("Could not create database directory: %1").arg(fileInfo.path()),
                                             QTKPluginDatabaseException::Type_DBCreateDirError);
        }
    }
}

void QTKPluginStorageSQL::open()
{
    this->createDatabaseDirectory();

    QSqlDatabase database = this->getConnection();

    //Check if the sqlite version supports foreign key constraints
    QSqlQuery query(database);
    if (!query.exec("PRAGMA foreign_keys")) {
        this->close();
        throw QTKPluginDatabaseException(QString("Check for foreign key support failed."),
                                         QTKPluginDatabaseException::Type_DBSqlError);
    }

    if (!query.next()) {
        this->close();
        throw QTKPluginDatabaseException(QString("SQLite db does not support foreign keys. It is either older than 3.6.19 or was compiled with SQLITE_OMIT_FOREIGN_KEY or SQLITE_OMIT_TRIGGER"),
                                         QTKPluginDatabaseException::Type_DBSqlError);
    }
    query.finish();
    query.clear();

    //Enable foreign key support
    if (!query.exec("PRAGMA foreign_keys = ON")) {
        this->close();
        throw QTKPluginDatabaseException(QString("Enabling foreign key support failed."),
                                         QTKPluginDatabaseException::Type_DBSqlError);
    }
    query.finish();


    //Check database structure (tables) and recreate tables if neccessary
    //If one of the tables is missing remove all tables and recreate them
    //This operation is required in order to avoid data coruption
    if (!this->checkTables()) {
        if (this->dropTables()) {
            this->createTables();
        } else {
            //dropTables() should've handled error message
            //and warning
            this->close();
        }
    }

    // silently remove any plugin marked as uninstalled
    this->cleanupDB();

    //Update database based on the recorded timestamps
    this->updateDB();

    this->initNextFreeIds();
}

void QTKPluginStorageSQL::initNextFreeIds()
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString strStatement = "SELECT ID,MAX(Generation) FROM " PLUGINS_TABLE " GROUP BY ID";
    this->executeQuery(&query, strStatement);

    while (query.next()) {
        m_mapGenerations.insert(query.value(EBindIndex).toInt(),
                                query.value(EBindIndex1).toInt()+1);
    }

    query.finish();
    query.clear();

    strStatement = "SELECT MAX(ID) FROM " PLUGINS_TABLE;
    this->executeQuery(&query, strStatement);
    QVariant id = query.next() ? query.value(EBindIndex) : QVariant();
    if (id.isValid()) {
        m_lNextFreeId = id.toInt() + 1;
    } else {
        m_lNextFreeId = 1;
    }
}

void QTKPluginStorageSQL::cleanupDB()
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    this->beginTransaction(&query, Write);

    try {
        // remove all plug-ins marked as UNINSTALLED
        QString sreStatement = "DELETE FROM " PLUGINS_TABLE " WHERE StartLevel==-2";
        this->executeQuery(&query, sreStatement);

        // remove all old plug-in generations
        sreStatement = "DELETE FROM " PLUGINS_TABLE
                " WHERE K NOT IN (SELECT K FROM (SELECT K, MAX(Generation) FROM " PLUGINS_TABLE " GROUP BY ID))";
    } catch (...) {
        this->rollbackTransaction(&query);
        throw;
    }

    this->commitTransaction(&query);
}

void QTKPluginStorageSQL::updateDB()
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    this->beginTransaction(&query, Write);

    // 1. Get the state information of all plug-ins (it is assumed that
    //    plug-ins marked as UNINSTALLED (startlevel == -2) are already removed

    QString strStatement = "SELECT ID,MAX(Generation),Location,LocalPath,Timestamp,StartLevel,AutoStart,K "
                           "FROM " PLUGINS_TABLE " GROUP BY ID";

    QList<int> listOutdatedIds;
    QList<QSharedPointer<QTKPluginArchiveSQL> > listUpdatedPluginArchives;
    try {
        this->executeQuery(&query, strStatement);

        // 2. Check the timestamp for each plug-in
        while (query.next()) {
            QFileInfo pluginInfo(query.value(EBindIndex3).toString());
            QDateTime pluginLastModified = pluginInfo.lastModified();
            // Make sure the QDateTime has the same accuracy as the one in the database
            pluginLastModified = getQDateTimeFromString(getStringFromQDateTime(pluginLastModified));

            if (pluginLastModified > getQDateTimeFromString(query.value(EBindIndex4).toString())) {
                QSharedPointer<QTKPluginArchiveSQL> pUpdatedPluginArchive(
                            new QTKPluginArchiveSQL(this,
                                                    query.value(EBindIndex2).toUrl(),    // plug-in location url
                                                    query.value(EBindIndex3).toString(), // plugin local path
                                                    query.value(EBindIndex).toInt(),     // plugin id
                                                    query.value(EBindIndex5).toInt(),    // start level
                                                    QDateTime(),                         // last modififed
                                                    query.value(EBindIndex6).toInt())    // auto start setting
                            );
                pUpdatedPluginArchive->m_iKey = query.value(EBindIndex7).toInt();
                listUpdatedPluginArchives << pUpdatedPluginArchive;

                // remember the plug-in ids for deletion
                listOutdatedIds << query.value(EBindIndex).toInt();
            }
        }
    } catch (...) {
        this->rollbackTransaction(&query);
        throw;
    }

    query.finish();
    query.clear();

    if (!listOutdatedIds.isEmpty()) {
        // 3. Remove all traces from outdated plug-in data. Due to cascaded delete,
        //    it is sufficient to remove the records from the main table

        strStatement = "DELETE FROM " PLUGINS_TABLE " WHERE ID IN (%1)";
        QString idStr;
        foreach(int id, listOutdatedIds) {
            idStr += QString::number(id) + ",";
        }
        idStr.chop(1);

        try {
            this->executeQuery(&query, strStatement.arg(idStr));
        } catch (...) {
            this->rollbackTransaction(&query);
            throw;
        }

        query.finish();
        query.clear();

        try {
            foreach (QSharedPointer<QTKPluginArchiveSQL> pUpdatedPluginArchive, listUpdatedPluginArchives) {
                this->insertArchive(pUpdatedPluginArchive, &query);
            }
        } catch (...) {
            this->rollbackTransaction(&query);
            throw;
        }
    }

    this->commitTransaction(&query);
}

QLibrary::LoadHints QTKPluginStorageSQL::getPluginLoadHints() const
{
    if (m_pPFWContext->m_properties.contains(QTKPluginConstants::FRAMEWORK_LOAD_HINTS)) {
        QVariant loadHintsVariant = m_pPFWContext->m_properties[QTKPluginConstants::FRAMEWORK_LOAD_HINTS];
        if (loadHintsVariant.isValid()) {
            return loadHintsVariant.value<QLibrary::LoadHints>();
        }
    }
    return QLibrary::LoadHints(0);
}

QSharedPointer<QTKPluginArchive> QTKPluginStorageSQL::insertPlugin(const QUrl &location, const QString &strLocalPath)
{
    QMutexLocker lock(&m_archivesLock);

    QFileInfo fileInfo(strLocalPath);
    if (!fileInfo.exists()) {
        throw QTKInvalidArgumentException(strLocalPath + " does not exist");
    }

    const QString strLibTimestamp = this->getStringFromQDateTime(fileInfo.lastModified());

    QSharedPointer<QTKPluginArchiveSQL> pPluginArchive(new QTKPluginArchiveSQL(this, location, strLocalPath,
                                                                               m_lNextFreeId++));
    try {
        this->insertArchive(pPluginArchive);
        m_listArchives << pPluginArchive;
        return pPluginArchive;
    } catch(...) {
        m_lNextFreeId--;
        throw;
    }
}

void QTKPluginStorageSQL::insertArchive(QSharedPointer<QTKPluginArchiveSQL> pPluginArchive)
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    this->beginTransaction(&query, Write);

    try {
        this->insertArchive(pPluginArchive, &query);
    } catch (...) {
        this->rollbackTransaction(&query);
        throw;
    }

    this->commitTransaction(&query);
}

void QTKPluginStorageSQL::insertArchive(QSharedPointer<QTKPluginArchiveSQL> pPluginArchive, QSqlQuery *pQuery)
{
    QFileInfo fileInfo(pPluginArchive->getLibLocation());
    QString strLibTimestamp = this->getStringFromQDateTime(fileInfo.lastModified());

    QString strResourcePrefix = fileInfo.baseName();
    if (strResourcePrefix.startsWith("lib")) {
        strResourcePrefix = strResourcePrefix.mid(3);
    }
    strResourcePrefix.replace("_", ".");
    strResourcePrefix = QString(":/") + strResourcePrefix + "/";

    // Load the plugin and cache the resources

    QPluginLoader pluginLoader;
    pluginLoader.setLoadHints(this->getPluginLoadHints());
    pluginLoader.setFileName(pPluginArchive->getLibLocation());
    if (!pluginLoader.load()) {
        QTKPluginException exception(QString("The plugin \"%1\" could not be loaded: %2").arg(pPluginArchive->getLibLocation())
                                     .arg(pluginLoader.errorString()));
        throw exception;
    }

    QFile manifestResource(strResourcePrefix + "META-INF/MANIFEST.MF");
    manifestResource.open(QIODevice::ReadOnly);
    QByteArray manifest = manifestResource.readAll();
    manifestResource.close();

    // Finally, complete the QTKPluginArchive information by reading the MANIFEST.MF resource
    pPluginArchive->readManifest(manifest);

    // Assemble the data for the sql records
    QString strVersion = pPluginArchive->getAttribute(QTKPluginConstants::PLUGIN_VERSION);
    if (strVersion.isEmpty()) {
        strVersion = "na";
    }

    QString strStatement = "INSERT INTO " PLUGINS_TABLE " (ID,Generation,Location,LocalPath,SymbolicName,Version,LastModified,Timestamp,StartLevel,AutoStart) "
                                                        "VALUES (?,?,?,?,?,?,?,?,?,?)";

    QList<QVariant> listBindValues;
    listBindValues << pPluginArchive->getPluginId();
    listBindValues << pPluginArchive->getPluginGeneration();
    listBindValues << pPluginArchive->getPluginLocation();
    listBindValues << pPluginArchive->getLibLocation();
    listBindValues << pPluginArchive->getAttribute(QTKPluginConstants::PLUGIN_SYMBOLIC_NAME);
    listBindValues << strVersion;
    listBindValues << "na";
    listBindValues << strLibTimestamp;
    listBindValues << pPluginArchive->getStartLevel();
    listBindValues << pPluginArchive->getAutostartSetting();

    this->executeQuery(pQuery, strStatement, listBindValues);

    pPluginArchive->m_iKey = pQuery->lastInsertId().toInt();

    // Write the plug-in resource data into the database
    QDirIterator dirIter(strResourcePrefix, QDirIterator::Subdirectories);
    while (dirIter.hasNext()) {
        QString strResourcePath = dirIter.next();
        if (QFileInfo(strResourcePath).isDir()) {
            continue;
        }

        QFile resourceFile(strResourcePath);
        resourceFile.open(QIODevice::ReadOnly);
        QByteArray resourceData = resourceFile.readAll();
        resourceFile.close();

        strStatement = "INSERT INTO " PLUGIN_RESOURCES_TABLE " (K,ResourcePath,Resource) VALUES(?,?,?)";
        listBindValues.clear();
        listBindValues << pPluginArchive->m_iKey;
        listBindValues << strResourcePath.mid(strResourcePrefix.size()-1);
        listBindValues << resourceData;

        this->executeQuery(pQuery, strStatement, listBindValues);
    }

    pluginLoader.unload();
}

QSharedPointer<QTKPluginArchive> QTKPluginStorageSQL::updatePluginArchive(QSharedPointer<QTKPluginArchive> pOldPluginArchive,
                                                                          const QUrl &updateLocation,
                                                                          const QString &strLocalPath)
{
    QSharedPointer<QTKPluginArchive> pNewPluginArchive(new QTKPluginArchiveSQL(qSharedPointerCast<QTKPluginArchiveSQL>(pOldPluginArchive),
                                                                               m_mapGenerations[pOldPluginArchive->getPluginId()]++,
                                                       updateLocation,
                                                       strLocalPath));
    return pNewPluginArchive;
}

void QTKPluginStorageSQL::replacePluginArchive(QSharedPointer<QTKPluginArchive> pOldPluginArchive, QSharedPointer<QTKPluginArchive> pNewPluginArchive)
{
    QMutexLocker lock(&m_archivesLock);

    int iPos;
    long lId = pOldPluginArchive->getPluginId();
    iPos = this->find(lId);
    if (iPos >= m_listArchives.size() || m_listArchives[iPos] != pOldPluginArchive) {
        throw QTKRuntimeException(QString("replacePluginArchive: Old plugin archive not found, pos=").append(iPos));
    }

    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    this->beginTransaction(&query, Write);

    try {
        this->removeArchiveFromDB(static_cast<QTKPluginArchiveSQL*>(pOldPluginArchive.data()), &query);
        this->insertArchive(qSharedPointerCast<QTKPluginArchiveSQL>(pNewPluginArchive), &query);

        this->commitTransaction(&query);
        m_listArchives[iPos] = pNewPluginArchive;
    } catch (const QTKRuntimeException& re) {
        this->rollbackTransaction(&query);
        qWarning() << "Removing plug-in archive failed:" << re;
        throw;
    } catch (...) {
        this->rollbackTransaction(&query);
        throw;
    }
}

bool QTKPluginStorageSQL::removeArchive(QTKPluginArchiveSQL *pPluginArchive)
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    this->beginTransaction(&query, Write);

    try {
        this->removeArchiveFromDB(pPluginArchive, &query);
        this->commitTransaction(&query);

        QMutexLocker lock(&m_archivesLock);
        int iIndex = find(pPluginArchive);
        if (iIndex >= 0 && iIndex < m_listArchives.size()) {
            m_listArchives.removeAt(iIndex);
        }
        return true;
    } catch (const QTKRuntimeException &exception) {
        this->rollbackTransaction(&query);
        qWarning() << "Removing plug-in archive failed:" << exception;
    } catch (...) {
        qWarning() << "Removing plug-in archive failed: Unexpected exception";
        this->rollbackTransaction(&query);
    }
    return false;
}

bool QTKPluginStorageSQL::removeArchive(QSharedPointer<QTKPluginArchive> pPluginArchive)
{
    return this->removeArchive(static_cast<QTKPluginArchiveSQL*>(pPluginArchive.data()));
}

void QTKPluginStorageSQL::removeArchiveFromDB(QTKPluginArchiveSQL *pPluginArchive, QSqlQuery *pQuery)
{
    QString strStatement = "DELETE FROM " PLUGINS_TABLE " WHERE K=?";

    QList<QVariant> listBindValues;
    listBindValues.append(pPluginArchive->m_iKey);

    this->executeQuery(pQuery, strStatement, listBindValues);
}

QList<QSharedPointer<QTKPluginArchive> > QTKPluginStorageSQL::getAllPluginArchives() const
{
    return m_listArchives;
}

QList<QString> QTKPluginStorageSQL::getStartOnLaunchPlugins() const
{
    QList<QString> listRes;
    foreach (QSharedPointer<QTKPluginArchive> pPluginArchive, m_listArchives) {
        if (pPluginArchive->getAutostartSetting() != -1) {
            listRes.push_back(pPluginArchive->getPluginLocation().toString());
        }
    }
    return listRes;
}

void QTKPluginStorageSQL::setStartLevel(int iKey, int iStartLevel)
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString strStatement = "UPDATE " PLUGINS_TABLE " SET StartLevel=? WHERE K=?";
    QList<QVariant> listBindValues;
    listBindValues.append(iStartLevel);
    listBindValues.append(iKey);

    this->executeQuery(&query, strStatement, listBindValues);
}

void QTKPluginStorageSQL::setLastModified(int iKey, const QDateTime &lastModified)
{
    QSqlDatabase database = this->getConnection();
    QSqlQuery query(database);

    QString strStatement = "UPDATE " PLUGINS_TABLE " SET LastModified=? WHERE K=?";
    QList<QVariant> listBindValues;
    listBindValues.append(getStringFromQDateTime(lastModified));
    listBindValues.append(iKey);

    this->executeQuery(&query, strStatement, listBindValues);
}

void QTKPluginStorageSQL::setAutostartSetting(int iKey, int iAutostart)
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString strStatement = "UPDATE " PLUGINS_TABLE " SET AutoStart=? WHERE K=?";
    QList<QVariant> listBindValues;
    listBindValues.append(iAutostart);
    listBindValues.append(iKey);

    this->executeQuery(&query, strStatement, listBindValues);
}

QStringList QTKPluginStorageSQL::findResourcesPath(int iArchiveKey, const QString& strPath) const
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString strStatement = "SELECT SUBSTR(ResourcePath,?) FROM PluginResources WHERE K=? AND SUBSTR(ResourcePath,1,?)=?";

    QString strResourcePath = strPath.startsWith('/') ? strPath : QString("/") + strPath;
    if (!strResourcePath.endsWith('/')) {
        strResourcePath += "/";
    }

    QList<QVariant> listBindValues;
    listBindValues.append(strResourcePath.size()+1);
    listBindValues.append(iArchiveKey);
    listBindValues.append(strResourcePath.size());
    listBindValues.append(strResourcePath);

    this->executeQuery(&query, strStatement, listBindValues);

    QSet<QString> paths;
    while (query.next()) {
        QString strCurrPath = query.value(EBindIndex).toString();
        QStringList listComponents = strCurrPath.split('/', QString::SkipEmptyParts);
        if (listComponents.size() == 1) {
            paths << listComponents.front();
        } else if (listComponents.size() == 2) {
            paths << listComponents.front() + "/";
        }
    }

    return paths.toList();
}

void QTKPluginStorageSQL::executeQuery(QSqlQuery *pQuery, const QString &strStatement,
                                       const QList<QVariant> &listBindValues) const
{
    Q_ASSERT(pQuery != 0);

    bool bSuccess = false;
    enum {Prepare =0 , Execute=1};

    for (int iStage = Prepare; iStage <= Execute; ++iStage) {
        if (iStage == Prepare) {
            bSuccess = pQuery->prepare(strStatement);
        } else {
            bSuccess = pQuery->exec(); // stage == Execute
        }

        if (!bSuccess) {
            QString strErrorText = "Problem: Could not %1 statement: %2\n"
                                   "Reason: %3\n"
                                   "Parameters: %4\n";
            QString strParameters;
            if (listBindValues.count() > 0) {
                for (int i = 0; i < listBindValues.count(); ++i) {
                    strParameters.append(QString("\n\t[") + QString::number(i) + "]: " + listBindValues.at(i).toString());
                }
            } else {
                strParameters = "None";
            }

            QTKPluginDatabaseException::Type eErrorType;
            int iResult = pQuery->lastError().number();
            if (iResult == 26 || iResult == 11) {  //SQLILTE_NOTADB || SQLITE_CORRUPT
                qWarning() << "QTKPluginFramework:- Database file is corrupt or invalid:" << getDatabasePath();
                eErrorType = QTKPluginDatabaseException::Type_DBFileInvalid;
            } else if (iResult == 8) {//SQLITE_READONLY
                eErrorType = QTKPluginDatabaseException::Type_DBWriteError;
            } else {
                eErrorType = QTKPluginDatabaseException::Type_DBSqlError;
            }

            pQuery->finish();
            pQuery->clear();

            throw QTKPluginDatabaseException(strErrorText.arg(iStage == Prepare ? "prepare":"execute")
                                             .arg(strStatement).arg(pQuery->lastError().text()).arg(strParameters), eErrorType);
        }

        if (iStage == Prepare) {
            foreach (const QVariant &bindValue, listBindValues) {
                pQuery->addBindValue(bindValue);
            }
        }
    }
}

void QTKPluginStorageSQL::close()
{
    const_cast<const QTKPluginStorageSQL*>(this)->close();
}

void QTKPluginStorageSQL::close() const
{
    if (isOpen()) {
        QSqlDatabase database = getConnection(false);
        if (database.isValid()) {
            if(database.isOpen()) {
                database.close();
                return;
            }
        } else {
            throw QTKPluginDatabaseException(QString("Problem closing database: Invalid connection %1").arg(m_connectionNames.localData()));
        }
    }
}

void QTKPluginStorageSQL::setDatabasePath(const QString &strDatabasePath)
{
    m_databasePath = QDir::toNativeSeparators(strDatabasePath);
}

QString QTKPluginStorageSQL::getDatabasePath() const
{
    QString strPath = m_databasePath;
    if(strPath.isEmpty()) {
        strPath = QDir::homePath() + "/QTKpluginfw/plugins.db";
        qWarning() << "No database path set. Using default:" << strPath;
    }

    strPath = QDir::toNativeSeparators(strPath);
//    qDebug() << "Using database:" << strPath;
    return strPath;
}

QByteArray QTKPluginStorageSQL::getPluginResource(int iKey, const QString &strRes) const
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);

    QString strStatement = "SELECT Resource FROM PluginResources WHERE K=? AND ResourcePath=?";

    QString strResourcePath = strRes.startsWith('/') ? strRes : QString("/") + strRes;
    QList<QVariant> listBindValues;
    listBindValues.append(iKey);
    listBindValues.append(strResourcePath);

    this->executeQuery(&query, strStatement, listBindValues);

    if (query.next()) {
        return query.value(EBindIndex).toByteArray();
    }

    return QByteArray();
}

void QTKPluginStorageSQL::createTables()
{
    QSqlDatabase database = this->getConnection();
    QSqlQuery query(database);

    //Begin Transaction
    this->beginTransaction(&query, Write);

    QString strStatement("CREATE TABLE " PLUGINS_TABLE " ("
                                                       "K INTEGER PRIMARY KEY,"
                                                       "ID INTEGER NOT nullptr,"
                                                       "Generation INTEGER NOT nullptr,"
                                                       "Location TEXT NOT nullptr,"
                                                       "LocalPath TEXT NOT nullptr,"
                                                       "SymbolicName TEXT NOT nullptr,"
                                                       "Version TEXT NOT nullptr,"
                                                       "LastModified TEXT NOT nullptr,"
                                                       "Timestamp TEXT NOT nullptr,"
                                                       "StartLevel INTEGER NOT nullptr,"
                                                       "AutoStart INTEGER NOT nullptr)");
    try {
        this->executeQuery(&query, strStatement);
    } catch (...) {
        this->rollbackTransaction(&query);
        throw;
    }

    strStatement = "CREATE TABLE " PLUGIN_RESOURCES_TABLE " ("
                                                          "K INTEGER NOT nullptr,"
                                                          "ResourcePath TEXT NOT nullptr,"
                                                          "Resource BLOB NOT nullptr,"
                                                          "FOREIGN KEY(K) REFERENCES " PLUGINS_TABLE "(K) ON DELETE CASCADE)";
    try {
        this->executeQuery(&query, strStatement);
    } catch (...) {
        this->rollbackTransaction(&query);
        throw;
    }

    try {
        this->commitTransaction(&query);
    } catch (...) {
        this->rollbackTransaction(&query);
        throw;
    }

}

bool QTKPluginStorageSQL::checkTables() const
{
    QSqlDatabase database = this->getConnection();

    bool bTables(false);
    QStringList listTables = database.tables();
    if (listTables.contains(PLUGINS_TABLE) && listTables.contains(PLUGIN_RESOURCES_TABLE)) {
        bTables = true;
    }
    return bTables;
}

bool QTKPluginStorageSQL::dropTables()
{
    //Execute transaction for deleting the database tables
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);
    QStringList listExpectedTables;
    listExpectedTables << PLUGINS_TABLE << PLUGIN_RESOURCES_TABLE;

    if (database.tables().count() > 0) {
        this->beginTransaction(&query, Write);
        QStringList listActualTables = database.tables();

        foreach(const QString expectedTable, listExpectedTables) {
            if (listActualTables.contains(expectedTable)) {
                try {
                    this->executeQuery(&query, QString("DROP TABLE ") + expectedTable);
                } catch (...) {
                    this->rollbackTransaction(&query);
                    throw;
                }
            }

            try {
                this->commitTransaction(&query);
            } catch (...) {
                this->rollbackTransaction(&query);
                throw;
            }
        }
    }
    return true;
}

bool QTKPluginStorageSQL::isOpen() const
{
    try {
        this->getConnection(false);
    } catch (const QTKPluginDatabaseException&) {
        return false;
    }

    return true;
}

int QTKPluginStorageSQL::find(long lId) const
{
    int iLb = 0;
    int iUb = m_listArchives.size() - 1;
    int iX = 0;
    while (iLb < iUb) {
        iX = (iLb + iUb) / 2;
        long lXid = m_listArchives[iX]->getPluginId();
        if (lId == lXid) {
            return iX;
        } else if (lId < lXid) {
            iUb = iX;
        } else {
            iLb = iX+1;
        }
    }
    if (iLb < m_listArchives.size() && m_listArchives[iLb]->getPluginId() < lId) {
        return iLb + 1;
    }
    return iLb;
}

int QTKPluginStorageSQL::find(QTKPluginArchive *pPluginArchive) const
{
    for (int i = 0; i < m_listArchives.size(); ++i) {
        if (m_listArchives[i].data() == pPluginArchive) {
            return i;
        }
    }
    return -1;
}

void QTKPluginStorageSQL::beginTransaction(QSqlQuery *pQuery, TransactionType eType)
{
    bool bSuccess;
    if (eType == Read) {
        bSuccess = pQuery->exec(QLatin1String("BEGIN"));
    } else {
        bSuccess = pQuery->exec(QLatin1String("BEGIN IMMEDIATE"));
    }

    if (!bSuccess) {
        int iResult = pQuery->lastError().number();
        if (iResult == 26 || iResult == 11) { //SQLITE_NOTADB || SQLITE_CORRUPT
            throw QTKPluginDatabaseException(QString("QTKPluginFramework: Database file is corrupt or invalid: %1").arg(getDatabasePath()),
                                             QTKPluginDatabaseException::Type_DBFileInvalid);
        } else if (iResult == 8) { //SQLITE_READONLY
            throw QTKPluginDatabaseException(QString("QTKPluginFramework: Insufficient permissions to write to database: %1").arg(getDatabasePath()),
                                             QTKPluginDatabaseException::Type_DBWriteError);
        } else {
            throw QTKPluginDatabaseException(QString("QTKPluginFramework: ") + pQuery->lastError().text(),
                                             QTKPluginDatabaseException::Type_DBSqlError);
        }
    }
}

void QTKPluginStorageSQL::commitTransaction(QSqlQuery *pQuery)
{
    Q_ASSERT(pQuery != 0);
    pQuery->finish();
    pQuery->clear();
    if (!pQuery->exec(QLatin1String("COMMIT"))) {
        throw QTKPluginDatabaseException(QString("QTKPluginFramework: ") + pQuery->lastError().text(),
                                         QTKPluginDatabaseException::Type_DBSqlError);
    }
}

void QTKPluginStorageSQL::rollbackTransaction(QSqlQuery *pQuery)
{
    Q_ASSERT(pQuery !=0);
    pQuery->finish();
    pQuery->clear();

    if (!pQuery->exec(QLatin1String("ROLLBACK"))) {
        throw QTKPluginDatabaseException(QString("QTKPluginFramework: ") + pQuery->lastError().text(),
                                         QTKPluginDatabaseException::Type_DBSqlError);
    }
}

void QTKPluginStorageSQL::restorePluginArchives()
{
    QSqlDatabase database = getConnection();
    QSqlQuery query(database);
    QString strStatement = "SELECT ID, Location, LocalPath, StartLevel, LastModified, AutoStart, K, MAX(Generation)"
                           " FROM " PLUGINS_TABLE " WHERE StartLevel != -2 GROUP BY ID"
                                                  " ORDER BY ID";

    this->executeQuery(&query, strStatement);

    while (query.next()) {
        const long lId = query.value(EBindIndex).toLongLong();
        const QUrl location(query.value(EBindIndex1).toString());
        const QString strLocalPath(query.value(EBindIndex2).toString());

        if (lId <= 0 || location.isEmpty() || strLocalPath.isEmpty()) {
            throw QTKPluginDatabaseException(QString("Database integrity corrupted, row %1 contains empty values.").arg(lId),
                                             QTKPluginDatabaseException::Type_DBFileInvalid);
        }

        const int iStartLevel = query.value(EBindIndex3).toInt();
        const QDateTime lastModified = getQDateTimeFromString(query.value(EBindIndex4).toString());
        const int iAutoStart = query.value(EBindIndex5).toInt();

        try {
            QSharedPointer<QTKPluginArchiveSQL> pPluginArchive(new QTKPluginArchiveSQL(this, location, strLocalPath, lId,
                                                                                       iStartLevel, lastModified, iAutoStart));
            pPluginArchive->m_iKey = query.value(EBindIndex6).toInt();
            pPluginArchive->readManifest();
            m_listArchives.append(pPluginArchive);
        } catch (const QTKPluginException &exception) {
            qWarning() << exception;
        }
    }
}

QString QTKPluginStorageSQL::getStringFromQDateTime(const QDateTime &dateTime) const
{
    return dateTime.toString(Qt::ISODate);
}

QDateTime QTKPluginStorageSQL::getQDateTimeFromString(const QString &strDateTime) const
{
    return QDateTime::fromString(strDateTime, Qt::ISODate);
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
