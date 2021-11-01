#ifndef QTKPUBLISHERPLUGIN_H
#define QTKPUBLISHERPLUGIN_H

#include <QTKPluginFramework/QTKPluginActivator>

#include <QObject>
#include <QScopedPointer>
#include <QTimer>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKEventPublisherPlugin : public QObject, public QTKPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginActivator)
    Q_PLUGIN_METADATA(IID "QTKEventPublisherPlugin")

public:
    void start(QTKPluginContext *pContext) Q_DECL_OVERRIDE;
    void stop(QTKPluginContext *pContext) Q_DECL_OVERRIDE;

private slots:
    void timerTimeout();

private:
    QTimer m_timer;
    QTKPluginContext *m_pContext;
};

#endif // QTKPUBLISHERPLUGIN_H
