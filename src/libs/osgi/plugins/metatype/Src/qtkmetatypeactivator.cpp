#include "qtkmetatypeactivator_p.h"
#include "qtkmtlogtracker_p.h"
#include "qtkmetatypeserviceimpl_p.h"
#include "qtkmtmsg_p.h"

#include <QTKPluginFramework/Service/Config/QTKManagedService>
#include <QTKPluginFramework/Service/Metatype/QTKMetaTypeProvider>

#include <QtPlugin>

QTKMTLogTracker* QTKMetaTypeActivator::logTracker = 0;

QString QTKMetaTypeActivator::FILTER()
{
    static QString filter(QString("(|(&(") + QTKPluginConstants::OBJECT_CLASS
                          + "=" + qobject_interface_iid<QTKManagedService*>() + "*)("
                          + QTKPluginConstants::SERVICE_PID + "=*))(&("
                          + QTKPluginConstants::OBJECT_CLASS + '='
                          + qobject_interface_iid<QTKMetaTypeProvider*>() + ")(|("
                          + QTKMetaTypeProvider::METATYPE_PID + "=*)("
                          + QTKMetaTypeProvider::METATYPE_FACTORY_PID + "=*))))");
    return filter;
}

const QString QTKMetaTypeActivator::SERVICE_PID = "org.qtk.metatype.impl.MetaType";

QTKMetaTypeActivator::QTKMetaTypeActivator()
    : metaTypeProviderTracker(0), metaTypeService(0)
{
}

QTKMetaTypeActivator::~QTKMetaTypeActivator()
{
    delete metaTypeProviderTracker;
    delete metaTypeService;
    delete logTracker;
    logTracker = 0;
}

void QTKMetaTypeActivator::start(QTKPluginContext* context)
{
    delete metaTypeProviderTracker;
    delete metaTypeService;
    delete logTracker;

    QTKMTLogTracker* lsTracker = 0;
    logFileFallback.open(stdout, QIODevice::WriteOnly);
    QTKLDAPSearchFilter filter(FILTER());
    QTKServiceTracker<>* mtpTracker = 0;

    {
        QMutexLocker l(&mutex);
        lsTracker = logTracker = new QTKMTLogTracker(context, &logFileFallback);
        mtpTracker = metaTypeProviderTracker = new QTKServiceTracker<>(context, filter);
    }
    // Do this first to make logging available as early as possible.
    lsTracker->open();
//    QTK_DEBUG(lsTracker) << "====== Meta Type Service starting ! =====";
    // Do this next to make QTKMetaTypeProviders available as early as possible.
    mtpTracker->open();

    // Register the Meta Type service
    QTKDictionary properties;
    properties.insert(QTKPluginConstants::SERVICE_VENDOR, "qtk");
    properties.insert(QTKPluginConstants::SERVICE_DESCRIPTION, QTKMTMsg::SERVICE_DESCRIPTION);
    properties.insert(QTKPluginConstants::SERVICE_PID, SERVICE_PID);
    metaTypeService = new QTKMetaTypeServiceImpl(lsTracker, mtpTracker);
    context->connectPluginListener(metaTypeService, SLOT(pluginChanged(QTKPluginEvent)), Qt::DirectConnection);
    metaTypeServiceRegistration = context->registerService<QTKMetaTypeService>(metaTypeService, properties);
}

void QTKMetaTypeActivator::stop(QTKPluginContext* context)
{
    Q_UNUSED(context)

    QTK_DEBUG(logTracker) << "====== Meta Type Service stopping ! =====";
    metaTypeService->disconnect();
    metaTypeProviderTracker->close();
    metaTypeServiceRegistration.unregister();
    metaTypeServiceRegistration = 0;
    // Do this last to leave logging available as long as possible.
    logTracker->close();
}

QTKLogService* QTKMetaTypeActivator::getLogService()
{
    return logTracker;
}
