#include "frmslider.h"
#include "ui_frmslider.h"



FrmSlider::FrmSlider(QWidget *parent) : QWidget(parent), ui(new Ui::FrmSlider)
{
    ui->setupUi(this);
    this->initForm();
}

FrmSlider::~FrmSlider()
{
    delete ui;
}

void FrmSlider::initForm()
{
//    FlatUI::Instance()->setSliderQss(ui->horizontalSlider1, 8, "#505050", "#1ABC9C", "#1ABC9C");
//    FlatUI::Instance()->setSliderQss(ui->horizontalSlider2, 8, "#505050", "#C0392B", "#C0392B");
//    FlatUI::Instance()->setSliderQss(ui->horizontalSlider3, 16, "#505050", "#2C3E50", "#2C3E50");
//    FlatUI::Instance()->setSliderQss(ui->horizontalSlider4, 16, "#505050", "#8E44AD", "#8E44AD");
//    FlatUI::Instance()->setSliderQss(ui->verticalSlider1, 8, "#505050", "#1ABC9C", "#1ABC9C");
//    FlatUI::Instance()->setSliderQss(ui->verticalSlider2, 8, "#505050", "#8E44AD", "#8E44AD");

    ui->horizontalSlider1->setBackgroundColor("#1ABC9C");
    ui->horizontalSlider2->setBackgroundColor("#C0392B");
    ui->horizontalSlider3->setBackgroundColor("#2C3E50");
    ui->horizontalSlider4->setBackgroundColor("#8E44AD");
    ui->verticalSlider1->setBackgroundColor("#1ABC9C");
    ui->verticalSlider2->setBackgroundColor("#1ABC9C");

    ui->horizontalSlider1->setArrowStyle(QExtSlider::ArrowStyle_Bottom);
    ui->horizontalSlider2->setArrowStyle(QExtSlider::ArrowStyle_Top);
    ui->horizontalSlider3->setArrowStyle(QExtSlider::ArrowStyle_Bottom);
    ui->horizontalSlider4->setArrowStyle(QExtSlider::ArrowStyle_Top);
    ui->verticalSlider1->setArrowStyle(QExtSlider::ArrowStyle_Right);
    ui->verticalSlider2->setArrowStyle(QExtSlider::ArrowStyle_Left);

    QFont font;
    font.setPixelSize(20);
    ui->horizontalSlider3->setToolTipFont(font);
    ui->horizontalSlider4->setToolTipFont(font);
    ui->horizontalSlider3->setUnitText("毫秒");
    ui->horizontalSlider4->setUnitText(" cm");

    ui->horizontalSlider3->setFixedHeight(30);
    ui->horizontalSlider4->setFixedHeight(30);
    ui->horizontalSlider3->setToolTipWidth(100);
    ui->horizontalSlider4->setToolTipWidth(100);
    ui->horizontalSlider3->setToolTipHeight(45);
    ui->horizontalSlider4->setToolTipHeight(45);
    ui->verticalSlider1->setToolTipWidth(40);
    ui->verticalSlider2->setToolTipWidth(40);

    ui->horizontalSlider1->setValue(20);
    ui->horizontalSlider2->setValue(50);
    ui->horizontalSlider3->setValue(40);
    ui->horizontalSlider4->setValue(70);
    ui->verticalSlider1->setValue(20);
    ui->verticalSlider2->setValue(50);

    ui->horizontalSlider3->setRange(0, 150);
}
