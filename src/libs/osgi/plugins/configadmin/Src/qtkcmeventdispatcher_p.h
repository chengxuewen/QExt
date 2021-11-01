#ifndef QTKCMEVENTDISPATCHER_P_H
#define QTKCMEVENTDISPATCHER_P_H

#include "qtkcmserializedtaskqueue_p.h"

#include <QTKPluginFramework/QTKServiceTracker>
#include <QTKPluginFramework/Service/Config/QTKConfigurationEvent>
#include <QTKPluginFramework/Service/Config/QTKConfigurationListener>
#include <QTKPluginFramework/Service/Log/QTKLogService>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

/**
 * EventDispatcher is responsible for delivering Configuration Events to ConfigurationListeners.
 * The originating ConfigAdmin ServiceReference is needed when delivering events. This reference
 * is made available by the service factory before returning the service object.
 */
class QTKCMEventDispatcher
{
public:
    QTKCMEventDispatcher(QTKPluginContext* context, QTKLogService* log);

    void start();
    void stop();

    void setServiceReference(const QTKServiceReference& reference);
    void dispatchEvent(QTKConfigurationEvent::Type type, const QString& factoryPid, const QString& pid);

private:
    QMutex mutex;
    QTKServiceTracker<QTKConfigurationListener*> tracker;
    QTKCMSerializedTaskQueue queue;
    /** @GuardedBy mutex */
    QTKServiceReference configAdminReference;
    QTKLogService * const log;

    QTKConfigurationEvent createConfigurationEvent(QTKConfigurationEvent::Type type, const QString& factoryPid, const QString& pid);
};

#endif // QTKCMEVENTDISPATCHER_P_H
