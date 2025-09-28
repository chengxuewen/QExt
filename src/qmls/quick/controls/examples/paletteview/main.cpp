#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QElapsedTimer>

#include <qextQmlConfig.h>
#include <qextCoreConfig.h>
#include <qextquickpalettetablemodel.h>

#ifndef QEXT_BUILD_SHARED
#   include <qextQuickLoader.h>
#endif

int main(int argc, char *argv[])
{
    QElapsedTimer timer;
    timer.start();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

#ifndef QEXT_BUILD_SHARED
    QExtQuickLoader::load(&engine);
#else
    qDebug() << "addImportPath:" << QML_MODULES_DIR;
    engine.addImportPath(QML_MODULES_DIR);
#endif

    qmlRegisterType<QExtQuickPaletteTableModel>("QExtQuickPaletteView", 1, 0, "QExtQuickPaletteTableModel");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    qDebug() << "Startup time:" << timer.elapsed() << "ms";
    return app.exec();
}
