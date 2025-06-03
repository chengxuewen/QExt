#include <QQmlApplicationEngine>
#include <QElapsedTimer>
#include <QApplication>
#include <QDebug>

#include <qextCoreConfig.h>
#include <qextQmlConfig.h>

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
    engine.addImportPath(QEXT_QT_QML_MODULE_PATH);
#endif

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    qDebug() << "Startup time:" << timer.elapsed() << "ms";

    return app.exec();
}
