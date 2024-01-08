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


#include "qextOsgiConfigurationImpl_p.h"
#include "qextOsgiConfigurationAdminFactory_p.h"
#include "qextOsgiConfigurationStore_p.h"

#include <qextOsgiConfigurationAdmin.h>
#include <qextOsgiPluginConstants.h>

#include <QThread>

QExtOsgiConfigurationImpl::QExtOsgiConfigurationImpl(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                                                     QExtOsgiConfigurationStore* configurationStore,
                                                     const QString& factoryPid, const QString& pid,
                                                     const QString& pluginLocation)
    : configurationAdminFactory(configurationAdminFactory),
    configurationStore(configurationStore), pluginLocation(pluginLocation),
    factoryPid(factoryPid), pid(pid), deleted(false), lockedCount(0), lockHolder(0)
{

}

QExtOsgiConfigurationImpl::QExtOsgiConfigurationImpl(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                                                     QExtOsgiConfigurationStore* configurationStore,
                                                     const QExtOsgiDictionary& dictionary)
    : configurationAdminFactory(configurationAdminFactory),
    configurationStore(configurationStore), deleted(false), lockedCount(0),
    lockHolder(0)
{
    pid = dictionary.value(QExtOsgiPluginConstants::SERVICE_PID).toString();
    factoryPid = dictionary.value(QExtOsgiConfigurationAdmin::SERVICE_FACTORYPID).toString();
    pluginLocation = dictionary.value(QExtOsgiConfigurationAdmin::SERVICE_PLUGINLOCATION).toString();
    updateDictionary(dictionary);
}

void QExtOsgiConfigurationImpl::remove()
{
    {
        QExtOsgiConfigurationImplLocker l(this);
        checkDeleted();
        deleted = true;
        configurationAdminFactory->notifyConfigurationDeleted(this, !factoryPid.isEmpty());
        configurationAdminFactory->dispatchEvent(QExtOsgiConfigurationEvent::CM_DELETED, factoryPid, pid);
    }
    configurationStore->removeConfiguration(pid);
}

QString QExtOsgiConfigurationImpl::getPluginLocation() const
{
    return getPluginLocation(true);
}

QString QExtOsgiConfigurationImpl::getFactoryPid() const
{
    return getFactoryPid(true);
}

QString QExtOsgiConfigurationImpl::getPid() const
{
    return getPid(true);
}

QExtOsgiDictionary QExtOsgiConfigurationImpl::getProperties() const
{
    QExtOsgiConfigurationImplLocker l(this);
    checkDeleted();
    if (dictionary.isEmpty())
        return dictionary;

    QExtOsgiDictionary copy = dictionary;
    copy.insert(QExtOsgiPluginConstants::SERVICE_PID, pid);
    if (!factoryPid.isEmpty())
    {
        copy.insert(QExtOsgiConfigurationAdmin::SERVICE_FACTORYPID, factoryPid);
    }

    return copy;
}

void QExtOsgiConfigurationImpl::setPluginLocation(const QString& pluginLocation)
{
    QExtOsgiConfigurationImplLocker l(this);
    checkDeleted();
    configurationAdminFactory->checkConfigurationPermission();
    this->pluginLocation = pluginLocation;
    boundPlugin.clear(); // always reset the boundPlugin when setPluginLocation is called
}

void QExtOsgiConfigurationImpl::update()
{
    QExtOsgiConfigurationImplLocker l(this);
    checkDeleted();
    configurationStore->saveConfiguration(pid, this);
    configurationAdminFactory->notifyConfigurationUpdated(this, !factoryPid.isEmpty());
}

void QExtOsgiConfigurationImpl::update(const QExtOsgiDictionary& properties)
{
    QExtOsgiConfigurationImplLocker l(this);
    checkDeleted();
    updateDictionary(properties);
    configurationStore->saveConfiguration(pid, this);
    configurationAdminFactory->notifyConfigurationUpdated(this, !factoryPid.isEmpty());
    configurationAdminFactory->dispatchEvent(QExtOsgiConfigurationEvent::CM_UPDATED, factoryPid, pid);
}

void QExtOsgiConfigurationImpl::lock() const
{
    QMutexLocker lock(&mutex);
    QThread* current = QThread::currentThread();
    if (lockHolder != current)
    {
        while (lockedCount != 0)
        {
            waitCond.wait(&mutex);
        }
    }
    ++lockedCount;
    lockHolder = current;
}

