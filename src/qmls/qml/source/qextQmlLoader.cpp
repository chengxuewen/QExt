#include <qextQmlLoader.h>
#include <qextQml.h>
#include <qextQmlConfig.h>

void QExtQmlLoader::load(QQmlEngine *engine)
{
    QExtQml::instance()->registerTypes(QEXT_QML_PLUGIN_NAME);
    QExtQml::instance()->initQmlEngine(engine, QEXT_QML_PLUGIN_NAME);
}

QString QExtQmlLoader::version()
{
    return QExtQml::instance()->version();
}
