#include "mainwindow.h"

#include <QTextCodec>
#include <QApplication>
#include <QDesktopWidget>
#include <QGuiApplication>

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, false);
#   if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#   endif
#endif


    Q_INIT_RESOURCE(app);
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    MainWindow w;
    w.showNormal();
/*
    QSize size(QApplication::desktop()->availableGeometry().width(),
               QApplication::desktop()->availableGeometry().height());
    w.resize(size);
    w.move ((QApplication::desktop()->width() - w.width())/2,
            (QApplication::desktop()->height() - w.height())/2);
*/
    return a.exec();
}
