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

#ifndef QTKBASICLOCATION_P_H
#define QTKBASICLOCATION_P_H

#include "Service/Location/qtklocation.h"

#include <QUrl>
#include <QString>
#include <QFileInfo>
#include <QReadWriteLock>

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

/**
 * @ingroup QTKPluginFramework
 * @brief The QTKBasicLocation class
 */
class QTK_PLUGINFRAMEWORK_EXPORT QTKBasicLocation : public QObject, public QTKLocation
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKLocation)

public:
    QTKBasicLocation(const QString &strProperty, const QUrl &defaultValue,
                     bool bReadOnly, const QString &strDataAreaPrefix);
    ~QTKBasicLocation();

    bool allowsDefault() const;
    QUrl getDefault() const;
    QTKLocation *getParentLocation() const;
    QUrl getUrl() const;
    bool isSet() const;
    bool isReadOnly() const;

    bool set(const QUrl &value, bool lock);
    bool set(const QUrl &value, bool lock, const QString &strLockFilePath);

    bool lock();
    void release();
    bool isLocked() const;

    QTKLocation* createLocation(QTKLocation *pParent, const QUrl &defaultValue, bool bReadonly);
    QUrl getDataArea(const QString &strPath) const;
    void setParent(QTKLocation *pParent);

    struct Locker;

private:
    bool isSetUnlocked() const;
    bool setUnlocked(QUrl value, bool lock);
    bool setUnlocked(QUrl value, bool lock, const QString &strLockFilePath);
    bool lockUnlocked(const QFileInfo &lock, const QUrl &locationValue);
    void setLockerUnlocked(const QFileInfo &lock);
    Locker *createLockerUnlocked(const QFileInfo &lock, QString strLockMode);
    bool isLocked_unlocked(const QFileInfo &lock) const;

    struct MockLocker;
    class FileLocker;
    bool m_bReadOnly;
    QUrl m_location;
    QScopedPointer<QTKLocation> m_pParent;
    QUrl m_defaultValue;
    QString m_strProperty;
    QString m_strDataAreaPrefix;

    // locking related fields
    QFileInfo m_lockFileInfo;
    Locker *m_pLocker;

    mutable QReadWriteLock m_sync;
};

QTK_PLUGINFRAMEWORK_END_NAMESPACE

#endif // QTKBASICLOCATION_P_H
