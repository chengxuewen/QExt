#pragma execution_character_set("utf-8")

#include "frmcirclegauge.h"
#include "ui_frmcirclegauge.h"
#include "qextCircleGauge.h"

FrmCircleGauge::FrmCircleGauge(QWidget *parent) : QWidget(parent), ui(new Ui::FrmCircleGauge)
{
    ui->setupUi(this);
    this->initForm();
}

FrmCircleGauge::~FrmCircleGauge()
{
    delete ui;
}

void FrmCircleGauge::initForm()
{
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeCar, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
    //ui->gaugeCar->setCircleWidth(30);
    ui->ckAnimation->setChecked(true);
}

void FrmCircleGauge::on_cboxPieStyle_currentIndexChanged(int index)
{
    ui->gaugeCar->setPieStyle((QEXTCircleGauge::PieStyleType)index);
}

void FrmCircleGauge::on_cboxPointerStyle_currentIndexChanged(int index)
{
    ui->gaugeCar->setPointerStyle((QEXTCircleGauge::PointerStyleType)index);
}

void FrmCircleGauge::on_ckAnimation_stateChanged(int arg1)
{
    ui->gaugeCar->setAnimation(arg1 != 0);
}
