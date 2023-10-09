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
    ui->sliderRange3->setTextVisible(true);
    ui->sliderRange4->setTextVisible(true);
    ui->sliderRange3->setSliderStyle(QExtRangeSlider::SliderStyle_Circle);
    ui->sliderRange4->setSliderStyle(QExtRangeSlider::SliderStyle_Circle);

    ui->sliderRange2->setUsedColor(QColor(255, 107, 107));
    ui->sliderRange4->setUsedColor(QColor(255, 107, 107));
}
