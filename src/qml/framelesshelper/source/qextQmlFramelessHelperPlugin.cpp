#include <qextQmlFramelessHelperPlugin.h>
#include <qextQmlFramelessHelperLoader.h>

#include <QObject>
#include <QQmlEngine>
#include <QFontDatabase>

void QEXTQmlFramelessHelperPlugin::registerTypes(const char *uri)
{
    QEXTQmlFramelessHelperLoader::registerTypes(uri);
}

void QEXTQmlFramelessHelperPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QEXTQmlFramelessHelperLoader::initQmlEngine(engine, uri);
}
