#include "frmnavigationbar.h"
#include "ui_frmnavigationbar.h"

#include <qextNavigationBar.h>

#include "qtimer.h"
#include "qdebug.h"



FrmNavigationBar::FrmNavigationBar(QWidget *parent) : QWidget(parent), ui(new Ui::FrmNavigationBar)
{
    ui->setupUi(this);
    this->initForm();    
}

FrmNavigationBar::~FrmNavigationBar()
{
    delete ui;
}

void FrmNavigationBar::showEvent(QShowEvent *)
{
    QTimer::singleShot(100, this, SLOT(setIndex()));
}

void FrmNavigationBar::initForm()
{
    QString item = "系统设置;教师管理;学生管理;数据查询;关于";

    ui->navBar1->setBackgroundRadius(5);
    ui->navBar2->setBackgroundRadius(5);

    ui->navBar1->setBarRadius(5);
    ui->navBar2->setBarRadius(5);

    ui->navBar2->setBarStartColor(QColor(24, 189, 155));
    ui->navBar2->setBarEndColor(QColor(26, 188, 156));

    ui->navBar4->setBarStartColor(QColor(24, 189, 155));
    ui->navBar4->setBarEndColor(QColor(26, 188, 156));

    ui->navBar3->setLineWidth(3);
    ui->navBar3->setBarStyle(QExtNavigationBar::BarStyle_Line_Top);

    ui->navBar4->setLineWidth(3);
    ui->navBar4->setBarStyle(QExtNavigationBar::BarStyle_Line_Top);

    ui->navBar5->setLineWidth(4);
    ui->navBar5->setLineColor(QColor(24, 189, 155));
    ui->navBar5->setBarStyle(QExtNavigationBar::BarStyle_Line_Bottom);

    ui->navBar6->setLineWidth(4);
    ui->navBar6->setLineColor(QColor(24, 189, 155));
    ui->navBar6->setBackgroundStartColor(Qt::transparent);
    ui->navBar6->setBackgroundEndColor(Qt::transparent);
    ui->navBar6->setBarStartColor(Qt::transparent);
    ui->navBar6->setBarEndColor(Qt::transparent);
    ui->navBar6->setTextNormalColor(QColor(50, 50, 50));
    ui->navBar6->setTextSelectColor(QColor(255, 107, 107));
    ui->navBar6->setBarStyle(QExtNavigationBar::BarStyle_Line_Bottom);

    ui->navBar1->setItems(item);
    ui->navBar2->setItems(item);
    ui->navBar3->setItems(item);
    ui->navBar4->setItems(item);
    ui->navBar5->setItems(item);
    ui->navBar6->setItems(item);
    ui->navBarLeft->setItems(item);

    ui->navBarLeft->setSpace(15);
    ui->navBarLeft->setKeyMoveEnable(true);
    ui->navBarLeft->setHorizontal(false);
    ui->navBarLeft->setBarStyle(QExtNavigationBar::BarStyle_Line_Left);

    ui->navBarLeft->setBackgroundStartColor(QColor(13, 138, 166));
    ui->navBarLeft->setBackgroundEndColor(QColor(13, 138, 166));

    ui->navBarLeft->setBackgroundStartColor(QColor(9, 52, 69));
    ui->navBarLeft->setBackgroundEndColor(QColor(9, 52, 69));

    ui->navBarLeft->setTextNormalColor(QColor(73, 138, 174));
    ui->navBarLeft->setTextSelectColor(QColor(223, 252, 253));

    ui->navBarLeft->setLineColor(QColor(223, 252, 253));
}

void FrmNavigationBar::setIndex()
{
    ui->navBar1->setCurrentIndex(3);
    ui->navBar2->setCurrentIndex(0);
    ui->navBar3->setCurrentIndex(1);
    ui->navBar4->setCurrentIndex(4);
    ui->navBar5->setCurrentIndex(2);
    ui->navBar6->setCurrentIndex(0);
    ui->navBarLeft->setCurrentIndex(1);
}
