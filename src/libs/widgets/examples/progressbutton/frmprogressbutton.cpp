#include "frmprogressbutton.h"
#include "ui_frmprogressbutton.h"



frmProgressButton::frmProgressButton(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressButton)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressButton::~frmProgressButton()
{
    delete ui;
}

void frmProgressButton::initForm()
{
    ui->progressButton2->setBackgroundColor(QColor(40, 45, 48));
    ui->progressButton3->setBackgroundColor(QColor(214, 77, 84));
    ui->progressButton4->setBackgroundColor(QColor(162, 121, 197));
    ui->progressButton5->setBackgroundColor(QColor(0, 150, 121));
    ui->progressButton6->setBackgroundColor(QColor(71, 164, 233));
}
