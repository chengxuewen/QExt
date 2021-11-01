#include "qtkplugingeneratoruiplugin_p.h"
#include "qtkplugingeneratormainextension.h"

#include <QTKPluginFramework/QTKPluginConstants>

#include <QtPlugin>
#include <QDebug>

void QTKPluginGeneratorUiPlugin::start(QTKPluginContext* context)
{
    mainExtension = new QTKPluginGeneratorMainExtension();

    QTKDictionary props;
    props.insert(QTKPluginConstants::SERVICE_RANKING, 0);
    context->registerService(QStringList("QTKPluginGeneratorAbstractUiExtension"),
                             mainExtension, props);

    qDebug() << "Registered Main Extension";
}

void QTKPluginGeneratorUiPlugin::stop(QTKPluginContext* context)
{
    Q_UNUSED(context)

    delete mainExtension;
}
