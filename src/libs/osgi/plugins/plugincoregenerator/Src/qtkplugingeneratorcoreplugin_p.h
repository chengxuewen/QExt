#ifndef QTKPLUGINGENERATORCOREPLUGIN_H
#define QTKPLUGINGENERATORCOREPLUGIN_H

#include <QTKPluginFramework/QTKPluginActivator>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKPluginGeneratorCodeModel;

class QTKPluginGeneratorCorePlugin : public QObject, public QTKPluginActivator
{
    Q_OBJECT
    Q_INTERFACES(QTK_PLUGINFRAMEWORK_NAMESPACE::QTKPluginActivator)
    Q_PLUGIN_METADATA(IID "QTKPluginGeneratorCorePlugin")

public:

    void start(QTKPluginContext* context);
    void stop(QTKPluginContext* context);

    QTKPluginContext* getContext() const;

    QTKPluginGeneratorCodeModel* getCodeModel() const;

    static QTKPluginGeneratorCorePlugin* getInstance();

private:

    static QTKPluginGeneratorCorePlugin* instance;

    QTKPluginContext* pluginContext;

    QTKPluginGeneratorCodeModel* codeModel;
};

#endif // QTKPLUGINGENERATORCOREPLUGIN_H
