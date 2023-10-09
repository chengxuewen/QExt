#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

#include <qextInput.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setFont(QFont("Microsoft YaHei", 10));
    //a.setFont(QFont("WenQuanYi Micro Hei", 10));

//    QExtInput::Instance()->setOnlyControl(true);
    QExtInput::Instance()->setFontInfo("MicroSoft Yahei", 16, 12);
//    QExtInput::Instance()->setFixedSize(QApplication::desktop()->width(), 400);
    QExtInput::Instance()->setFixedSize(800, 400);
    QExtInput::Instance()->setIconSize(26, 26);
    QExtInput::Instance()->setTopHeight(60);
    QExtInput::Instance()->setPopUpType(QExtInput::PopUp_Control);
    QExtInput::Instance()->setStyleType(QExtInput::Style_Black);

    MainWindow w;
    w.show();

    return a.exec();
}
