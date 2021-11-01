#ifndef QTKCONFIGURATIONIMPL_P_H
#define QTKCONFIGURATIONIMPL_P_H

#include <QTKPluginFramework/Service/Config/QTKConfiguration>
#include <QTKPluginFramework/QTKPlugin>

#include <QMutex>
#include <QWaitCondition>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKConfigurationAdminFactory;
class QTKConfigurationStore;

class QTKConfigurationImpl : public QTKConfiguration
{
public:
    QTKConfigurationImpl(QTKConfigurationAdminFactory* configurationAdminFactory,
                         QTKConfigurationStore* configurationStore,
                         const QString& factoryPid, const QString& pid,
                         const QString& pluginLocation);

    QTKConfigurationImpl(QTKConfigurationAdminFactory* configurationAdminFactory,
                         QTKConfigurationStore* configurationStore,
                         const QTKDictionary& dictionary);

    void remove();

    QString getPluginLocation() const;
    QString getFactoryPid() const;
    QString getPid() const;
    QTKDictionary getProperties() const;

    void setPluginLocation(const QString& pluginLocation);

    void update();
    void update(const QTKDictionary& properties);

    void checkLocked() const;

    bool bind(QSharedPointer<QTKPlugin> plugin);
    void unbind(QSharedPointer<QTKPlugin> plugin);

    QString getPluginLocation(bool checkPermission) const;
    QString getFactoryPid(bool checkDeleted) const;
    QString getPid(bool checkDeleted) const;
    QTKDictionary getAllProperties() const;

    void lock() const;
    void unlock() const;

    bool isDeleted() const;

private:

    typedef QTKDictionary QTKConfigurationDictionary;

    mutable QMutex mutex;
    mutable QWaitCondition waitCond;

    QTKConfigurationAdminFactory* configurationAdminFactory;
    QTKConfigurationStore* configurationStore;
    /** @GuardedBy mutex*/
    QString pluginLocation;
    QString factoryPid;
    QString pid;
    QTKConfigurationDictionary dictionary;
    /** @GuardedBy mutex*/
    bool deleted;
    /** @GuardedBy mutex*/
    QSharedPointer<QTKPlugin> boundPlugin;
    /** @GuardedBy mutex*/
    mutable int lockedCount;
    /** @GuardedBy mutex*/
    mutable QThread* lockHolder;

    void checkDeleted() const;

    void updateDictionary(const QTKDictionary& properties);

};

typedef QSharedPointer<QTKConfigurationImpl> QTKConfigurationImplPtr;

class QTKConfigurationImplLocker
{
public:

    QTKConfigurationImplLocker(const QTKConfigurationImpl* impl);
    QTKConfigurationImplLocker(const QList<QTKConfigurationImplPtr>& implList);
    ~QTKConfigurationImplLocker();

private:

    const QTKConfigurationImpl* impl;
    QList<QTKConfigurationImplPtr> implList;
};

#endif // QTKCONFIGURATIONIMPL_P_H
