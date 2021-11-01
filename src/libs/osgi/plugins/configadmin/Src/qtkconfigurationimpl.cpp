#include "qtkconfigurationimpl_p.h"
#include "qtkconfigurationadminfactory_p.h"
#include "qtkconfigurationstore_p.h"

#include <QTKPluginFramework/Service/Config/QTKConfigurationAdmin>
#include <QTKPluginFramework/QTKPluginConstants>

#include <QThread>

QTKConfigurationImpl::QTKConfigurationImpl(QTKConfigurationAdminFactory* configurationAdminFactory,
                                           QTKConfigurationStore* configurationStore,
                                           const QString& factoryPid, const QString& pid,
                                           const QString& pluginLocation)
    : configurationAdminFactory(configurationAdminFactory),
      configurationStore(configurationStore), pluginLocation(pluginLocation),
      factoryPid(factoryPid), pid(pid), deleted(false), lockedCount(0), lockHolder(0)
{

}

QTKConfigurationImpl::QTKConfigurationImpl(QTKConfigurationAdminFactory* configurationAdminFactory,
                                           QTKConfigurationStore* configurationStore,
                                           const QTKDictionary& dictionary)
    : configurationAdminFactory(configurationAdminFactory),
      configurationStore(configurationStore), deleted(false), lockedCount(0),
      lockHolder(0)
{
    pid = dictionary.value(QTKPluginConstants::SERVICE_PID).toString();
    factoryPid = dictionary.value(QTKConfigurationAdmin::SERVICE_FACTORYPID).toString();
    pluginLocation = dictionary.value(QTKConfigurationAdmin::SERVICE_PLUGINLOCATION).toString();
    updateDictionary(dictionary);
}

void QTKConfigurationImpl::remove()
{
    {
        QTKConfigurationImplLocker l(this);
        checkDeleted();
        deleted = true;
        configurationAdminFactory->notifyConfigurationDeleted(this, !factoryPid.isEmpty());
        configurationAdminFactory->dispatchEvent(QTKConfigurationEvent::CM_DELETED, factoryPid, pid);
    }
    configurationStore->removeConfiguration(pid);
}

QString QTKConfigurationImpl::getPluginLocation() const
{
    return getPluginLocation(true);
}

QString QTKConfigurationImpl::getFactoryPid() const
{
    return getFactoryPid(true);
}

QString QTKConfigurationImpl::getPid() const
{
    return getPid(true);
}

QTKDictionary QTKConfigurationImpl::getProperties() const
{
    QTKConfigurationImplLocker l(this);
    checkDeleted();
    if (dictionary.isEmpty())
        return dictionary;

    QTKDictionary copy = dictionary;
    copy.insert(QTKPluginConstants::SERVICE_PID, pid);
    if (!factoryPid.isEmpty())
    {
        copy.insert(QTKConfigurationAdmin::SERVICE_FACTORYPID, factoryPid);
    }

    return copy;
}

void QTKConfigurationImpl::setPluginLocation(const QString& pluginLocation)
{
    QTKConfigurationImplLocker l(this);
    checkDeleted();
    configurationAdminFactory->checkConfigurationPermission();
    this->pluginLocation = pluginLocation;
    boundPlugin.clear(); // always reset the boundPlugin when setPluginLocation is called
}

void QTKConfigurationImpl::update()
{
    QTKConfigurationImplLocker l(this);
    checkDeleted();
    configurationStore->saveConfiguration(pid, this);
    configurationAdminFactory->notifyConfigurationUpdated(this, !factoryPid.isEmpty());
}

void QTKConfigurationImpl::update(const QTKDictionary& properties)
{
    QTKConfigurationImplLocker l(this);
    checkDeleted();
    updateDictionary(properties);
    configurationStore->saveConfiguration(pid, this);
    configurationAdminFactory->notifyConfigurationUpdated(this, !factoryPid.isEmpty());
    configurationAdminFactory->dispatchEvent(QTKConfigurationEvent::CM_UPDATED, factoryPid, pid);
}

