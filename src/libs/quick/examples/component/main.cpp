#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QElapsedTimer>
#include <QDebug>

#include <qextglobal.h>
#ifndef QEXT_BUILD_SHARED_LIBS
# include <qextquickloader.h>
#else
# include <qextquickexampleconfig.h>
#endif

int main(int argc, char *argv[])
{
    QElapsedTimer timer;
    timer.start();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

#ifndef QEXT_BUILD_SHARED_LIBS
    QEXTQuickLoader::load(&engine);
#else
    engine.addImportPath(QEXT_QML_OUTPUT_DIR);
#endif

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    qDebug() << "Startup time:"
             << timer.elapsed() << "ms";

    return app.exec();
}
