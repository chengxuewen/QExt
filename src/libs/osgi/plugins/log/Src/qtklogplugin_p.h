#ifndef QTKLOGPLUGIN_P_H
#define QTKLOGPLUGIN_P_H

#include <QTKPluginFramework/QTKPluginActivator>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKLogQDebug;

class QTKLogPlugin : public QObject, public QTKPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginActivator)
    Q_PLUGIN_METADATA(IID "QTKLogPlugin")

public:
    QTKLogPlugin();

    void start(QTKPluginContext *pContext);
    void stop(QTKPluginContext *pContext);

private:
    QTKLogQDebug *m_pLogService;

}; // QTKLogPlugin

#endif // QTKLOGPLUGIN_P_H
