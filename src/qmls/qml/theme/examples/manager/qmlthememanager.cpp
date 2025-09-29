#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QDebug>
#include <QFile>

#include <qextQmlThemeManager.h>

int main(int argc, char *argv[])
{
    qDebug() << "QML_MODULES_DIR=" << QML_MODULES_DIR;
    QGuiApplication application(argc, argv);

    // QExtQmlThemeManager::instance()->addTheme(qApp->applicationDirPath() + "/Template.json");
    QExtQmlThemeManager::instance()->addThemeDir(qApp->applicationDirPath());
    QExtQmlThemeManager::instance()->setCurrentTheme("Template");
    QQmlApplicationEngine engine;
    engine.addImportPath(QML_MODULES_DIR);
    engine.load(":/window.qml");

    return application.exec();
}
