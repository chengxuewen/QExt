#ifndef QTKCONFIGURATIONEVENTADAPTER_P_H
#define QTKCONFIGURATIONEVENTADAPTER_P_H

#include <QTKPluginFramework/QTKServiceTracker>
#include <QTKPluginFramework/Service/Config/QTKConfigurationListener>
#include <QTKPluginFramework/Service/Event/QTKEventAdmin>

#include <QObject>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKConfigurationEventAdapter : public QObject, public QTKConfigurationListener
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKConfigurationListener)

public:
    static const QString TOPIC; // = "org/qtk/service/cm/configurationevent"
    static const QChar TOPIC_SEPARATOR; // = '/'
    // constants for Event types
    static const QString CM_UPDATED; // = "CM_UPDATED"
    static const QString CM_DELETED; // = "CM_DELETED"
    // constants for Event properties
    static const QString CM_FACTORY_PID; // = "cm.factoryPid"
    static const QString CM_PID; // = "cm.pid"
    static const QString SERVICE; // = "service"
    static const QString SERVICE_ID; // = "service.id"
    static const QString SERVICE_OBJECTCLASS; // = "service.objectClass"
    static const QString SERVICE_PID; // = "service.pid"

private:
    QTKPluginContext* const context;
    QTKServiceRegistration configListenerRegistration;
    QTKServiceTracker<QTKEventAdmin*> eventAdminTracker;

public:
    QTKConfigurationEventAdapter(QTKPluginContext* context);

    void start();
    void stop();

    void configurationEvent(const QTKConfigurationEvent& event);

    void putServiceReferenceProperties(QTKDictionary& properties, const QTKServiceReference& ref);
};

#endif // QTKCONFIGURATIONEVENTADAPTER_P_H
