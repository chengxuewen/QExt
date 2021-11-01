#ifndef QTKEVENTBUSPLUGIN_H
#define QTKEVENTBUSPLUGIN_H

#include <QTKPluginFramework/QTKPluginActivator>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEventBusImpl;

class QTKEventBusPlugin : public QObject, public QTKPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginActivator)
    Q_PLUGIN_METADATA(IID "QTKEventBusPlugin")

public:
    QTKEventBusPlugin() {}
    ~QTKEventBusPlugin() {}

    void start(QTKPluginContext *pContext) Q_DECL_OVERRIDE;
    void stop(QTKPluginContext *pContext) Q_DECL_OVERRIDE;

    static QTKEventBusPlugin* getInstance();

    QTKPluginContext *getPluginContext() const;

private:
    static QTKEventBusPlugin *m_pInstance;
    QTKPluginContext *m_pContext;
    QTKEventBusImpl *m_pBus;
};


#endif // QTKEVENTBUSPLUGIN_H
