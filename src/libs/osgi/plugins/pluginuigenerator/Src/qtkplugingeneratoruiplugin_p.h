#ifndef QTKPLUGINGENERATORUIPLUGIN_H
#define QTKPLUGINGENERATORUIPLUGIN_H

#include <QTKPluginFramework/QTKPluginActivator>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKPluginGeneratorAbstractUiExtension;

class QTKPluginGeneratorUiPlugin : public QObject, public QTKPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginActivator)
    Q_PLUGIN_METADATA(IID "QTKPluginGeneratorUiPlugin")

public:

    void start(QTKPluginContext* context);
    void stop(QTKPluginContext* context);

private:

    QTKPluginGeneratorAbstractUiExtension* mainExtension;
};

#endif // QTKPLUGINGENERATORUIPLUGIN_H
