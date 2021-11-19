#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QEXTFramelessMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initForm();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initForm()
{
    ui->labTitle->setText("无边框窗体示例-支持win、linux、mac等系统");
    this->setWindowTitle(ui->labTitle->text());
    this->setTitleBar(ui->labTitle);

    //关联信号
    connect(this, SIGNAL(titleDoubleClicked()), this, SLOT(onTitleDoubleClicked()));
    connect(this, SIGNAL(windowStateChanged(bool)), this, SLOT(onWindowStateChanged(bool)));

    return;
    //设置样式表
    QStringList list;
    list << "#titleBar{background:#BBBBBB;}";
    list << "#titleBar{border-top-left-radius:8px;border-top-right-radius:8px;}";
    list << "#widgetMain{border:2px solid #BBBBBB;background:#FFFFFF;}";
    //list << "#widgetMain{border-bottom-left-radius:8px;border-bottom-right-radius:8px;}";
    this->setStyleSheet(list.join(""));
}

void MainWindow::onTitleDoubleClicked()
{
    on_btnMenu_Max_clicked();
}

void MainWindow::onWindowStateChanged(bool max)
{
    ui->btnMenu_Max->setText(max ? "还原" : "最大");
}

void MainWindow::on_btnMenu_Min_clicked()
{
#ifdef Q_OS_MACOS
    this->setWindowFlags(this->windowFlags() & ~Qt::FramelessWindowHint);
#endif
    this->showMinimized();
}

void MainWindow::on_btnMenu_Max_clicked()
{
    if (this->isMaximized()) {
        this->showNormal();
        ui->btnMenu_Max->setText("最大");
    } else {
        this->showMaximized();
        ui->btnMenu_Max->setText("还原");
    }
}

void MainWindow::on_btnMenu_Close_clicked()
{
    this->close();
}
