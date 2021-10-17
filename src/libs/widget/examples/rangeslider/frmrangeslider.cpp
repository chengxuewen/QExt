#pragma execution_character_set("utf-8")

#include "frmrangeslider.h"
#include "ui_frmrangeslider.h"

frmRangeSlider::frmRangeSlider(QWidget *parent) : QWidget(parent), ui(new Ui::frmRangeSlider)
{
    ui->setupUi(this);
    this->initForm();
}

frmRangeSlider::~frmRangeSlider()
{
    delete ui;
}

void frmRangeSlider::initForm()
{
    ui->sliderRange3->setShowText(true);
    ui->sliderRange4->setShowText(true);
    ui->sliderRange3->setSliderStyle(QEXTRangeSlider::SliderStyle_Circle);
    ui->sliderRange4->setSliderStyle(QEXTRangeSlider::SliderStyle_Circle);

    ui->sliderRange2->setUsedColor(QColor(255, 107, 107));
    ui->sliderRange4->setUsedColor(QColor(255, 107, 107));
}
