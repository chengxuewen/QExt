#pragma execution_character_set("utf-8")

#include <navtreeviewform.h>
#include <ui_navtreeviewform.h>

#include <QDebug>

NavTreeViewForm::NavTreeViewForm(QWidget *parent) : QWidget(parent), ui(new Ui::NavTreeViewForm)
{
    ui->setupUi(this);
    this->initForm();
}

NavTreeViewForm::~NavTreeViewForm()
{
    delete ui;
}

void NavTreeViewForm::initForm()
{
    ui->navListWidget->setSeparateHeight(1);
    ui->navListWidget->setSeparateColor(QColor(40, 43, 51));

    ui->navListWidget->setChildBgNormalColor(QColor(40, 43, 51));
    ui->navListWidget->setChildBgSelectedColor(QColor(20, 20, 20));
    ui->navListWidget->setChildBgHoverColor(QColor(20, 20, 20));
    ui->navListWidget->setChildTextNormalColor(QColor(180, 180, 180));
    ui->navListWidget->setChildTextSelectedColor(QColor(250, 250, 250));
    ui->navListWidget->setChildTextHoverColor(QColor(255, 255, 255));

    ui->navListWidget->setParentBgNormalColor(QColor(57, 61, 73));
    ui->navListWidget->setParentBgSelectedColor(QColor(78, 83, 102));
    ui->navListWidget->setParentBgHoverColor(QColor(78, 83, 102));
    ui->navListWidget->setParentTextNormalColor(QColor(250, 250, 250));
    ui->navListWidget->setParentTextSelectedColor(QColor(250, 250, 250));
    ui->navListWidget->setParentTextHoverColor(QColor(250, 250, 250));

    ui->navListWidget->setExpendMode(QEXTNavTreeWidget::ExpendMode_SingleClick);

    //设置节点数据,格式 标题|父节点标题(父节点为空)|是否展开|提示信息|左侧图标
    QStringList items;
    items.append("主界面||0|正常|");
    items.append("地图监控|主界面|||0xf03e");
    items.append("视频监控|主界面|||0xf03d");
    items.append("设备监控|主界面|||0xf108");

    items.append("系统设置||0||");
    items.append("防区信息|系统设置|||0xf0e8");
    items.append("位置调整|系统设置|||0xf060");
    items.append("地图编辑|系统设置|||0xf03e");

    items.append("警情查询||0|120|");
    items.append("记录查询|警情查询|||0xf073");
    items.append("图像查询|警情查询|||0xf03e");
    items.append("视频查询|警情查询|||0xf03d");
    items.append("数据回放|警情查询|||0xf080");
    items.append("TEST|数据回放|||0xf080");
    items.append("MM|TEST|||0xf080");

    items.append("帮助文档||1|1024|");

    ui->navListWidget->setItems(items.join(","));
    ui->navListWidget->setCurrentItem("系统设置");
    on_navListView_pressed(ui->navListWidget->currentIndex());
}

void NavTreeViewForm::on_navListView_pressed(const QModelIndex &index)
{
    QString text = index.data().toString();
    if (text == "地图监控")
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (text == "视频监控")
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (text == "设备监控")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
}
