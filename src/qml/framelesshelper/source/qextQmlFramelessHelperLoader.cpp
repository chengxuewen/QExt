#include <qextQmlFramelessHelperLoader.h>
#include <qextQmlFramelessHelperConfig.h>
#include <qextQmlFramelessHelper.h>

void QEXTQmlFramelessHelperLoader::load(QQmlEngine *engine)
{
    QEXTQmlFramelessHelperLoader::registerTypes(QEXT_QML_PLUGIN_NAME);
    QEXTQmlFramelessHelperLoader::initQmlEngine(engine, QEXT_QML_PLUGIN_NAME);
}

void QEXTQmlFramelessHelperLoader::registerTypes(const char *uri)
{
    Q_INIT_RESOURCE(QEXTQmlFramelessHelper);
    int major = QEXT_QML_PLUGIN_VERSION_MAJOR;
    int minor = QEXT_QML_PLUGIN_VERSION_MINOR;

    qmlRegisterType<QEXTQmlFramelessHelper>(uri, major, minor, "QEXTQmlFramelessHelper");
}

void QEXTQmlFramelessHelperLoader::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(engine)
    Q_UNUSED(uri)
}

QString QEXTQmlFramelessHelperLoader::version()
{
    return QString("%1.%2").arg(QEXT_QML_PLUGIN_VERSION_MAJOR).arg(QEXT_QML_PLUGIN_VERSION_MINOR);
}
