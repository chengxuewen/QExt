#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



LFAMMainWindow::LFAMMainWindow(QWidget *parent) : QMainWindow(parent),
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

LFAMMainWindow::~LFAMMainWindow()
{
    delete ui;
}

void LFAMMainWindow::updateCpu(const quint64 &ulPercent)
{
    qDebug() << "MainWindow::updateCpu():ulPercent=" << ulPercent;
}

void LFAMMainWindow::updateMemory(const quint64 &ulIdle, const quint64 &ulTotal, const quint64 &ulPercent)
{
    qDebug() << "MainWindow::updateMemory()----------------------";
    qDebug() << "ulIdle=" << ulIdle;
    qDebug() << "ulTotal=" << ulTotal;
    qDebug() << "ulPercent=" << ulPercent;
}

void LFAMMainWindow::updateDisk(const QList<QEXTDiskInfo> &listDiskInfo)
{
    qDebug() << "MainWindow::updateDisk()----------------------";
    foreach (QEXTDiskInfo info, listDiskInfo) {
        qDebug() << "info.strName=" << info.name();
        qDebug() << "info.strUsedSize=" << info.usedSize();
        qDebug() << "info.strFreeSize=" << info.freeSize();
        qDebug() << "info.strAllSize=" << info.allSize();
        qDebug() << "info.dUsedPercent=" << info.usedPercent();
    }
}
