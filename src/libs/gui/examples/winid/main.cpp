#include <QApplication>
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#   include <QTextCodec>
#endif

#include <qextGlobal.h>
#include <qextWindowUtils.h>
#include "widcontainerwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#   if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#       if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#       else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#       endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#   else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#   endif
#endif

    widcontainerWindow w;
    w.show();
    while (!w.isVisible()) { }
    w.load();

    return a.exec();
}
