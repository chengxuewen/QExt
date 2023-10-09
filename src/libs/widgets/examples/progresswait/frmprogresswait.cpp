#include "frmprogresswait.h"
#include "ui_frmprogresswait.h"



frmProgressWait::frmProgressWait(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressWait)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressWait::~frmProgressWait()
{
    delete ui;
}

void frmProgressWait::initForm()
{
    ui->progressWait1->setShowPercent(true);
    ui->progressWait2->setShowPercent(true);
    ui->progressWait3->setShowPercent(false);
    ui->progressWait4->setShowPercent(true);
    ui->progressWait5->setShowPercent(true);
    ui->progressWait6->setShowPercent(true);
    ui->progressWait7->setShowPercent(false);
    ui->progressWait8->setShowPercent(false);

    ui->progressWait1->setBarStyle(QExtProgressWait::Style_Line);

    ui->progressWait2->setForegroundColor(QColor(225, 102, 255));
    ui->progressWait2->setTextColor(QColor(225, 102, 255));
    ui->progressWait2->setBarStyle(QExtProgressWait::Style_Dot);

    ui->progressWait3->setForegroundColor(QColor(24, 189, 155));
//    ui->progressWait3->setBarStyle(QExtProgressWait::BarStyle_Arc);

    ui->progressWait4->setForegroundColor(QColor(255, 107, 107));
    ui->progressWait4->setTextColor(QColor(30, 30, 30));
//    ui->progressWait4->setBarStyle(QExtProgressWait::BarStyle_Pie);

    ui->progressWait5->setClockWise(false);
    ui->progressWait5->setForegroundColor(QColor(255, 107, 107));
    ui->progressWait5->setTextColor(QColor(255, 107, 107));
    ui->progressWait5->setBarStyle(QExtProgressWait::Style_Line);

    ui->progressWait6->setForegroundColor(QColor(24, 189, 155));
    ui->progressWait6->setTextColor(QColor(24, 189, 155));
//    ui->progressWait6->setBarStyle(QExtProgressWait::BarStyle_Ring);

//    ui->progressWait7->setBarStyle(QExtProgressWait::BarStyle_SingleCircle);

//    ui->progressWait8->setBarStyle(QExtProgressWait::BarStyle_DoubleCircle);
}
