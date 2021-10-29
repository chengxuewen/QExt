
#pragma execution_character_set("utf-8")

#include "navlistwidgetform.h"
#include "ui_navlistwidgetform.h"
#include "qdebug.h"

#include <QListView>

#include <qextIconsFontAwesome.h>

NavListWidgetForm::NavListWidgetForm(QWidget *parent) : QWidget(parent), ui(new Ui::NavListWidgetForm)
{
    ui->setupUi(this);
    this->initForm();
}

NavListWidgetForm::~NavListWidgetForm()
{
    delete ui;
}

void NavListWidgetForm::initForm()
{
    ui->navListWidget->setItemSeparateHeight(1);
    ui->navListWidget->setItemSeparateColor(QColor(40, 43, 51));

    ui->navListWidget->setChildItemNormalBackgroundColor(QColor(40, 43, 51));
    ui->navListWidget->setChildItemBackgroundCheckedColor(QColor(20, 20, 20));
    ui->navListWidget->setChildItemHoverBackgroundColor(QColor(20, 20, 20));
    ui->navListWidget->setChildItemNormalTextColor(QColor(180, 180, 180));
    ui->navListWidget->setChildItemCheckedTextColor(QColor(250, 250, 250));
    ui->navListWidget->setChildItemHoverTextColor(QColor(255, 255, 255));

    ui->navListWidget->setParentItemNormalBackgroundColor(QColor(57, 61, 73));
    ui->navListWidget->setParentItemCheckedBackgroundColor(QColor(78, 83, 102));
    ui->navListWidget->setParentItemHoverBackgroundColor(QColor(78, 83, 102));
    ui->navListWidget->setParentItemNormalTextColor(QColor(250, 250, 250));
    ui->navListWidget->setParentItemCheckedTextColor(QColor(250, 250, 250));
    ui->navListWidget->setParentItemHoverTextColor(QColor(250, 250, 250));
    ui->navListWidget->setBackgroundColor(QColor(57, 61, 73));

    ui->navListWidget->setExpendMode(QEXTNavListWidget::ExpendMode_SingleClick);

    //设置节点数据,格式 标题|父节点标题(父节点为空)|是否展开|提示信息|左侧图标
    QStringList items;
    items.append("主界面||1|正常|");
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

    items.append("帮助文档||1|1024|");

    m_parentItems = ui->navListWidget->setItems(items.join(","));
    ui->navListWidget->setCurrentRow(1);
    connect(ui->navListWidget->view(), SIGNAL(pressed(QModelIndex)), this, SLOT(onNavListWidgetPressed(QModelIndex)));
    connect(ui->navListWidget, SIGNAL(itemPressed(QEXTNavListWidgetItem*)), this, SLOT(onItemPressed(QEXTNavListWidgetItem*)));
    this->onNavListWidgetPressed(ui->navListWidget->view()->currentIndex());
}

void NavListWidgetForm::onNavListWidgetPressed(const QModelIndex &index)
{
    QString text = index.data().toString();
    if (text == "地图监控") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (text == "视频监控") {
        ui->stackedWidget->setCurrentIndex(1);
    } else if (text == "设备监控") {
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void NavListWidgetForm::onItemPressed(QEXTNavListWidgetItem *item)
{
    if (item->isChildItem())
    {
        //        QString tip = item->tip();
        //        item->setTip(QString::number(tip.toInt() + 1));
        //        item->deleteLater();
        //        item->parentItem()->deleteLater();
        //        item->setParentItem(m_parentItems.last());

        //        QEXTIconsFontAwesome::FontOptionValueMap optionMap;
        //        optionMap.insert(QEXTIconsFontAwesome::Option_Color, ui->navListWidget->childItemTextNormalColor());
        //        optionMap.insert(QEXTIconsFontAwesome::Option_ColorActive, ui->navListWidget->childItemTextHoverColor());
        //        optionMap.insert(QEXTIconsFontAwesome::Option_ColorSelected, ui->navListWidget->childItemTextCheckedColor());
        //        optionMap.insert(QEXTIconsFontAwesome::Option_TextActive, qextIconsFontAwesome->fontChar(QEXTIconsFontAwesome::FA_address_book_o));
        //        item->setIcon(qextIconsFontAwesome->icon(QEXTIconsFontAwesome::FA_address_book, optionMap));
        //        item->setFontIcon(qextIconsFontAwesome->fontChar(QEXTIconsFontAwesome::FA_address_book));

//        item->setEnable(false);
//        item->parentItem()->setEnable(false);
//                item->setVisiable(false);
//        item->setChecked(false);

//        item->parentItem()->setVisiable(true);
    } else {
//        item->setEnable(false);
//        QList<QEXTNavListWidgetItem *> childItems = item->childItems();
//        QList<QEXTNavListWidgetItem *>::iterator iter;
//        for (iter = childItems.begin(); iter != childItems.end(); ++iter) {
//            (*iter)->setChecked(false);
//        }

//        if (0 == item->childItemsCount())
//        {
//            QList<QEXTNavListWidgetItem *>::iterator iter;
//            for (iter = m_parentItems.begin(); iter != m_parentItems.end(); ++iter) {
//                (*iter)->setVisiable(true);
//            }
//        }
    }
}