void QTKConfigurationImpl::lock() const
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

void QTKConfigurationImpl::unlock() const
{
    QMutexLocker lock(&mutex);
    QThread* current = QThread::currentThread();
    if (lockHolder != current)
    {
        throw QTKIllegalStateException("Thread not lock owner");
    }

    --lockedCount;
    if (lockedCount == 0)
    {
        lockHolder = 0;
        waitCond.wakeOne();
    }
}

void QTKConfigurationImpl::checkLocked() const
{
    QMutexLocker lock(&mutex);
    QThread* current = QThread::currentThread();
    if (lockHolder != current)
    {
        throw QTKIllegalStateException("Thread not lock owner");
    }
}

bool QTKConfigurationImpl::bind(QSharedPointer<QTKPlugin> plugin)
{
    QTKConfigurationImplLocker l(this);
    if (boundPlugin.isNull() && (pluginLocation.isEmpty() || pluginLocation == plugin->getLocation()))
    {
        boundPlugin = plugin;
    }
    return (boundPlugin == plugin);
}

void QTKConfigurationImpl::unbind(QSharedPointer<QTKPlugin> plugin)
{
    QTKConfigurationImplLocker l(this);
    if (boundPlugin == plugin)
    {
        boundPlugin.clear();
    }
}

QString QTKConfigurationImpl::getPluginLocation(bool checkPermission) const
{
    QTKConfigurationImplLocker l(this);
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

QString QTKConfigurationImpl::getFactoryPid(bool checkDel) const
{
    QTKConfigurationImplLocker l(this);
    if (checkDel)
    {
        checkDeleted();
    }
    return factoryPid;
}

QString QTKConfigurationImpl::getPid(bool checkDel) const
{
    QTKConfigurationImplLocker l(this);
    if (checkDel)
    {
        checkDeleted();
    }
    return pid;
}

QTKDictionary QTKConfigurationImpl::getAllProperties() const
{
    QTKConfigurationImplLocker l(this);
    if (deleted)
    {
        return QTKDictionary();
    }
    QTKDictionary copy = getProperties();
    if (copy.isEmpty())
    {
        return copy;
    }

    QString boundLocation = getPluginLocation(false);
    if (!boundLocation.isEmpty())
    {
        copy.insert(QTKConfigurationAdmin::SERVICE_PLUGINLOCATION, boundLocation);
    }
    return copy;
}

bool QTKConfigurationImpl::isDeleted() const
{
    QTKConfigurationImplLocker l(this);
    return deleted;
}

void QTKConfigurationImpl::checkDeleted() const
{
    if (deleted)
        throw QTKIllegalStateException("deleted");
}

void QTKConfigurationImpl::updateDictionary(const QTKDictionary& properties)
{
    QTKConfigurationDictionary newDictionary = properties;
    newDictionary.remove(QTKPluginConstants::SERVICE_PID);
    newDictionary.remove(QTKConfigurationAdmin::SERVICE_FACTORYPID);
    newDictionary.remove(QTKConfigurationAdmin::SERVICE_PLUGINLOCATION);
    dictionary = newDictionary;
}

QTKConfigurationImplLocker::QTKConfigurationImplLocker(const QTKConfigurationImpl* impl)
    : impl(impl)
{
    if (impl) impl->lock();
}

QTKConfigurationImplLocker::QTKConfigurationImplLocker(const QList<QTKConfigurationImplPtr>& implList)
    : impl(0), implList(implList)
{
    foreach(QTKConfigurationImplPtr i, this->implList)
    {
        if (i) i->lock();
    }
}

QTKConfigurationImplLocker::~QTKConfigurationImplLocker()
{
    if (impl) impl->unlock();
    foreach(QTKConfigurationImplPtr i, implList)
    {
        if (i) i->unlock();
    }
}
