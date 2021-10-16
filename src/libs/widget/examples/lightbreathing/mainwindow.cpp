#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->setStyleSheet("QWidget#widget{background:url(:/bg1.jpg);}");
    listLightPoint << ui->qtklightpoint_1 << ui->qtklightpoint_2 << ui->qtklightpoint_3
                   << ui->qtklightpoint_4 << ui->qtklightpoint_5 << ui->qtklightpoint_6;

    QList<QColor> colors;
    colors << "#47A4E9" << "#00B17D" << "#D64D54" << "#DEAF39" << "#A279C5" << "#009679";

    int count = listLightPoint.count();
    for (int i = 0; i < count; i++) {
        listLightPoint.at(i)->setBackgroundColor(colors.at(i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
