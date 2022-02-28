#include <QApplication>
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#include <QTextCodec>
#endif
#include <QFont>
#include <QDebug>

#include "mainwindow.h"

#include <qextStyleThemeDefault.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#elif (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    MainWindow w;
    w.setWindowTitle("StyleTheme gallery");
    w.show();

    QEXTStyleThemeDefault style;
    style.setCurrentTheme(QEXTStyleThemeDefault::Theme_PSBlack);
//    qApp->setStyleSheet(style.styleSheet());

    return a.exec();
}
