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

#include "qtkbasiclocation_p.h"
#include "qtkpluginframeworkproperties_p.h"

#include <QTKCore/QTKException>

#include <QFileInfo>
#include <QUrl>
#include <QDir>
#include <QDebug>
#include <QReadLocker>
#include <QWriteLocker>

QTK_CORE_USE_NAMESPACE

QTK_PLUGINFRAMEWORK_BEGIN_NAMESPACE

static const char *CC_PROP_OSGI_LOCKING = "blueberry.locking";
static const char *CC_DEFAULT_LOCK_FILENAME = ".metadata/.lock";

struct QTKBasicLocation::Locker
{
    virtual ~Locker() {}
    virtual bool lock() = 0;
    virtual bool isLocked() const = 0;
    virtual void release() = 0;
};

struct QTKBasicLocation::MockLocker : public QTKBasicLocation::Locker
{
    bool lock() { return true; }
    bool isLocked() const { return false; }
    void release() {}
};


class QTKBasicLocation::FileLocker : public QTKBasicLocation::MockLocker
{
public:
    FileLocker(const QString&) {}
};


QTKBasicLocation::QTKBasicLocation(const QString &strProperty, const QUrl &defaultValue,
                                   bool bReadOnly, const QString &strDataAreaPrefix)
    : m_bReadOnly(bReadOnly)
    , m_pParent(nullptr)
    , m_defaultValue(defaultValue)
    , m_strProperty(strProperty)
    , m_strDataAreaPrefix(strDataAreaPrefix)
    , m_pLocker(nullptr)
    , m_sync()
{

}

QTKBasicLocation::~QTKBasicLocation()
{
    QWriteLocker writeLocker(&m_sync);
    delete m_pLocker;
}

bool QTKBasicLocation::allowsDefault() const
{
    QReadLocker readLocker(&m_sync);
    return !m_defaultValue.isEmpty();
}

QUrl QTKBasicLocation::getDefault() const
{
    QReadLocker readLocker(&m_sync);
    return m_defaultValue;
}

QTKLocation *QTKBasicLocation::getParentLocation() const
{
    QReadLocker readLocker(&m_sync);
    return m_pParent.data();
}

QUrl QTKBasicLocation::getUrl() const
{
    QWriteLocker writeLocker(&m_sync);
    if (m_location.isEmpty() && !m_defaultValue.isEmpty()) {
        const_cast<QTKBasicLocation*>(this)->setUnlocked(m_defaultValue, false);
    }
    return m_location;
}

bool QTKBasicLocation::isSet() const
{
    QReadLocker readLocker(&m_sync);
    return this->isSetUnlocked();
}

bool QTKBasicLocation::isReadOnly() const
{
    QReadLocker readLocker(&m_sync);
    return m_bReadOnly;
}

bool QTKBasicLocation::set(const QUrl &value, bool bLock)
{
    QWriteLocker writeLocker(&m_sync);
    return this->setUnlocked(value, bLock, QString::null);
}

bool QTKBasicLocation::set(const QUrl &value, bool bLock, const QString &strLockFilePath)
{
    QWriteLocker writeLocker(&m_sync);
    return this->setUnlocked(value, bLock, strLockFilePath);
}

bool QTKBasicLocation::lock()
{
    QWriteLocker writeLocker(&m_sync);
    if (!this->isSetUnlocked()) {
        throw QTKRuntimeException("The location has not been set.");
    }
    return this->lockUnlocked(m_lockFileInfo, m_location);
}

void QTKBasicLocation::release()
{
    QWriteLocker writeLocker(&m_sync);
    if (m_pLocker) {
        m_pLocker->release();
    }
}

bool QTKBasicLocation::isLocked() const
{
    QReadLocker readLocker(&m_sync);
    if (!this->isSetUnlocked()) {
        return false;
    }
    return this->isLocked_unlocked(m_lockFileInfo);
}

QTKLocation *QTKBasicLocation::createLocation(QTKLocation *pParent, const QUrl &defaultValue, bool bReadonly)
{
    QWriteLocker l(&m_sync);
    QTKBasicLocation* result = new QTKBasicLocation(QString::null, defaultValue, bReadonly, m_strDataAreaPrefix);
    result->m_pParent.reset(pParent);
    return result;
}

QUrl QTKBasicLocation::getDataArea(const QString &strPath) const
{
    QUrl base = this->getUrl();
    if (base.isEmpty()) {
        throw QTKRuntimeException("The location has not been set.");
    }
    QString strPrefix = base.toLocalFile();
    if (!strPrefix.isEmpty() && strPrefix.at(strPrefix.size() - 1) != '/') {
        strPrefix += '/';
    }
    QString strFilename = strPath;
    strFilename.replace('\\', '/');
    if (!strFilename.isEmpty() && strFilename.at(0) == '/') {
        strFilename = strFilename.mid(1);
    }

    QReadLocker readLocker(&m_sync);
    return QUrl(strPrefix + m_strDataAreaPrefix + strFilename);
}

