#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumber2->setNumberStartColor(QColor(255, 107, 107));
    ui->lcdNumber2->setNumberEndColor(QColor(255, 0, 0));

    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);

    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    timer->start();
    this->updateValue();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateValue()
{
    ui->lcdNumber1->setNumber(qrand() % 10);
    ui->lcdNumber2->setNumber(qrand() % 10);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->lcdNumber1->setSymbolType(QEXTLcdNumber::Symbol(index));
    ui->lcdNumber2->setSymbolType(QEXTLcdNumber::Symbol(index));
}
