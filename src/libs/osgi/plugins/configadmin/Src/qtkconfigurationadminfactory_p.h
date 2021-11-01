#ifndef QTKCONFIGURATIONADMINFACTORY_P_H
#define QTKCONFIGURATIONADMINFACTORY_P_H

#include "qtkcmeventdispatcher_p.h"
#include "qtkcmpluginmanager_p.h"
#include "qtkconfigurationstore_p.h"
#include "qtkconfigurationimpl_p.h"
#include "qtkconfigurationadminimpl_p.h"
#include "qtkmanagedservicetracker_p.h"
#include "qtkmanagedservicefactorytracker_p.h"

#include <QTKPluginFramework/QTKPluginEvent>
#include <QTKPluginFramework/QTKServiceFactory>
#include <QTKPluginFramework/Service/Config/QTKConfigurationListener>
#include <QTKPluginFramework/Service/Log/QTKLogService>

#include <QObject>

/**
 * QTKConfigurationAdminFactory provides a Configuration Admin ServiceFactory but more significantly
 * launches the whole implementation.
 */
class QTKConfigurationAdminFactory : public QObject, public QTKServiceFactory
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKServiceFactory)

public:
    QTKConfigurationAdminFactory(QTKPluginContext* context, QTKLogService* log);
    ~QTKConfigurationAdminFactory();

    void start();
    void stop();

    QObject* getService(QSharedPointer<QTKPlugin> plugin, QTKServiceRegistration registration);
    void ungetService(QSharedPointer<QTKPlugin> plugin, QTKServiceRegistration registration, QObject* service);

    void checkConfigurationPermission();

    QTKLogService* getLogService() const;

    void dispatchEvent(QTKConfigurationEvent::Type type, const QString& factoryPid, const QString& pid);

    void notifyConfigurationUpdated(QTKConfigurationImpl* config, bool isFactory);
    void notifyConfigurationDeleted(QTKConfigurationImpl* config, bool isFactory);

    void modifyConfiguration(const QTKServiceReference& reference, QTKDictionary& properties);

public Q_SLOTS:
    void pluginChanged(const QTKPluginEvent& event);

private:

    //Permission configurationPermission = new ConfigurationPermission("*", ConfigurationPermission.CONFIGURE); //$NON-NLS-1$
    QTKCMEventDispatcher eventDispatcher;
    QTKCMPluginManager pluginManager;
    QTKLogService* logService;
    QTKConfigurationStore configurationStore;
    QTKManagedServiceTracker managedServiceTracker;
    QTKManagedServiceFactoryTracker managedServiceFactoryTracker;

    QList<QTKConfigurationAdminImpl*> configAdmins;
};

#endif // QTKCONFIGURATIONADMINFACTORY_P_H
