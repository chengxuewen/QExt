#ifndef QTKMETATYPEACTIVATOR_P_H
#define QTKMETATYPEACTIVATOR_P_H

#include <QTKPluginFramework/QTKPluginActivator>
#include <QTKPluginFramework/Service/Log/QTKLogService>
#include <QTKPluginFramework/QTKServiceTracker>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKMTLogTracker;
class QTKMetaTypeServiceImpl;

class QTKMetaTypeActivator : public QObject, public QTKPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginActivator)
    Q_PLUGIN_METADATA(IID "QTKMetaTypeActivator")

private:

    QMutex mutex;

    QFile logFileFallback;

    static QTKMTLogTracker* logTracker;

    /*
   * The following filter guarantees only services meeting the following
   * criteria will be tracked.
   *
   * (1) A QTKManagedService or QTKManagedServiceFactory registered with a
   * SERVICE_PID property. May also be registered as a QTKMetaTypeProvider.
   * (2) A QTKMetaTypeProvider registered with a METATYPE_PID or
   * METATYPE_FACTORY_PID property.
   *
   * Note that it's still necessary to inspect a QTKManagedService or
   * QTKManagedServiceFactory to ensure it also implements QTKMetaTypeProvider.
   */
    static QString FILTER();
    static const QString SERVICE_PID; // = "org.qtk.metatype.impl.MetaType"

    // Could be QTKManagedService, QTKManagedServiceFactory, or QTKMetaTypeProvider.
    // The tracker tracks all services regardless of the plugin. Services are
    // filtered by plugin later in the QTKMTProviderTracker class. It may
    // therefore be shared among multiple instances of that class.
    QTKServiceTracker<>* metaTypeProviderTracker;

    QTKMetaTypeServiceImpl* metaTypeService;
    QTKServiceRegistration metaTypeServiceRegistration;

public:

    QTKMetaTypeActivator();
    ~QTKMetaTypeActivator();

    void start(QTKPluginContext* context);
    void stop(QTKPluginContext* context);

    /**
   * Gets a wrapper log service object. This object will either print messages
   * to standard out if no QTKLogService is present or call the respective
   * methods of available QTKLogService instances.
   */
    static QTKLogService* getLogService();

}; // QTKMetaTypeActivator

#endif // QTKMETATYPEACTIVATOR_P_H
