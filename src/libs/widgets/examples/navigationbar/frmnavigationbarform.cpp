#include "frmnavigationbarform.h"
#include "ui_frmnavigationbarform.h"
#include "qtimer.h"
#include "qdebug.h"



FrmNavigationBarForm::FrmNavigationBarForm(QWidget *parent) : QWidget(parent), ui(new Ui::FrmNavigationBarForm)
{
    ui->setupUi(this);
    this->initForm();
}

FrmNavigationBarForm::~FrmNavigationBarForm()
{
    delete ui;
}

void FrmNavigationBarForm::showEvent(QShowEvent *)
{
    QTimer::singleShot(100, this, SLOT(setIndex()));
}

void FrmNavigationBarForm::initForm()
{
    //设置圆角
    //ui->navBar->setBgRadius(5);
    //ui->navBar->setBarRadius(5);

    //设置间距,即元素高度
    ui->navBar->setSpace(18);
    ui->navBar->setBarStartColor(QColor(24, 189, 155));
    ui->navBar->setBarEndColor(QColor(24, 189, 155));
    ui->navBar->setItems("主界面;系统设置;防区管理;警情查询;视频预览");
    ui->navBar->setHorizontal(false);
    connect(ui->navBar, SIGNAL(currentItemChanged(int, QString)), this, SLOT(currentItemChanged(int, QString)));
}

void FrmNavigationBarForm::currentItemChanged(int index, const QString &item)
{
    ui->stackedWidget->setCurrentIndex(index);
    qDebug() << "index" << index << "item" << item;
}

void FrmNavigationBarForm::setIndex()
{
    ui->navBar->setCurrentIndex(2);
}
