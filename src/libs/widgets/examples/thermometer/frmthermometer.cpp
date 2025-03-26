#include "frmthermometer.h"
#include "ui_frmthermometer.h"
#include "qextThermometer.h"
#include "qdatetime.h"
#include "qtimer.h"



frmThermometer::frmThermometer(QWidget *parent) : QWidget(parent), ui(new Ui::frmThermometer)
{
    ui->setupUi(this);
    this->initForm();
}

frmThermometer::~frmThermometer()
{
    delete ui;
}

void frmThermometer::initForm()
{
    ui->thermometer1->setTickPosition(QExtThermometer::TickPosition_Left);
    ui->thermometer1->setBarPosition(QExtThermometer::BarPosition_Right);
    ui->thermometer2->setTickPosition(QExtThermometer::TickPosition_Left);
    ui->thermometer4->setTickPosition(QExtThermometer::TickPosition_Right);
    ui->thermometer5->setTickPosition(QExtThermometer::TickPosition_Right);
    ui->thermometer5->setBarPosition(QExtThermometer::BarPosition_Left);

    ui->thermometer3->setAnimationEnable(true);

    ui->thermometer2->setBarColor(QColor(24, 189, 155));
    ui->thermometer3->setBarColor(QColor(255, 107, 107));
    ui->thermometer4->setBarColor(QColor("#DEAF39"));
    ui->thermometer5->setBarColor(QColor("#A279C5"));

    ui->thermometer3->setAnimationEnable(true);

    //初始化随机数种子
    QTime t = QTime::currentTime();
    QEXT_RANDOM_INT_SEED(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    updateValue();
}

void frmThermometer::updateValue()
{
    ui->thermometer1->setValue(QEXT_RANDOM_INT() % 100);
    ui->thermometer2->setValue(QEXT_RANDOM_INT() % 100);
    ui->thermometer3->setValue(QEXT_RANDOM_INT() % 100);
    ui->thermometer4->setValue(QEXT_RANDOM_INT() % 100);
    ui->thermometer5->setValue(QEXT_RANDOM_INT() % 100);
}
