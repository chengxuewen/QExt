#pragma execution_character_set("utf-8")

#include "frmselectslider.h"
#include "ui_frmselectslider.h"
#include "qextSelectSlider.h"

frmSelectSlider::frmSelectSlider(QWidget *parent) : QWidget(parent), ui(new Ui::frmSelectSlider)
{
    ui->setupUi(this);
    this->initForm();
}

frmSelectSlider::~frmSelectSlider()
{
    delete ui;
}

void frmSelectSlider::initForm()
{
    ui->sliderSelect2->setUsedColor(QColor("#FF6B6B"));
    ui->sliderSelect3->setUsedColor(QColor("#3498DB"));

    sliders << ui->sliderSelect1 << ui->sliderSelect2 << ui->sliderSelect3;

    foreach (QEXTSelectSlider *slider, sliders) {
        connect(ui->sliderLeftValue, SIGNAL(valueChanged(int)), slider, SLOT(setLeftValue(int)));
        connect(ui->sliderRightValue, SIGNAL(valueChanged(int)), slider, SLOT(setRightValue(int)));
        connect(ui->sliderRangeValue, SIGNAL(valueChanged(int)), slider, SLOT(setRangeValue(int)));
        connect(slider, SIGNAL(valueChanged(int, int)), this, SLOT(valueChanged(int, int)));
        connect(slider, SIGNAL(rangeChanged(int)), this, SLOT(rangeChanged(int)));
    }

    ui->sliderLeftValue->setValue(-20);
    ui->sliderRightValue->setValue(20);
    ui->sliderRangeValue->setValue(40);
}

void frmSelectSlider::valueChanged(int leftValue, int rightValue)
{
    ui->labValueLeft->setText(QString::number(leftValue));
    ui->labValueRight->setText(QString::number(rightValue));
}

void frmSelectSlider::rangeChanged(int rangeValue)
{
    ui->labValueRange->setText(QString::number(rangeValue));
}
