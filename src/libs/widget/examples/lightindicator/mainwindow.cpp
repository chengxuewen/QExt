#pragma execution_character_set("utf-8")

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->qtklightbutton_1->setStyleType(QEXTLightIndicator::Style_Green);
    ui->qtklightbutton_2->setStyleType(QEXTLightIndicator::Style_Red);
    ui->qtklightbutton_3->setStyleType(QEXTLightIndicator::Style_Yellow);
    ui->qtklightbutton_4->setStyleType(QEXTLightIndicator::Style_Black);
    ui->qtklightbutton_5->setStyleType(QEXTLightIndicator::Style_Gray);
    ui->qtklightbutton_6->setStyleType(QEXTLightIndicator::Style_Blue);
    ui->qtklightbutton_7->setStyleType(QEXTLightIndicator::Style_LightBlue);
    ui->qtklightbutton_8->setStyleType(QEXTLightIndicator::Style_LightRed);
    ui->qtklightbutton_9->setStyleType(QEXTLightIndicator::Style_LightGreen);

    ui->qtklightbutton_1->setText("light");
    ui->qtklightbutton_2->setText("light");
    ui->qtklightbutton_3->setText("");
    ui->qtklightbutton_4->setText("Alarm");
    ui->qtklightbutton_4->setFontPixelSize(50);
    ui->qtklightbutton_5->setText("Output");
    ui->qtklightbutton_5->setFontPixelSize(50);
    ui->qtklightbutton_6->setText("light");
    ui->qtklightbutton_7->setText("light");

    ui->qtklightbutton_1->setShapeType(QEXTLightIndicator::Shape_Circle);
    ui->qtklightbutton_2->setShapeType(QEXTLightIndicator::Shape_Square);
    ui->qtklightbutton_3->setShapeType(QEXTLightIndicator::Shape_Triangle);
    ui->qtklightbutton_4->setShapeType(QEXTLightIndicator::Shape_Rounded);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_overlay_clicked(bool checked)
{
    ui->qtklightbutton_1->setOverlayVisiable(checked);
    ui->qtklightbutton_2->setOverlayVisiable(checked);
    ui->qtklightbutton_3->setOverlayVisiable(checked);
    ui->qtklightbutton_4->setOverlayVisiable(checked);
    ui->qtklightbutton_5->setOverlayVisiable(checked);
    ui->qtklightbutton_6->setOverlayVisiable(checked);
    ui->qtklightbutton_7->setOverlayVisiable(checked);
    ui->qtklightbutton_8->setOverlayVisiable(checked);
    ui->qtklightbutton_9->setOverlayVisiable(checked);
}

void MainWindow::on_checkBox_flicker_clicked(bool checked)
{
    ui->qtklightbutton_1->setFlickerState(checked);
    ui->qtklightbutton_2->setFlickerState(checked);
    ui->qtklightbutton_3->setFlickerState(checked);
    ui->qtklightbutton_4->setFlickerState(checked);
    ui->qtklightbutton_5->setFlickerState(checked);
    ui->qtklightbutton_6->setFlickerState(checked);
    ui->qtklightbutton_7->setFlickerState(checked);
    ui->qtklightbutton_8->setFlickerState(checked);
    ui->qtklightbutton_9->setFlickerState(checked);
}

void MainWindow::on_checkBox_light_clicked(bool checked)
{
    ui->qtklightbutton_1->setLightState(checked);
    ui->qtklightbutton_2->setLightState(checked);
    ui->qtklightbutton_3->setLightState(checked);
    ui->qtklightbutton_4->setLightState(checked);
    ui->qtklightbutton_5->setLightState(checked);
    ui->qtklightbutton_6->setLightState(checked);
    ui->qtklightbutton_7->setLightState(checked);
    ui->qtklightbutton_8->setLightState(checked);
    ui->qtklightbutton_9->setLightState(checked);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->qtklightbutton_1->setFlickerInterval(arg1);
    ui->qtklightbutton_2->setFlickerInterval(arg1);
    ui->qtklightbutton_3->setFlickerInterval(arg1);
    ui->qtklightbutton_4->setFlickerInterval(arg1);
    ui->qtklightbutton_5->setFlickerInterval(arg1);
    ui->qtklightbutton_6->setFlickerInterval(arg1);
    ui->qtklightbutton_7->setFlickerInterval(arg1);
    ui->qtklightbutton_8->setFlickerInterval(arg1);
    ui->qtklightbutton_9->setFlickerInterval(arg1);
}
