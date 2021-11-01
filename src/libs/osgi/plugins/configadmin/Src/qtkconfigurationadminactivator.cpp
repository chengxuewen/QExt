#include "qtkconfigurationadminactivator_p.h"
#include "qtkconfigurationadminfactory_p.h"
#include "qtkconfigurationeventadapter_p.h"

#include <QTKPluginFramework/QTKServiceTracker>
#include <QTKPluginFramework/Service/Config/QTKConfigurationAdmin>
#include <QTKPluginFramework/Service/Config/QTKConfigurationListener>

#include <QtPlugin>


QTKConfigurationAdminActivator::QTKConfigurationAdminActivator()
    : logTracker(0), factory(0), eventAdapter(0)
{
}

QTKConfigurationAdminActivator::~QTKConfigurationAdminActivator()
{
    delete logTracker;
    delete factory;
}

void QTKConfigurationAdminActivator::start(QTKPluginContext* context)
{
    logFileFallback.open(stdout, QIODevice::WriteOnly);
    logTracker = new QTKCMLogTracker(context, &logFileFallback);
    logTracker->open();
    eventAdapter = new QTKConfigurationEventAdapter(context);
    eventAdapter->start();
    factory = new QTKConfigurationAdminFactory(context, logTracker);
    factory->start();
    context->connectPluginListener(factory, SLOT(pluginChanged(QTKPluginEvent)));
    registration = context->registerService<QTKConfigurationAdmin>(factory);
}

void QTKConfigurationAdminActivator::stop(QTKPluginContext* context)
{
    Q_UNUSED(context)

    if (registration)
    {
        registration.unregister();
    }

    factory->stop();
    delete factory;
    factory = 0;

    eventAdapter->stop();
    delete eventAdapter;
    eventAdapter = 0;

    logTracker->close();
    delete logTracker;
    logTracker = 0;

    logFileFallback.close();
}
