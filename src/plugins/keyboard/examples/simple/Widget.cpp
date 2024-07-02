#include "Widget.h"
#include "ui_Widget.h"
#include <qextKeyboardInputContext.h>

#include <QKeyEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
}

void Widget::on_pushButton_2_clicked()
{
    QExtKeyboardInputContext::instance()->showInputPanel();
}


void Widget::on_pushButton_3_clicked()
{
    QExtKeyboardInputContext::instance()->hideInputPanel();
}

