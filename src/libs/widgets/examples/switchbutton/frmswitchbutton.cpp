#include "frmswitchbutton.h"
#include "ui_frmswitchbutton.h"
#include "qextSwitchButton.h"



#define color1 QColor(34, 163, 169)
#define color2 QColor(162, 121, 197)
#define color3 QColor(255, 107, 107)
#define color4 QColor(72, 103, 149)

frmSwitchButton::frmSwitchButton(QWidget *parent) : QWidget(parent), ui(new Ui::frmSwitchButton)
{
    ui->setupUi(this);
    this->initForm();
}

frmSwitchButton::~frmSwitchButton()
{
    delete ui;
}

void frmSwitchButton::initForm()
{
    this->initBtn1();
    this->initBtn2();
    this->initBtn3();
}

void frmSwitchButton::initBtn1()
{
    ui->switchButton11->setOnBackgroundColor(color1);
    ui->switchButton12->setOnBackgroundColor(color2);
    ui->switchButton13->setOnBackgroundColor(color3);
    ui->switchButton14->setOnBackgroundColor(color4);

    ui->switchButton11->setTextVisible(false);
    ui->switchButton12->setTextVisible(false);
    ui->switchButton13->setTextVisible(true);
    ui->switchButton14->setTextVisible(true);
    ui->switchButton12->setCircleVisible(true);
    ui->switchButton14->setAnimationEnable(true);
    ui->switchButton12->setChecked(true);
    ui->switchButton14->setChecked(true);

    ui->switchButton13->setOffText("停止");
    ui->switchButton13->setOnText("启动");
    ui->switchButton14->setOffText("禁用");
    ui->switchButton14->setOnText("启用");
}

void frmSwitchButton::initBtn2()
{
    ui->switchButton21->setStyleType(QExtSwitchButton::Style_Rect);
    ui->switchButton22->setStyleType(QExtSwitchButton::Style_Rect);
    ui->switchButton23->setStyleType(QExtSwitchButton::Style_Rect);
    ui->switchButton24->setStyleType(QExtSwitchButton::Style_Rect);

    ui->switchButton21->setOnBackgroundColor(color1);
    ui->switchButton22->setOnBackgroundColor(color2);
    ui->switchButton23->setOnBackgroundColor(color3);
    ui->switchButton24->setOnBackgroundColor(color4);

    ui->switchButton21->setTextVisible(false);
    ui->switchButton22->setTextVisible(false);
    ui->switchButton23->setTextVisible(true);
    ui->switchButton24->setTextVisible(true);
    ui->switchButton22->setCircleVisible(true);
    ui->switchButton24->setAnimationEnable(true);
    ui->switchButton22->setChecked(true);
    ui->switchButton24->setChecked(true);

    ui->switchButton23->setOffText("停止");
    ui->switchButton23->setOnText("启动");
    ui->switchButton24->setOffText("禁用");
    ui->switchButton24->setOnText("启用");
}

void frmSwitchButton::initBtn3()
{
    ui->switchButton31->setStyleType(QExtSwitchButton::Style_CircleOut);
    ui->switchButton32->setStyleType(QExtSwitchButton::Style_CircleOut);
    ui->switchButton33->setStyleType(QExtSwitchButton::Style_CircleOut);
    ui->switchButton34->setStyleType(QExtSwitchButton::Style_CircleOut);

    int space = 8;
    ui->switchButton31->setSpace(space);
    ui->switchButton32->setSpace(space);
    ui->switchButton33->setSpace(space);
    ui->switchButton34->setSpace(space);

    int radius = 8;
    ui->switchButton31->setRectRadius(radius);
    ui->switchButton32->setRectRadius(radius);
    ui->switchButton33->setRectRadius(radius);
    ui->switchButton34->setRectRadius(radius);

    ui->switchButton31->setOnBackgroundColor(color1);
    ui->switchButton32->setOnBackgroundColor(color2);
    ui->switchButton33->setOnBackgroundColor(color3);
    ui->switchButton34->setOnBackgroundColor(color4);

    ui->switchButton31->setOnSliderColor(color1);
    ui->switchButton32->setOnSliderColor(color2);
    ui->switchButton33->setOnSliderColor(color3);
    ui->switchButton34->setOnSliderColor(color4);

    ui->switchButton31->setTextVisible(false);
    ui->switchButton32->setTextVisible(false);
    ui->switchButton33->setTextVisible(true);
    ui->switchButton34->setTextVisible(true);
    ui->switchButton34->setAnimationEnable(true);
    ui->switchButton32->setChecked(true);
    ui->switchButton34->setChecked(true);
}
