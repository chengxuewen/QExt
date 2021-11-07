#pragma execution_character_set("utf-8")

#include "frmarrowcompass.h"
#include "ui_frmarrowcompass.h"

FrmArrowCompass::FrmArrowCompass(QWidget *parent) : QWidget(parent), ui(new Ui::FrmArrowCompass)
{
    ui->setupUi(this);
    this->initForm();
}

FrmArrowCompass::~FrmArrowCompass()
{
    delete ui;
}

void FrmArrowCompass::initForm()
{    
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->gaugeCompass, SLOT(setValue(int)));
    ui->horizontalSlider->setValue(88);
}
