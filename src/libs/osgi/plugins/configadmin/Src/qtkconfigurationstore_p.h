#ifndef QTKCONFIGURATIONSTORE_P_H
#define QTKCONFIGURATIONSTORE_P_H

#include "qtkconfigurationimpl_p.h"

#include <QTKPluginFramework/QTKLDAPSearchFilter>
#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/QTKPlugin>

#include <QSharedPointer>
#include <QHash>
#include <QDir>
#include <QMutex>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKConfigurationImpl;
class QTKConfigurationAdminFactory;

class QTKConfigurationStore
{
public:
    QTKConfigurationStore(QTKConfigurationAdminFactory* configurationAdminFactory,
                          QTKPluginContext* context);

    void saveConfiguration(const QString& pid, QTKConfigurationImpl* config);
    void removeConfiguration(const QString& pid);

    QTKConfigurationImplPtr getConfiguration(const QString& pid, const QString& location);

    QTKConfigurationImplPtr createFactoryConfiguration(
            const QString& factoryPid, const QString& location);

    QTKConfigurationImplPtr findConfiguration(const QString& pid);

    QList<QTKConfigurationImplPtr> getFactoryConfigurations(const QString& factoryPid);
    QList<QTKConfigurationImplPtr> listConfigurations(const QTKLDAPSearchFilter& filter);

    void unbindConfigurations(QSharedPointer<QTKPlugin> plugin);

private:

    QMutex mutex;
    QTKConfigurationAdminFactory* configurationAdminFactory;
    static const QString STORE_DIR; // = "store"
    static const QString PID_EXT; // = ".pid"
    QHash<QString, QTKConfigurationImplPtr> configurations;
    int createdPidCount;
    QDir store;


    void writeConfigurationFile(QFile& configFile,
                                const QTKDictionary& configProperties);
    void deleteConfigurationFile(QFile& configFile);

};

#endif // QTKCONFIGURATIONSTORE_P_H
