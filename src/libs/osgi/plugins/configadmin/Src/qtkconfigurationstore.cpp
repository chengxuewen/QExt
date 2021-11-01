#include "qtkconfigurationstore_p.h"
#include "qtkconfigurationadminfactory_p.h"

#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/Service/Log/QTKLogService>

#include <QDataStream>
#include <QDateTime>

const QString QTKConfigurationStore::STORE_DIR = "store";
const QString QTKConfigurationStore::PID_EXT = ".pid";

QTKConfigurationStore::QTKConfigurationStore(
        QTKConfigurationAdminFactory* configurationAdminFactory,
        QTKPluginContext* context)
    : configurationAdminFactory(configurationAdminFactory),
      createdPidCount(0)
{
    store = context->getDataFile(STORE_DIR).absoluteDir();

    if (!store.mkpath(store.absolutePath()))
    {
        return; // no persistent store
    }

    QStringList nameFilters;
    nameFilters << QString('*') + PID_EXT;
    QFileInfoList configurationFiles = store.entryInfoList(nameFilters, QDir::Files | QDir::CaseSensitive);
    foreach (QFileInfo configFileInfo, configurationFiles)
    {
        QString configurationFilePath = configFileInfo.absoluteFilePath();
        QString configurationFileName = configFileInfo.fileName();
        QString pid = configurationFileName.mid(0, configurationFileName.size() - PID_EXT.size());

        bool deleteFile = false;
        QIODevice* iodevice = new QFile(configurationFilePath);
        iodevice->open(QIODevice::ReadOnly);
        QDataStream dataStream(iodevice);

        QTKDictionary dictionary;
        dataStream >> dictionary;
        if (dataStream.status() == QDataStream::Ok)
        {
            QTKConfigurationImplPtr config(new QTKConfigurationImpl(configurationAdminFactory, this, dictionary));
            configurations.insert(config->getPid(), config);
        }
        else
        {
            QString message = iodevice->errorString();
            QString errorMessage = QString("{Configuration Admin - pid = %1} could not be restored. %2").arg(pid).arg(message);
            QTK_ERROR(configurationAdminFactory->getLogService()) << errorMessage;
            deleteFile = true;
        }

        iodevice->close();
        delete iodevice;

        if (deleteFile)
        {
            QFile::remove(configurationFilePath);
        }
    }
}

void QTKConfigurationStore::saveConfiguration(const QString& pid, QTKConfigurationImpl* config)
{
    if (!store.exists())
        return; // no persistent store

    config->checkLocked();
    QFile configFile(store.filePath(pid + PID_EXT));
    QTKDictionary configProperties = config->getAllProperties();
    //TODO security
    //  try
    //  {
    //    AccessController.doPrivileged(new PrivilegedExceptionAction() {
    //      public Object run() throws Exception {
    writeConfigurationFile(configFile, configProperties);
    //        return null;
    //      }
    //    });
    //  }
    //  catch (PrivilegedActionException e)
    //  {
    //    throw (IOException) e.getException();
    //  }
}

void QTKConfigurationStore::removeConfiguration(const QString& pid)
{
    QMutexLocker lock(&mutex);
    configurations.remove(pid);
    if (!store.exists())
        return; // no persistent store

    QFile configFile(store.filePath(pid + PID_EXT));
    //TODO security//  AccessController.doPrivileged(new PrivilegedAction() {
    //    public Object run() {
    deleteConfigurationFile(configFile);
    //      return null;
    //    }
    //  });
}

QTKConfigurationImplPtr QTKConfigurationStore::getConfiguration(
        const QString& pid, const QString& location)
{
    QMutexLocker lock(&mutex);
    QTKConfigurationImplPtr config = configurations.value(pid);
    if (config.isNull())
    {
        config = QTKConfigurationImplPtr(new QTKConfigurationImpl(configurationAdminFactory, this,
                                                                  QString(), pid, location));
        configurations.insert(pid, config);
    }
    return config;
}

QTKConfigurationImplPtr QTKConfigurationStore::createFactoryConfiguration(
        const QString& factoryPid, const QString& location)
{
    QMutexLocker lock(&mutex);
    //TODO Qt4.7 use QDateTime::currentMSecsSinceEpoch()
    QString pid = factoryPid + "-" + QDateTime::currentDateTime().toString("yyyyMMdd-hhmmsszzz") + "-" + QString::number(createdPidCount++);
    QTKConfigurationImplPtr config(new QTKConfigurationImpl(configurationAdminFactory, this, factoryPid, pid, location));
    configurations.insert(pid, config);
    return config;
}

QTKConfigurationImplPtr QTKConfigurationStore::findConfiguration(const QString& pid)
{
    QMutexLocker lock(&mutex);
    return configurations.value(pid);
}

QList<QTKConfigurationImplPtr> QTKConfigurationStore::getFactoryConfigurations(const QString& factoryPid)
{
    QMutexLocker lock(&mutex);
    QList<QTKConfigurationImplPtr> resultList;
    foreach (QTKConfigurationImplPtr config, configurations)
    {
        QString otherFactoryPid = config->getFactoryPid();
        if (otherFactoryPid == factoryPid)
        {
            resultList.push_back(config);
        }
    }
    return resultList;
}

QList<QTKConfigurationImplPtr> QTKConfigurationStore::listConfigurations(const QTKLDAPSearchFilter& filter)
{
    QMutexLocker lock(&mutex);
    QList<QTKConfigurationImplPtr> resultList;
    foreach (QTKConfigurationImplPtr config, configurations)
    {
        QTKDictionary properties = config->getAllProperties();
        if (filter.match(properties))
        {
            resultList.push_back(config);
        }
    }
    return resultList;
}

void QTKConfigurationStore::unbindConfigurations(QSharedPointer<QTKPlugin> plugin)
{
    QMutexLocker lock(&mutex);
    foreach (QTKConfigurationImplPtr config, configurations)
    {
        config->unbind(plugin);
    }
}

void QTKConfigurationStore::writeConfigurationFile(QFile& configFile,
                                                   const QTKDictionary& configProperties)
{
    QIODevice* iodevice = &configFile;
    iodevice->open(QIODevice::WriteOnly);
    QDataStream datastream(iodevice);

    datastream << configProperties;
    // ignore errors
    iodevice->close();
}

void QTKConfigurationStore::deleteConfigurationFile(QFile& configFile)
{
    configFile.remove();
}
