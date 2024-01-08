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


#include "qextOsgiConfigurationStore_p.h"
#include "qextOsgiConfigurationAdminFactory_p.h"

#include <qextOsgiPluginContext.h>
#include <qextOsgiLogService.h>

#include <QDataStream>
#include <QDateTime>

const QString QExtOsgiConfigurationStore::STORE_DIR = "store";
const QString QExtOsgiConfigurationStore::PID_EXT = ".pid";

QExtOsgiConfigurationStore::QExtOsgiConfigurationStore(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                                                       QExtOsgiPluginContext* context)
    : configurationAdminFactory(configurationAdminFactory)
    , createdPidCount(0)
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

        QExtOsgiDictionary dictionary;
        dataStream >> dictionary;
        if (dataStream.status() == QDataStream::Ok)
        {
            QExtOsgiConfigurationImplPtr config(new QExtOsgiConfigurationImpl(configurationAdminFactory, this, dictionary));
            configurations.insert(config->getPid(), config);
        }
        else
        {
            QString message = iodevice->errorString();
            QString errorMessage = QString("{Configuration Admin - pid = %1} could not be restored. %2").arg(pid).arg(message);
            QEXT_OSGI_ERROR(configurationAdminFactory->getLogService()) << errorMessage;
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

void QExtOsgiConfigurationStore::saveConfiguration(const QString& pid, QExtOsgiConfigurationImpl* config)
{
    if (!store.exists())
        return; // no persistent store

    config->checkLocked();
    QFile configFile(store.filePath(pid + PID_EXT));
    QExtOsgiDictionary configProperties = config->getAllProperties();
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
    //  catch (const PrivilegedActionException& e)
    //  {
    //    throw (IOException) e.getException();
    //  }
}

void QExtOsgiConfigurationStore::removeConfiguration(const QString& pid)
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

QExtOsgiConfigurationImplPtr QExtOsgiConfigurationStore::getConfiguration(
    const QString& pid, const QString& location)
{
    QMutexLocker lock(&mutex);
    QExtOsgiConfigurationImplPtr config = configurations.value(pid);
    if (config.isNull())
    {
        config = QExtOsgiConfigurationImplPtr(new QExtOsgiConfigurationImpl(configurationAdminFactory, this,
                                                                            QString(), pid, location));
        configurations.insert(pid, config);
    }
    return config;
}

QExtOsgiConfigurationImplPtr QExtOsgiConfigurationStore::createFactoryConfiguration(
    const QString& factoryPid, const QString& location)
{
    QMutexLocker lock(&mutex);
    //TODO Qt4.7 use QDateTime::currentMSecsSinceEpoch()
    QString pid = factoryPid + "-" + QDateTime::currentDateTime().toString("yyyyMMdd-hhmmsszzz") + "-" + QString::number(createdPidCount++);
    QExtOsgiConfigurationImplPtr config(new QExtOsgiConfigurationImpl(configurationAdminFactory, this, factoryPid, pid, location));
    configurations.insert(pid, config);
    return config;
}

QExtOsgiConfigurationImplPtr QExtOsgiConfigurationStore::findConfiguration(const QString& pid)
{
    QMutexLocker lock(&mutex);
    return configurations.value(pid);
}

QList<QExtOsgiConfigurationImplPtr> QExtOsgiConfigurationStore::getFactoryConfigurations(const QString& factoryPid)
{
    QMutexLocker lock(&mutex);
    QList<QExtOsgiConfigurationImplPtr> resultList;
    foreach (QExtOsgiConfigurationImplPtr config, configurations)
    {
        QString otherFactoryPid = config->getFactoryPid();
        if (otherFactoryPid == factoryPid)
        {
            resultList.push_back(config);
        }
    }
    return resultList;
}

QList<QExtOsgiConfigurationImplPtr> QExtOsgiConfigurationStore::listConfigurations(const QExtOsgiLDAPSearchFilter& filter)
{
    QMutexLocker lock(&mutex);
    QList<QExtOsgiConfigurationImplPtr> resultList;
    foreach (QExtOsgiConfigurationImplPtr config, configurations)
    {
        QExtOsgiDictionary properties = config->getAllProperties();
        if (filter.match(properties))
        {
            resultList.push_back(config);
        }
    }
    return resultList;
}

void QExtOsgiConfigurationStore::unbindConfigurations(QSharedPointer<QExtOsgiPlugin> plugin)
{
    QMutexLocker lock(&mutex);
    foreach (QExtOsgiConfigurationImplPtr config, configurations)
    {
        config->unbind(plugin);
    }
}

void QExtOsgiConfigurationStore::writeConfigurationFile(QFile& configFile,
                                                        const QExtOsgiDictionary& configProperties)
{
    QIODevice* iodevice = &configFile;
    iodevice->open(QIODevice::WriteOnly);
    QDataStream datastream(iodevice);

    datastream << configProperties;
    // ignore errors
    iodevice->close();
}

void QExtOsgiConfigurationStore::deleteConfigurationFile(QFile& configFile)
{
    configFile.remove();
}
