#pragma execution_character_set("utf-8")
#include "navigationlistview.h"
#include "ui_navigationlistview.h"
#include "qtimer.h"



NavigationListView::NavigationListView(QWidget *parent) : QWidget(parent), ui(new Ui::NavigationListView)
{
    ui->setupUi(this);
    this->initForm();
}

NavigationListView::~NavigationListView()
{
    delete ui;
}

void NavigationListView::initForm()
{
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

    items.append("帮助文档||1|1024|");

    m_parentItems1 = ui->navListView1->setItems(items.join(","));
    ui->navListView1->setItemTipVisible(true);
    ui->navListView1->setExpendMode(QExtNavigationListView::ExpendMode_SingleClick);
    connect(ui->navListView1, SIGNAL(itemPressed(QExtNavigationListItem*)),
            this, SLOT(onItemPressed1(QExtNavigationListItem*)));


    m_parentItems2 = ui->navListView2->setItems(items.join(","));
    ui->navListView2->setItemTipVisible(false);
    ui->navListView2->setItemSeparateColor(QColor(255, 255, 255));
    ui->navListView2->setItemBackgroundColor(false, QExtNavigationListView::ItemState_Normal, QColor(238, 238, 238));
    ui->navListView2->setItemBackgroundColor(false, QExtNavigationListView::ItemState_Hovered, QColor(255, 160, 122));
    ui->navListView2->setItemBackgroundColor(false, QExtNavigationListView::ItemState_Checked, QColor(255, 69, 0));
    ui->navListView2->setItemBackgroundColor(false, QExtNavigationListView::ItemState_Selected, QColor(255, 69, 0));
    ui->navListView2->setItemTextColor(false, QExtNavigationListView::ItemState_Normal, QColor(10, 10, 10));
    ui->navListView2->setItemTextColor(false, QExtNavigationListView::ItemState_Hovered, QColor(10, 10, 10));
    ui->navListView2->setItemTextColor(false, QExtNavigationListView::ItemState_Checked, QColor(250, 250, 250));
    ui->navListView2->setItemTextColor(false, QExtNavigationListView::ItemState_Selected, QColor(250, 250, 250));
    ui->navListView2->setItemBackgroundColor(true, QExtNavigationListView::ItemState_Normal, QColor(238, 238, 238));
    ui->navListView2->setItemBackgroundColor(true, QExtNavigationListView::ItemState_Hovered, QColor(255, 160, 122));
    ui->navListView2->setItemBackgroundColor(true, QExtNavigationListView::ItemState_Checked, QColor(255, 69, 0));
    ui->navListView2->setItemBackgroundColor(true, QExtNavigationListView::ItemState_Selected, QColor(255, 69, 0));
    ui->navListView2->setItemTextColor(true, QExtNavigationListView::ItemState_Normal, QColor(10, 10, 10));
    ui->navListView2->setItemTextColor(true, QExtNavigationListView::ItemState_Hovered, QColor(10, 10, 10));
    ui->navListView2->setItemTextColor(true, QExtNavigationListView::ItemState_Checked, QColor(250, 250, 250));
    ui->navListView2->setItemTextColor(true, QExtNavigationListView::ItemState_Selected, QColor(250, 250, 250));
    ui->navListView2->setBackgroundColor(QColor(238, 238, 238));
    ui->navListView2->setExpendMode(QExtNavigationListView::ExpendMode_DoubleClick);
    connect(ui->navListView2, SIGNAL(itemPressed(QExtNavigationListItem*)),
            this, SLOT(onItemPressed2(QExtNavigationListItem*)));


    m_parentItems3 = m_parentItems2;
    ui->navListView3->setItems(m_parentItems2);
    ui->navListView3->setItemTipVisible(false);
    ui->navListView3->setItemSeparateColor(QColor(193, 193, 193));
    ui->navListView3->setItemBackgroundColor(false, QExtNavigationListView::ItemState_Normal, QColor(255, 255, 255));
    ui->navListView3->setItemBackgroundColor(false, QExtNavigationListView::ItemState_Hovered, QColor(240, 240, 240));
    ui->navListView3->setItemBackgroundColor(false, QExtNavigationListView::ItemState_Checked, QColor(230, 230, 230));
    ui->navListView3->setItemBackgroundColor(false, QExtNavigationListView::ItemState_Selected, QColor(230, 230, 230));
    ui->navListView3->setItemTextColor(false, QExtNavigationListView::ItemState_Normal, QColor(19, 36, 62));
    ui->navListView3->setItemTextColor(false, QExtNavigationListView::ItemState_Hovered, QColor(19, 36, 62));
    ui->navListView3->setItemTextColor(false, QExtNavigationListView::ItemState_Checked, QColor(19, 36, 62));
    ui->navListView3->setItemTextColor(false, QExtNavigationListView::ItemState_Selected, QColor(19, 36, 62));
    ui->navListView3->setItemBackgroundColor(true, QExtNavigationListView::ItemState_Normal, QColor(255, 255, 255));
    ui->navListView3->setItemBackgroundColor(true, QExtNavigationListView::ItemState_Hovered, QColor(240, 240, 240));
    ui->navListView3->setItemBackgroundColor(true, QExtNavigationListView::ItemState_Checked, QColor(230, 230, 230));
    ui->navListView3->setItemBackgroundColor(true, QExtNavigationListView::ItemState_Selected, QColor(230, 230, 230));
    ui->navListView3->setItemTextColor(true, QExtNavigationListView::ItemState_Normal, QColor(19, 36, 62));
    ui->navListView3->setItemTextColor(true, QExtNavigationListView::ItemState_Hovered, QColor(19, 36, 62));
    ui->navListView3->setItemTextColor(true, QExtNavigationListView::ItemState_Checked, QColor(19, 36, 62));
    ui->navListView3->setItemTextColor(true, QExtNavigationListView::ItemState_Selected, QColor(19, 36, 62));
    ui->navListView3->setBackgroundColor(QColor(255, 255, 255));
    ui->navListView3->setExpendMode(QExtNavigationListView::ExpendMode_SingleClick);
    connect(ui->navListView3, SIGNAL(itemPressed(QExtNavigationListItem*)),
            this, SLOT(onItemPressed3(QExtNavigationListItem*)));


    QList<QExtNavigationListItem *> itemList;
    QExtNavigationListItem *parentItem = new QExtNavigationListItem;
    itemList.append(parentItem);
    parentItem->setText("警情查询");
    parentItem->setTip("11");
    parentItem->setFontIcon(QChar(0xf073));
    QExtNavigationListItem *item = new QExtNavigationListItem(parentItem);
    item->setText("记录查询");
    item->setTip("ss");
    item->setFontIcon(QChar(0xf073));
    item = new QExtNavigationListItem;
    item->setParentItem(parentItem);
    item->setText("图像查询");
    item->setTip("ss");
    item->setFontIcon(QChar(0xf03e));
    item = new QExtNavigationListItem();
    item->setParentItem(parentItem);
    item->setText("视频查询");
    item->setTip("ss");
    item->setFontIcon(QChar(0xf03d));
    item = new QExtNavigationListItem();
    item->setParentItem(parentItem);
    item->setText("数据回放");
    item->setTip("ss");
    item->setFontIcon(QChar(0xf080));
    parentItem = new QExtNavigationListItem;
    itemList.append(parentItem);
    parentItem->setText("帮助文档");
    parentItem->setTip("11");
    //    m_parentItems4 = ui->navListView4->setItems(items.join(","));
    ui->navListView4->setItems(itemList);
    ui->navListView4->setItemTipVisible(false);
    // ui->navListView4->setItemSeparateColor(QColor(32, 53, 74));
    // ui->navListView4->setItemBackgroundColor(QColor(52, 73, 94));
    // ui->navListView4->setItemBackgroundColor(QColor(24, 189, 155));
    // ui->navListView4->setItemBackgroundColor(QColor(24, 189, 155));
    // ui->navListView4->setChildItemNormalTextColor(QColor(250, 250, 250));
    // ui->navListView4->setChildItemCheckedTextColor(QColor(230, 230, 230));
    // ui->navListView4->setChildItemHoverTextColor(QColor(10, 10, 10));
    // ui->navListView4->setParentItemNormalBackgroundColor(QColor(52, 73, 94));
    // ui->navListView4->setParentItemCheckedBackgroundColor(QColor(24, 189, 155));
    // ui->navListView4->setParentItemHoverBackgroundColor(QColor(24, 189, 155));
    // ui->navListView4->setParentItemNormalTextColor(QColor(250, 250, 250));
    // ui->navListView4->setParentItemCheckedTextColor(QColor(230, 230, 230));
    // ui->navListView4->setParentItemHoverTextColor(QColor(10, 10, 10));
    // ui->navListView4->setBackgroundColor(QColor(52, 73, 94));
    ui->navListView4->setExpendMode(QExtNavigationListView::ExpendMode_SingleClick);
    connect(ui->navListView4, SIGNAL(itemPressed(QExtNavigationListItem*)),
            this, SLOT(onItemPressed4(QExtNavigationListItem*)));

}

void NavigationListView::onItemPressed1(QExtNavigationListItem *item)
{
    if (item->isChildItem())
    {
//        item->setEnable(false);
//        item->parentItem()->setEnable(false);
    }
    else
    {

    }
}

void NavigationListView::onItemPressed2(QExtNavigationListItem *item)
{
    if (item->isChildItem())
    {
//        item->setEnable(false);
//        item->parentItem()->setEnable(false);
    }
    else
    {

    }
}

void NavigationListView::onItemPressed3(QExtNavigationListItem *item)
{
    if (item->isChildItem())
    {
//        item->setEnable(false);
//        item->parentItem()->setEnable(false);
    }
    else
    {

    }
}

void NavigationListView::onItemPressed4(QExtNavigationListItem *item)
{
    if (item->isChildItem())
    {
//        item->setVisible(false);
//        item->setEnable(false);
//        item->setEnable(false);
//        item->parentItem()->setEnable(false);
//        item->parentItem()->setVisible(false);
    }
    else
    {

    }
}
