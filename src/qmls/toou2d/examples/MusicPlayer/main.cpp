#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <time.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    clock_t start,finish;
    double totaltime;
    start=clock();

    qputenv("QSG_RENDER_LOOP","basic");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qDebug() << "addImportPath:" << QML_MODULES_DIR;
    engine.addImportPath(QML_MODULES_DIR);
    engine.addImportPath(QT_QML_MODULES_PATH);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    qDebug() << "Startup time :" << totaltime << "s";

    return app.exec();
}
