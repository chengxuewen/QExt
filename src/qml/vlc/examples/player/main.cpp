#include <QApplication>
#include <QQmlApplicationEngine>

#include <qextQmlVLCLoader.h>

#include <qextQmlVLCExampleConfig.h>

#ifndef QEXT_BUILD_SHARED_LIBS
#include <QtPlugin>
Q_IMPORT_PLUGIN(QEXTQmlVLC)
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath(QEXT_QML_OUTPUT_DIR);
    engine.load(QUrl(QStringLiteral("qrc:/video.qml")));

    return app.exec();
}
