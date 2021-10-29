#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qextGuiGVRectangle.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scene.reset(new QGraphicsScene);
    ui->graphicsView->setScene(m_scene.data());
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QEXTGuiGVRectangle *rect = new QEXTGuiGVRectangle;
    rect->setColor(Qt::blue);
    rect->setSmooth(true);
    rect->setSize(QSize(100, 100));
    rect->setOpacity(0.5);
    rect->setRotation(30);
    rect->setPos(0, 0);
    m_scene->addItem(rect);
}

MainWindow::~MainWindow()
{
    delete ui;
}
