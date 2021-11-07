#include "frmringcompass.h"
#include "ui_frmringcompass.h"

FrmRingCompass::FrmRingCompass(QWidget *parent) : QWidget(parent), ui(new Ui::FrmRingCompass)
{
    ui->setupUi(this);
    ui->horizontalSlider->setValue(165);
}

FrmRingCompass::~FrmRingCompass()
{
    delete ui;
}

void FrmRingCompass::on_horizontalSlider_valueChanged(int value)
{
    ui->qextRingCompass->setValue(value);
}
