#include "frmsemicirclegauge.h"
#include "ui_frmsemicirclegauge.h"



FrmSemicircleGauge::FrmSemicircleGauge(QWidget *parent) : QWidget(parent), ui(new Ui::FrmSemicircleGauge)
{
    ui->setupUi(this);
    this->initForm();
}

FrmSemicircleGauge::~FrmSemicircleGauge()
{
    delete ui;
}

void FrmSemicircleGauge::initForm()
{    
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeSimple, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
