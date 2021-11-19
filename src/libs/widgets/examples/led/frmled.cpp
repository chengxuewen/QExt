#include "frmled.h"
#include "ui_frmled.h"

#include <qextDial.h>



FrmLED::FrmLED(QWidget *parent) : QWidget(parent), ui(new Ui::FrmLED)
{
    ui->setupUi(this);
    this->initForm();
}

FrmLED::~FrmLED()
{
    delete ui;
}

void FrmLED::initForm()
{
    ui->led->setColor(Qt::red);
    ui->led_2->setColor(Qt::blue);
    ui->led_3->setColor(Qt::cyan);
    ui->led_4->setColor(Qt::yellow);
    ui->led_5->setColor(Qt::gray);
    ui->led_6->setColor(Qt::green);
}
