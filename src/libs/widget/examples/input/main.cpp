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

//    QEXTInput::Instance()->setOnlyControl(true);
    QEXTInput::Instance()->setFontInfo("MicroSoft Yahei", 16, 12);
//    QEXTInput::Instance()->setFixedSize(QApplication::desktop()->width(), 400);
    QEXTInput::Instance()->setFixedSize(800, 400);
    QEXTInput::Instance()->setIconSize(26, 26);
    QEXTInput::Instance()->setTopHeight(60);
    QEXTInput::Instance()->setPopUpType(QEXTInput::PopUp_Control);
    QEXTInput::Instance()->setStyleType(QEXTInput::Style_Black);

    MainWindow w;
    w.show();

    return a.exec();
}
