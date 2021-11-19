#include <qextQuickPlugin.h>
#include <qextQuick.h>

#include <QObject>
#include <QQmlEngine>
#include <QFontDatabase>

void QEXTQuickPlugin::registerTypes(const char *uri)
{
    QEXTQuick::instance()->registerTypes(uri);
}

void QEXTQuickPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
//    QFontDatabase::addApplicationFont(":/QEXTQuick/font/fontawesome-webfont.ttf");
    QEXTQuick::instance()->initQmlEngine(engine, uri);
}
