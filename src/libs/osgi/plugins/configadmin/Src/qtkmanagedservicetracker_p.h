#ifndef QTKMANAGEDSERVICETRACKER_P_H
#define QTKMANAGEDSERVICETRACKER_P_H

#include "qtkcmserializedtaskqueue_p.h"

#include <QTKPluginFramework/QTKServiceTracker>
#include <QTKPluginFramework/Service/Config/QTKManagedService>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKConfigurationAdminFactory;
class QTKConfigurationStore;
class QTKConfigurationImpl;

/**
 * QTKManagedServiceTracker tracks... ManagedServices and notifies them about related configuration changes
 */
class QTKManagedServiceTracker : public QTKServiceTracker<QTKManagedService*>
{
public:
    QTKManagedServiceTracker(QTKConfigurationAdminFactory* configurationAdminFactory,
                             QTKConfigurationStore* configurationStore,
                             QTKPluginContext* context);

    QTKManagedService* addingService(const QTKServiceReference& reference);
    void modifiedService(const QTKServiceReference& reference, QTKManagedService* service);
    void removedService(const QTKServiceReference& reference, QTKManagedService* service);

    void notifyDeleted(QTKConfigurationImpl* config);
    void notifyUpdated(QTKConfigurationImpl* config);

private:
    QTKPluginContext* context;
    QTKConfigurationAdminFactory* configurationAdminFactory;
    QMutex configurationStoreMutex;
    QTKConfigurationStore* configurationStore;

    // managedServiceMutex guards both managedServices and managedServiceReferences
    mutable QMutex managedServiceMutex;
    QHash<QString, QTKManagedService*> managedServices;
    QHash<QString, QTKServiceReference> managedServiceReferences;

    QTKCMSerializedTaskQueue queue;

    void addManagedService(const QTKServiceReference& reference, const QString& pid,
                           QTKManagedService* service);

    void removeManagedService(const QTKServiceReference& reference, const QString& pid);

    bool trackManagedService(const QString& pid, const QTKServiceReference& reference,
                             QTKManagedService* service);

    void untrackManagedService(const QString& pid, const QTKServiceReference& reference);

    QTKManagedService* getManagedService(const QString& pid) const;

    QTKServiceReference getManagedServiceReference(const QString& pid) const;

    QString getPidForManagedService(QTKManagedService* service) const;

    void asynchUpdated(QTKManagedService* service, const QTKDictionary& properties);
};

#endif // QTKMANAGEDSERVICETRACKER_P_H
