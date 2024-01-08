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


#ifndef _QEXTOSGICONFIGURATIONIMPL_P_H
#define _QEXTOSGICONFIGURATIONIMPL_P_H

#include <qextOsgiConfiguration.h>

#include <QMutex>
#include <QWaitCondition>

class QExtOsgiConfigurationAdminFactory;
class QExtOsgiConfigurationStore;
class QExtOsgiPlugin;

/**
 * QExtOsgiConfigurationImpl provides the QExtOsgiConfiguration implementation.
 * The lock and unlock methods are used for synchronization. Operations outside of
 * ConfigurationImpl that expect to have control of the lock should call checkLocked
 */
class QExtOsgiConfigurationImpl : public QExtOsgiConfiguration
{
public:
    QExtOsgiConfigurationImpl(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                              QExtOsgiConfigurationStore* configurationStore,
                              const QString& factoryPid, const QString& pid,
                              const QString& pluginLocation);

    QExtOsgiConfigurationImpl(QExtOsgiConfigurationAdminFactory* configurationAdminFactory,
                              QExtOsgiConfigurationStore* configurationStore,
                              const QExtOsgiDictionary& dictionary);

    void remove();

    QString getPluginLocation() const;
    QString getFactoryPid() const;
    QString getPid() const;
    QExtOsgiDictionary getProperties() const;

    void setPluginLocation(const QString& pluginLocation);

    void update();
    void update(const QExtOsgiDictionary& properties);

    void checkLocked() const;

    bool bind(QSharedPointer<QExtOsgiPlugin> plugin);
    void unbind(QSharedPointer<QExtOsgiPlugin> plugin);

    QString getPluginLocation(bool checkPermission) const;
    QString getFactoryPid(bool checkDeleted) const;
    QString getPid(bool checkDeleted) const;
    QExtOsgiDictionary getAllProperties() const;

    void lock() const;
    void unlock() const;

    bool isDeleted() const;

private:
    typedef QExtOsgiDictionary QExtOsgiConfigurationDictionary;

    mutable QMutex mutex;
    mutable QWaitCondition waitCond;

    QExtOsgiConfigurationAdminFactory* configurationAdminFactory;
    QExtOsgiConfigurationStore* configurationStore;
    /** @GuardedBy mutex*/
    QString pluginLocation;
    QString factoryPid;
    QString pid;
    QExtOsgiConfigurationDictionary dictionary;
    /** @GuardedBy mutex*/
    bool deleted;
    /** @GuardedBy mutex*/
    QSharedPointer<QExtOsgiPlugin> boundPlugin;
    /** @GuardedBy mutex*/
    mutable int lockedCount;
    /** @GuardedBy mutex*/
    mutable QThread* lockHolder;

    void checkDeleted() const;

    void updateDictionary(const QExtOsgiDictionary& properties);

};

typedef QSharedPointer<QExtOsgiConfigurationImpl> QExtOsgiConfigurationImplPtr;

class QExtOsgiConfigurationImplLocker
{
public:

    QExtOsgiConfigurationImplLocker(const QExtOsgiConfigurationImpl* impl);
    QExtOsgiConfigurationImplLocker(const QList<QExtOsgiConfigurationImplPtr>& implList);
    ~QExtOsgiConfigurationImplLocker();

private:

    const QExtOsgiConfigurationImpl* impl;
    QList<QExtOsgiConfigurationImplPtr> implList;
};

#endif // _QEXTOSGICONFIGURATIONIMPL_P_H
