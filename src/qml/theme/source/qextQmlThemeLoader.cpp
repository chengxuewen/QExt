#include <qextQmlThemeLoader.h>
#include <qextQmlThemeConfig.h>
#include <qextQmlThemeBinder.h>
#include <qextQmlThemeHandler.h>
#include <qextQmlThemeManager.h>

void QEXTQmlThemeLoader::load(QQmlEngine *engine)
{
    QEXTQmlThemeLoader::registerTypes(QEXT_QML_PLUGIN_NAME);
    QEXTQmlThemeLoader::initQmlEngine(engine, QEXT_QML_PLUGIN_NAME);
}

void QEXTQmlThemeLoader::registerTypes(const char *uri)
{
    Q_INIT_RESOURCE(QEXTQmlTheme);
    int major = QEXT_QML_PLUGIN_VERSION_MAJOR;
    int minor = QEXT_QML_PLUGIN_VERSION_MINOR;

    qmlRegisterType<QEXTQmlThemeBinder>(uri, major, minor, "QEXTQmlThemeBinder");
    qmlRegisterSingletonType<QEXTQmlThemeManager>(uri, major, minor, "QEXTQmlThemeManager", QEXTQmlThemeManager::qmlSingletonTypeProvider);
}

void QEXTQmlThemeLoader::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(engine)
    Q_UNUSED(uri)
}

QString QEXTQmlThemeLoader::version()
{
    return QString("%1.%2").arg(QEXT_QML_PLUGIN_VERSION_MAJOR).arg(QEXT_QML_PLUGIN_VERSION_MINOR);
}
