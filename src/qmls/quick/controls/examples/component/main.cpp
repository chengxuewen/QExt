#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QElapsedTimer>
#include <QDebug>

#include <qextCoreConfig.h>
#include <qextQmlConfig.h>
#include <qextObject.h>

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
    qDebug() << "QML_MODULES_DIR:" << QML_MODULES_DIR;
    engine.addImportPath(QML_MODULES_DIR);
#endif

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    QExtObject obj(&engine);
    obj.setParent(&app);

    qDebug() << "Startup time:" << timer.elapsed() << "ms";
    return app.exec();
}
