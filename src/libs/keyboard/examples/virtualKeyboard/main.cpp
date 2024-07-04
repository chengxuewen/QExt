#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

#include <qextVirtualKeyboard.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setFont(QFont("Microsoft YaHei", 10));
    //a.setFont(QFont("WenQuanYi Micro Hei", 10));

    //    QExtVirtualKeyboard::Instance()->setOnlyControl(true);
    QExtVirtualKeyboard::instance()->setFontInfo("MicroSoft Yahei", 16, 12);
    //    QExtVirtualKeyboard::Instance()->setFixedSize(QApplication::desktop()->width(), 400);
    QExtVirtualKeyboard::instance()->setFixedSize(800, 400);
    QExtVirtualKeyboard::instance()->setIconSize(26, 26);
    QExtVirtualKeyboard::instance()->setTopHeight(60);
    QExtVirtualKeyboard::instance()->setPopUpType(QExtVirtualKeyboard::PopUp_Control);
    QExtVirtualKeyboard::instance()->setStyleType(QExtVirtualKeyboard::Style_Black);

    MainWindow w;
    w.show();

    return a.exec();
}
