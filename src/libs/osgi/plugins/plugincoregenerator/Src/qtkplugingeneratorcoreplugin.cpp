#include "qtkplugingeneratorcoreplugin_p.h"
#include "qtkplugingeneratorcodemodel.h"

#include <QtPlugin>

QTKPluginGeneratorCorePlugin* QTKPluginGeneratorCorePlugin::instance = 0;

void QTKPluginGeneratorCorePlugin::start(QTKPluginContext* context)
{
    pluginContext = context;
    instance = this;

    codeModel = new QTKPluginGeneratorCodeModel();
    context->registerService(QStringList("QTKPluginGeneratorCodeModel"), codeModel);
}

void QTKPluginGeneratorCorePlugin::stop(QTKPluginContext* context)
{
    Q_UNUSED(context);

    delete codeModel;
    instance = 0;
}

QTKPluginContext* QTKPluginGeneratorCorePlugin::getContext() const
{
    return pluginContext;
}

QTKPluginGeneratorCodeModel* QTKPluginGeneratorCorePlugin::getCodeModel() const
{
    return codeModel;
}

QTKPluginGeneratorCorePlugin* QTKPluginGeneratorCorePlugin::getInstance()
{
    return instance;
}
