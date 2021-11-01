#ifndef QTKCONFIGURATIONADMINACTIVATOR_P_H
#define QTKCONFIGURATIONADMINACTIVATOR_P_H

#include <QTKPluginFramework/QTKPluginActivator>

#include "qtkcmlogtracker_p.h"
#include "qtkcmlogtracker_p.h"

class QTKConfigurationAdminFactory;
class QTKConfigurationEventAdapter;

/**
 * The QTKConfigurationAdminActivator starts the QTKConfigurationAdminFactory but also handles passing in the Service
 * Registration needed by Asynch threads. Asynch threads are controlled by the QTKConfigurationAdminFactory
 * start and stop. It requires some care to handle pending events as the service is registered before
 * activating the threads. (see QTKConfigurationAdminEventDispatcher)
 */
class QTKConfigurationAdminActivator : public QObject, public QTKPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginActivator)
    Q_PLUGIN_METADATA(IID "QTKConfigurationAdminActivator")

public:
    QTKConfigurationAdminActivator();
    ~QTKConfigurationAdminActivator();

    void start(QTKPluginContext* context);
    void stop(QTKPluginContext* context);

private:
    QFile logFileFallback;
    QTKCMLogTracker* logTracker;
    QTKServiceRegistration registration;
    QTKConfigurationAdminFactory* factory;
    QTKConfigurationEventAdapter* eventAdapter;

}; // QTKConfigurationAdminActivator

#endif // QTKCONFIGURATIONADMINACTIVATOR_P_H
