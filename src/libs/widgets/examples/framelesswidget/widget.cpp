#include "widget.h"
#include "ui_widget.h"
//#include "head.h"

Widget::Widget(QWidget *parent) : QExtFramelessWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->initForm();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initForm()
{
    //设置标题栏控件
    ui->labTitle->setText("无边框窗体示例-支持win、linux、mac等系统");
    this->setWindowTitle(ui->labTitle->text());
    this->setTitleBar(ui->labTitle);
    this->setMoveEnable(true);

    //关联信号
    connect(this, SIGNAL(titleDoubleClicked()), this, SLOT(onTitleDoubleClicked()));
    connect(this, SIGNAL(windowStateChanged(bool)), this, SLOT(onWindowStateChanged(bool)));

    //设置样式表
    QStringList list;
    list << "#titleBar{background:#BBBBBB;}";
    list << "#titleBar{border-top-left-radius:8px;border-top-right-radius:8px;}";
    list << "#widgetMain{border:2px solid #BBBBBB;background:#FFFFFF;}";
    //list << "#widgetMain{border-bottom-left-radius:8px;border-bottom-right-radius:8px;}";
    this->setStyleSheet(list.join(""));
}

void Widget::onTitleDoubleClicked()
{
    on_btnMenu_Max_clicked();
}

void Widget::onWindowStateChanged(bool max)
{
    ui->btnMenu_Max->setText(max ? "还原" : "最大");
}

void Widget::on_btnMenu_Min_clicked()
{
#ifdef Q_OS_MACOS
    this->setWindowFlags(this->windowFlags() & ~Qt::FramelessWindowHint);
#endif
    this->showMinimized();
}

void Widget::on_btnMenu_Max_clicked()
{
    if (this->isMaximized()) {
        this->showNormal();
        ui->btnMenu_Max->setText("最大");
    } else {
        this->showMaximized();
        ui->btnMenu_Max->setText("还原");
    }
}

void Widget::on_btnMenu_Close_clicked()
{
    this->close();
}