void QExtOsgiConfigurationImpl::unlock() const
{
    QMutexLocker lock(&mutex);
    QThread* current = QThread::currentThread();
    if (lockHolder != current)
    {
        throw QExtIllegalStateException("Thread not lock owner");
    }

    --lockedCount;
    if (lockedCount == 0)
    {
        lockHolder = 0;
        waitCond.wakeOne();
    }
}

void QExtOsgiConfigurationImpl::checkLocked() const
{
    QMutexLocker lock(&mutex);
    QThread* current = QThread::currentThread();
    if (lockHolder != current)
    {
        throw QExtIllegalStateException("Thread not lock owner");
    }
}

bool QExtOsgiConfigurationImpl::bind(QSharedPointer<QExtOsgiPlugin> plugin)
{
    QExtOsgiConfigurationImplLocker l(this);
    if (boundPlugin.isNull() && (pluginLocation.isEmpty() || pluginLocation == plugin->getLocation()))
    {
        boundPlugin = plugin;
    }
    return (boundPlugin == plugin);
}

void QExtOsgiConfigurationImpl::unbind(QSharedPointer<QExtOsgiPlugin> plugin)
{
    QExtOsgiConfigurationImplLocker l(this);
    if (boundPlugin == plugin)
    {
        boundPlugin.clear();
    }
}

QString QExtOsgiConfigurationImpl::getPluginLocation(bool checkPermission) const
{
    QExtOsgiConfigurationImplLocker l(this);
    checkDeleted();
    if (checkPermission)
    {
        configurationAdminFactory->checkConfigurationPermission();
    }

    if (!pluginLocation.isEmpty())
    {
        return pluginLocation;
    }

    if (boundPlugin)
    {
        return boundPlugin->getLocation();
    }

    return QString();
}

QString QExtOsgiConfigurationImpl::getFactoryPid(bool checkDel) const
{
    QExtOsgiConfigurationImplLocker l(this);
    if (checkDel)
    {
        checkDeleted();
    }
    return factoryPid;
}

QString QExtOsgiConfigurationImpl::getPid(bool checkDel) const
{
    QExtOsgiConfigurationImplLocker l(this);
    if (checkDel)
    {
        checkDeleted();
    }
    return pid;
}

QExtOsgiDictionary QExtOsgiConfigurationImpl::getAllProperties() const
{
    QExtOsgiConfigurationImplLocker l(this);
    if (deleted)
    {
        return QExtOsgiDictionary();
    }
    QExtOsgiDictionary copy = getProperties();
    if (copy.isEmpty())
    {
        return copy;
    }

    QString boundLocation = getPluginLocation(false);
    if (!boundLocation.isEmpty())
    {
        copy.insert(QExtOsgiConfigurationAdmin::SERVICE_PLUGINLOCATION, boundLocation);
    }
    return copy;
}

bool QExtOsgiConfigurationImpl::isDeleted() const
{
    QExtOsgiConfigurationImplLocker l(this);
    return deleted;
}

void QExtOsgiConfigurationImpl::checkDeleted() const
{
    if (deleted)
        throw QExtIllegalStateException("deleted");
}

void QExtOsgiConfigurationImpl::updateDictionary(const QExtOsgiDictionary& properties)
{
    QExtOsgiConfigurationDictionary newDictionary = properties;
    newDictionary.remove(QExtOsgiPluginConstants::SERVICE_PID);
    newDictionary.remove(QExtOsgiConfigurationAdmin::SERVICE_FACTORYPID);
    newDictionary.remove(QExtOsgiConfigurationAdmin::SERVICE_PLUGINLOCATION);
    dictionary = newDictionary;
}

QExtOsgiConfigurationImplLocker::QExtOsgiConfigurationImplLocker(const QExtOsgiConfigurationImpl* impl)
    : impl(impl)
{
    if (impl) impl->lock();
}

QExtOsgiConfigurationImplLocker::QExtOsgiConfigurationImplLocker(const QList<QExtOsgiConfigurationImplPtr>& implList)
    : impl(0), implList(implList)
{
    foreach(QExtOsgiConfigurationImplPtr i, this->implList)
    {
        if (i) i->lock();
    }
}

QExtOsgiConfigurationImplLocker::~QExtOsgiConfigurationImplLocker()
{
    if (impl) impl->unlock();
    foreach(QExtOsgiConfigurationImplPtr i, implList)
    {
        if (i) i->unlock();
    }
}
