#include "frmprogressknob.h"
#include "ui_frmprogressknob.h"



FrmProgressKnob::FrmProgressKnob(QWidget *parent) : QWidget(parent), ui(new Ui::FrmProgressKnob)
{
    ui->setupUi(this);
    this->initForm();
}

FrmProgressKnob::~FrmProgressKnob()
{
    delete ui;
}

void FrmProgressKnob::initForm()
{
    ui->ckShowPointer->setChecked(true);
    gauges << ui->gaugeProgress1 << ui->gaugeProgress2 << ui->gaugeProgress3 << ui->gaugeProgress4 << ui->gaugeProgress5 << ui->gaugeProgress6;

    QList<QColor> colors;
    colors << "#47A4E9" << "#00B17D" << "#D64D54" << "#DEAF39" << "#A279C5" << "#009679";

    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setProgressColor(colors.at(i));
        connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), gauges.at(i), SLOT(setValue(int)));
    }

    ui->horizontalSlider->setValue(88);
}

void FrmProgressKnob::on_ckShowPointer_stateChanged(int arg1)
{
    bool check = (arg1 != 0);
    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setPointerVisiable(check);
    }
}

void FrmProgressKnob::on_ckShowValue_stateChanged(int arg1)
{
    bool check = (arg1 != 0);
    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setValueVisiable(check);
    }
}

void FrmProgressKnob::on_cboxPointerStyle_currentIndexChanged(int index)
{
    QEXTProgressKnob::PointerStyle style = (QEXTProgressKnob::PointerStyle)index;
    int count = gauges.count();
    for (int i = 0; i < count; i++) {
        gauges.at(i)->setPointerStyle(style);
    }
}
