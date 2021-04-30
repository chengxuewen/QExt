#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QEXTHostInfoUtils *info = new QEXTHostInfoUtils(this);
    info->startQueryCPU(1000);
    info->startQueryMemory(1000);
    info->startQueryDisk(1000);
    connect(info, SIGNAL(cpuChanged(quint64)), this, SLOT(updateCpu(quint64)));
    connect(info, SIGNAL(memoryChanged(quint64,quint64,quint64)), this, SLOT(updateMemory(quint64,quint64,quint64)));
    connect(info, SIGNAL(diskChanged(QList<QEXTDiskInfo>)), this, SLOT(updateDisk(QList<QEXTDiskInfo>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCpu(const quint64 &ulPercent)
{
    qDebug() << "MainWindow::updateCpu():ulPercent=" << ulPercent;
}

void MainWindow::updateMemory(const quint64 &ulIdle, const quint64 &ulTotal, const quint64 &ulPercent)
{
    qDebug() << "MainWindow::updateMemory()----------------------";
    qDebug() << "ulIdle=" << ulIdle;
    qDebug() << "ulTotal=" << ulTotal;
    qDebug() << "ulPercent=" << ulPercent;
}

void MainWindow::updateDisk(const QList<QEXTDiskInfoUtils> &listDiskInfo)
{
    qDebug() << "MainWindow::updateDisk()----------------------";
    foreach (QEXTDiskInfoUtils info, listDiskInfo) {
        qDebug() << "info.strName=" << info.getName();
        qDebug() << "info.strUsedSize=" << info.getUsedSize();
        qDebug() << "info.strFreeSize=" << info.getFreeSize();
        qDebug() << "info.strAllSize=" << info.getAllSize();
        qDebug() << "info.dUsedPercent=" << info.getUsedPercent();
    }
}
