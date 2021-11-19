#include "frmprogressbar.h"
#include "ui_frmprogressbar.h"



frmProgressBar::frmProgressBar(QWidget *parent) : QWidget(parent), ui(new Ui::frmProgressBar)
{
    ui->setupUi(this);
    this->initForm();
}

frmProgressBar::~frmProgressBar()
{
    delete ui;
}

void frmProgressBar::initForm()
{
    ui->progressColor1->setTextColor(QColor(250, 250, 250));
    ui->progressColor1->setBarBgColor(QColor(30, 30, 30));

    ui->progressColor2->setBarColor(QColor(255, 107, 107));
    ui->progressColor2->setPrecision(1);
    ui->progressColor2->setStep(5);

    ui->progressColor3->setTextColor(QColor(250, 250, 250));
    ui->progressColor3->setBarBgColor(QColor(80, 80, 80));
    ui->progressColor3->setBarColor(QColor(24, 189, 155));
    ui->progressColor3->setStep(7);

    connect(ui->horizontalSlider1, SIGNAL(valueChanged(int)), ui->progressColor1, SLOT(setValue(int)));
    connect(ui->horizontalSlider2, SIGNAL(valueChanged(int)), ui->progressColor2, SLOT(setValue(int)));
    connect(ui->horizontalSlider3, SIGNAL(valueChanged(int)), ui->progressColor3, SLOT(setValue(int)));

    ui->progressColor1->setRange(0, 100);
    ui->progressColor2->setRange(0, 200);
    ui->progressColor3->setRange(-100, 100);

    ui->horizontalSlider1->setRange(0, 100);
    ui->horizontalSlider2->setRange(0, 200);
    ui->horizontalSlider3->setRange(-100, 100);

    ui->horizontalSlider1->setValue(30);
    ui->horizontalSlider2->setValue(50);
    ui->horizontalSlider3->setValue(70);
}
