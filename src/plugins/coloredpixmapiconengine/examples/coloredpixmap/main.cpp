#include "MainWindow.h"

#include <QApplication>
#include <QDebug>
#include <QProcessEnvironment>

#include <QtPlugin>

Q_IMPORT_PLUGIN(QExtColoredPixmapIconEnginePlugin)


int main(int argc, char *argv[])
{
    qputenv("QT_COLORED_ICONS_FILES_PATTERN", "^colored.*");
    qputenv("QT_COLORED_ICONS_COLOR", "blue");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
