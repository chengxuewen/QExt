#ifndef QTKMANAGEDSERVICEFACTORYTRACKER_P_H
#define QTKMANAGEDSERVICEFACTORYTRACKER_P_H

#include "qtkcmserializedtaskqueue_p.h"

#include <QTKPluginFramework/QTKServiceTracker>
#include <QTKPluginFramework/Service/Config/QTKManagedServiceFactory>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKConfigurationAdminFactory;
class QTKConfigurationStore;
class QTKConfigurationImpl;

class QTKManagedServiceFactoryTracker : public QTKServiceTracker<QTKManagedServiceFactory*>
{
public:
    QTKManagedServiceFactoryTracker(QTKConfigurationAdminFactory* configurationAdminFactory,
                                    QTKConfigurationStore* configurationStore,
                                    QTKPluginContext* context);

    QTKManagedServiceFactory* addingService(const QTKServiceReference& reference);
    void modifiedService(const QTKServiceReference& reference, QTKManagedServiceFactory* service);
    void removedService(const QTKServiceReference& reference, QTKManagedServiceFactory* service);

    void notifyDeleted(QTKConfigurationImpl* config);
    void notifyUpdated(QTKConfigurationImpl* config);

private:

    QTKPluginContext* context;
    QTKConfigurationAdminFactory* configurationAdminFactory;
    QMutex configurationStoreMutex;
    QTKConfigurationStore* configurationStore;

    // managedServiceFactoryMutex guards both managedServiceFactories and managedServiceFactoryReferences
    mutable QMutex managedServiceFactoryMutex;
    QHash<QString, QTKManagedServiceFactory*> managedServiceFactories;
    QHash<QString, QTKServiceReference> managedServiceFactoryReferences;

    QTKCMSerializedTaskQueue queue;

    void addManagedServiceFactory(const QTKServiceReference& reference,
                                  const QString& factoryPid,
                                  QTKManagedServiceFactory* service);

    void removeManagedServiceFactory(const QTKServiceReference& reference,
                                     const QString& factoryPid);

    bool trackManagedServiceFactory(const QString& factoryPid,
                                    const QTKServiceReference& reference,
                                    QTKManagedServiceFactory* service);

    void untrackManagedServiceFactory(const QString& factoryPid,
                                      const QTKServiceReference& reference);

    QTKManagedServiceFactory* getManagedServiceFactory(const QString& factoryPid) const;

    QTKServiceReference getManagedServiceFactoryReference(const QString& factoryPid) const;

    QString getPidForManagedServiceFactory(QTKManagedServiceFactory* service) const;

    void asynchDeleted(QTKManagedServiceFactory* service, const QString& pid);

    void asynchUpdated(QTKManagedServiceFactory* service, const QString& pid,
                       const QTKDictionary& properties);
};

#endif // QTKMANAGEDSERVICEFACTORYTRACKER_P_H