void QTKBasicLocation::setParent(QTKLocation *pParent)
{
    QWriteLocker writeLocker(&this->m_sync);
    m_pParent.reset(pParent);
}

bool QTKBasicLocation::isSetUnlocked() const
{
    return !m_location.isEmpty();
}

bool QTKBasicLocation::setUnlocked(QUrl value, bool lock)
{
    return this->setUnlocked(value, lock, QString::null);
}

bool QTKBasicLocation::setUnlocked(QUrl value, bool lock, const QString &strLockFilePath)
{
    if (!m_location.isEmpty()) {
        throw QTKIllegalStateException("Cannot change the location once it is set.");
    }

    QFileInfo fileInfo;
    if (value.scheme().compare("file", Qt::CaseInsensitive) == 0) {
        QString strBasePath = QFileInfo(value.toLocalFile()).absolutePath();
        if (!strBasePath.isEmpty()) {
            value = QUrl::fromLocalFile(strBasePath);
        }

        if (!strLockFilePath.isEmpty()) {
            QFileInfo givenLockFile(strLockFilePath);
            if (givenLockFile.isAbsolute()) {
                fileInfo = givenLockFile;
            } else {
                fileInfo = QFileInfo(QDir(value.toLocalFile()), strLockFilePath);
            }
        } else {
            fileInfo = QFileInfo(QDir(value.toLocalFile()), CC_DEFAULT_LOCK_FILENAME);
        }
    }
    lock = lock && !m_bReadOnly;
    if (lock) {
        if (!this->lockUnlocked(fileInfo, value)) {
            return false;
        }
    }
    m_lockFileInfo = fileInfo;
    m_location = value;
    if (!m_strProperty.isEmpty()) {
        QTKPluginFrameworkProperties::setProperty(m_strProperty, m_location.toString());
    }
    return lock;
}

bool QTKBasicLocation::lockUnlocked(const QFileInfo &lock, const QUrl &locationValue)
{
    if (m_bReadOnly) {
        throw QTKRuntimeException(QString("The folder \"%1\" is read-only.").arg(lock.absoluteFilePath()));
    }

    if (lock.fileName().isEmpty()) {
        if (locationValue.scheme().compare("file", Qt::CaseInsensitive) != 0) {
            throw QTKRuntimeException(QString("Unable to lock the location. The set location is not a file URL: ") + locationValue.toString());
        }
        throw QTKIllegalStateException("The lock file has not been set"); // this is really unexpected
    }

    if (this->isLocked()) {
        return false;
    }

    QDir parentDir = lock.dir();
    if (!parentDir.exists()) {
        if (!parentDir.mkpath(lock.canonicalPath())) {
            throw QTKRuntimeException(QString("The folder \"%1\" is read-only.").arg(parentDir.absolutePath()));
        }
    }

    this->setLockerUnlocked(lock);
    if (m_pLocker == nullptr) {
        return true;
    }
    bool bLocked = m_pLocker->lock();
    if (!bLocked) {
        delete m_pLocker;
    }
    return bLocked;
}

void QTKBasicLocation::setLockerUnlocked(const QFileInfo &lock)
{
    if (nullptr != m_pLocker) {
        return;
    }

    QString strLockMode = QTKPluginFrameworkProperties::getProperty(CC_PROP_OSGI_LOCKING).toString();
    m_pLocker = this->createLockerUnlocked(lock, strLockMode);
}

QTKBasicLocation::Locker *QTKBasicLocation::createLockerUnlocked(const QFileInfo &lock,
                                                                 QString strLockMode)
{
    if (strLockMode.isEmpty()) {
        strLockMode = QTKPluginFrameworkProperties::getProperty(CC_PROP_OSGI_LOCKING).toString();
    }

    if (strLockMode == "none") {
        return new MockLocker();
    }

    if (strLockMode == "qt.lockfile") {
        return new FileLocker(lock.canonicalFilePath());
    }

    // Backup case if an invalid value has been specified
    return new FileLocker(lock.canonicalFilePath());
}

bool QTKBasicLocation::isLocked_unlocked(const QFileInfo &lock) const
{
    if (lock.fileName().isEmpty() || m_bReadOnly) {
        return true;
    }
    if (!lock.exists()) {
        return false;
    }
    const_cast<QTKBasicLocation *>(this)->setLockerUnlocked(lock);
    return this->m_pLocker->isLocked();
}

QTK_PLUGINFRAMEWORK_END_NAMESPACE
