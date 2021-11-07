#pragma execution_character_set("utf-8")

#include "frmtooltip.h"
#include "ui_frmtooltip.h"

FrmTooltip::FrmTooltip(QWidget *parent) : QWidget(parent), ui(new Ui::FrmTooltip)
{
    ui->setupUi(this);
    this->initForm();
}

FrmTooltip::~FrmTooltip()
{
    delete ui;
}

void FrmTooltip::initForm()
{
    ui->navLabel11->setArrowPosition(QEXTTooltip::ArrowPosition_Left);
    ui->navLabel12->setArrowPosition(QEXTTooltip::ArrowPosition_Left);
    ui->navLabel13->setArrowPosition(QEXTTooltip::ArrowPosition_Left);

    ui->navLabel21->setArrowPosition(QEXTTooltip::ArrowPosition_Right);
    ui->navLabel22->setArrowPosition(QEXTTooltip::ArrowPosition_Right);
    ui->navLabel23->setArrowPosition(QEXTTooltip::ArrowPosition_Right);

    ui->navLabel31->setArrowPosition(QEXTTooltip::ArrowPosition_Top);
    ui->navLabel32->setArrowPosition(QEXTTooltip::ArrowPosition_Top);
    ui->navLabel33->setArrowPosition(QEXTTooltip::ArrowPosition_Top);

    ui->navLabel41->setArrowPosition(QEXTTooltip::ArrowPosition_Bottom);
    ui->navLabel42->setArrowPosition(QEXTTooltip::ArrowPosition_Bottom);
    ui->navLabel43->setArrowPosition(QEXTTooltip::ArrowPosition_Bottom);

    ui->navLabel12->setBackgroundColor(QColor(255, 107, 107));
    ui->navLabel13->setBackgroundColor(QColor(24, 189, 155));
    ui->navLabel21->setBackgroundColor(QColor(225, 102, 255));
    ui->navLabel22->setBackgroundColor(QColor(45, 62, 80));
    ui->navLabel23->setBackgroundColor(QColor(210, 84, 0));

    ui->navLabel32->setBackgroundColor(QColor(255, 107, 107));
    ui->navLabel33->setBackgroundColor(QColor(24, 189, 155));
    ui->navLabel41->setBackgroundColor(QColor(225, 102, 255));
    ui->navLabel42->setBackgroundColor(QColor(45, 62, 80));
    ui->navLabel43->setBackgroundColor(QColor(210, 84, 0));

    ui->navLabel51->setBorderRadius(0);
    ui->navLabel52->setBorderRadius(0);
    ui->navLabel53->setBorderRadius(0);
    ui->navLabel51->setBackgroundColor(QColor(80,80,80));
    ui->navLabel52->setBackgroundColor(QColor(80,80,80));
    ui->navLabel53->setBackgroundColor(QColor(80,80,80));
    ui->navLabel52->setTriangleVisiable(true);
    ui->navLabel53->setTriangleVisiable(true);
    ui->navLabel53->setArrowVisiable(false);

}
