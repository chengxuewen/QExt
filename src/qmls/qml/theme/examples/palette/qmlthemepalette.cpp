#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QDebug>
#include <QFile>

#include <qextQmlThemeManager.h>
#include "palettetablemodel.h"

int main(int argc, char *argv[])
{
    qDebug() << "QML_MODULES_DIR=" << QML_MODULES_DIR;
    QGuiApplication application(argc, argv);

    QExtQmlThemeManager::instance()->version();
    QQmlApplicationEngine engine;
    engine.addImportPath(QML_MODULES_DIR);
    qmlRegisterType<PaletteTableModel>("PaletteTableModel", 1, 0, "PaletteTableModel");
    engine.load(":/window.qml");

    return application.exec();
}
