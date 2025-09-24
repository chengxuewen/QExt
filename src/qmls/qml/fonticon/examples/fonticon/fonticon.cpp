#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QGuiApplication application(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath(QML_MODULES_DIR);
    engine.load(":/window.qml");

    return application.exec();
}
