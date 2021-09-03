#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QColorDialog>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButtonSelectColor_clicked()
{
    const QColor color(QString::fromLocal8Bit(qgetenv("QT_COLORED_ICONS_COLOR")));
    const QColor selectedColor = QColorDialog::getColor(color, this);
    if (selectedColor.isValid()) {
        qputenv("QT_COLORED_ICONS_COLOR", selectedColor.name().toLocal8Bit());
        update();
    }
}

void MainWindow::on_label_3_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(link);
}
