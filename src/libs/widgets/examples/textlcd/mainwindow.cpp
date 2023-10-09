#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ledText1->setText("~!@#$%^&*()-+");
    ui->ledText1->setAnimationType(QExtTextLcd::Animation_Static);
    ui->ledText1->setHighLightBorderEnable(true);

    ui->ledText2->setText("123456789");
    ui->ledText2->setAnimationType(QExtTextLcd::Animation_LeftToRight);
    ui->ledText2->setTextColor(QColor(255, 107, 107));

    ui->ledText3->setText("ABCDEFG");
    ui->ledText3->setAnimationType(QExtTextLcd::Animation_RightToLeft);
    ui->ledText3->setTextColor(QColor(0, 255, 255));

    QString strText;
    strText.append("<<山行>> 杜牧\n");
    strText.append("远上寒山石径斜\n");
    strText.append("白云生处有人家\n");
    strText.append("停车坐爱枫林晚\n");
    strText.append("霜叶红于二月花\n");
    ui->ledText4->setRowCount(64);
    ui->ledText4->setFontPixelSize(24);
    ui->ledText4->setAnimationType(QExtTextLcd::Animation_TopToBottom);
    ui->ledText4->setText(strText);

    ui->ledText5->setText("ABCDEFG");
    ui->ledText5->setAnimationType(QExtTextLcd::Animation_TopToBottom);
    ui->ledText5->setTextColor(QColor(255, 107, 107));
    ui->ledText5->setHighLightBorderEnable(true);
    ui->ledText5->setAnimationInterval(200);

    ui->ledText6->setText("ABCDEFG");
    ui->ledText6->setAnimationType(QExtTextLcd::Animation_BottomToTop);
    ui->ledText6->setTextColor(QColor(0, 255, 255));
}

MainWindow::~MainWindow()
{
    delete ui;
}
