#include <qextQmlVLCLoader.h>
#include <qextQmlVLCConfig.h>

#include "qextVLC.h"
#include "qextVLCTrackModel.h"
#include "qextQmlVLCPlayer.h"
#include "qextQmlVLCSource.h"
#include "qextQmlVLCVideoOutput.h"

void QEXTQmlVLCLoader::load(QQmlEngine *engine)
{
    QEXTQmlVLCLoader::registerTypes(QEXT_QML_PLUGIN_NAME);
    QEXTQmlVLCLoader::initQmlEngine(engine, QEXT_QML_PLUGIN_NAME);
}

void QEXTQmlVLCLoader::registerTypes(const char *uri)
{
    Q_INIT_RESOURCE(QEXTQmlVLC);
    int major = QEXT_QML_PLUGIN_VERSION_MAJOR;
    int minor = QEXT_QML_PLUGIN_VERSION_MINOR;

    qmlRegisterUncreatableType<QEXTVLC>(uri, major, minor, "QEXTVLC", QStringLiteral("QEXTVLC cannot be instantiated directly"));
    qmlRegisterUncreatableType<QEXTQmlVLCSource>(uri, major, minor, "QEXTQmlVLCSource", QStringLiteral("QEXTQmlVLCSource cannot be instantiated directly"));
    qmlRegisterUncreatableType<QEXTVLCTrackModel>(uri, major, minor, "QEXTVLCTrackModel", QStringLiteral("QEXTVLCTrackModel cannot be instantiated directly"));

    qmlRegisterType<QEXTQmlVLCPlayer>(uri, major, minor, "QEXTQmlVLCPlayer");
    qmlRegisterType<QEXTQmlVLCVideoOutput>(uri, major, minor, "QEXTQmlVLCVideoOutput");
}

void QEXTQmlVLCLoader::initQmlEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(engine)
    Q_UNUSED(uri)
}

QString QEXTQmlVLCLoader::version()
{
    return QString("%1.%2").arg(QEXT_QML_PLUGIN_VERSION_MAJOR).arg(QEXT_QML_PLUGIN_VERSION_MINOR);
}
