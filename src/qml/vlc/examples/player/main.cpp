#include <QApplication>
#include <QQmlApplicationEngine>

#ifndef QEXT_BUILD_SHARED_LIBS
#include <qextQmlVLCLoader.h>
#include <QtPlugin>
Q_IMPORT_PLUGIN(QEXTQmlVLC)
#else
#include <qextQmlVLCExampleConfig.h>
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

#ifndef QEXT_BUILD_SHARED_LIBS
    QEXTQmlVLCLoader::load(&engine);
#else
    engine.addImportPath(QEXT_OUTPUT_QML_DIR);
#endif

    engine.load(QUrl(QStringLiteral("qrc:/video.qml")));

    return app.exec();
}
