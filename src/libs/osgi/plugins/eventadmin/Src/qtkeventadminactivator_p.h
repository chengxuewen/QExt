#ifndef QTKEVENTADMINACTIVATOR_H
#define QTKEVENTADMINACTIVATOR_H

#include <QTKPluginFramework/QTKPluginActivator>
#include <QTKPluginFramework/Service/Log/QTKLogService>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEALogTracker;
class QTKEAConfiguration;

class QTKEventAdminActivator : public QObject, public QTKPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginActivator)
    Q_PLUGIN_METADATA(IID "QTKEventAdminActivator")

public:
    QTKEventAdminActivator();
    ~QTKEventAdminActivator();

    void start(QTKPluginContext *pContext);

    void stop(QTKPluginContext *pContext);

    static QTKLogService *getLogService();

private:
    static QTKEALogTracker *sm_pLogTracker;
    QFile m_logFileFallback;
    QTKEAConfiguration *m_pConfig;
};


#endif // QTKEVENTADMINACTIVATOR_H
