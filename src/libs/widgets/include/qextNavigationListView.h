#ifndef _QEXTNAVIGATIONLISTVIEW_H
#define _QEXTNAVIGATIONLISTVIEW_H

/***************************************************************************************************
 *@Brief:列表导航控件
 *  1.Multiple model case sometions appear item background color is drawn in black
 *@Author:chengxuewen，QQ：1398831004，Email：1398831004@qq.com,基于刘典武工程师（QQ:517216493）代码。
 *@Version:V0.1
 *@Date:2018-8-15
 *@History:
 *  Modification data:2021-10-16
 *  Author:chengxuewen
 *  Brief:  （1）.整理优化;
***************************************************************************************************/

#include <qextWidgetGlobal.h>

#include <QScopedPointer>
#include <QStringList>
#include <QListView>
#include <QList>

class QEXTNavigationListItemPrivate;
class QEXT_WIDGETS_API QEXTNavigationListItem : public QObject
{
    Q_OBJECT
public:
    explicit QEXTNavigationListItem(QEXTNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavigationListItem(const QString &text, QEXTNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavigationListItem(const QString &text, const QPixmap &icon, QEXTNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavigationListItem(const QString &text, const QPixmap &icon, bool expand, QEXTNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavigationListItem(const QString &text, const QString &tip, const QPixmap &icon, QEXTNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavigationListItem(const QString &text, const QString &tip, const QPixmap &icon, bool expand, QEXTNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavigationListItem(const QString &text, const QChar &fontChar, QEXTNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavigationListItem(const QString &text, const QChar &fontChar, bool expand, QEXTNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavigationListItem(const QString &text, const QString &tip, const QChar &fontChar, QEXTNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavigationListItem(const QString &text, const QString &tip, const QChar &fontChar, bool expand, QEXTNavigationListItem *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavigationListItem();

    QPixmap normalIcon() const;
    QPixmap hoverIcon() const;
    QPixmap checkedIcon() const;
    QPixmap selectedIcon() const;
    void setIcon(const QPixmap &icon);
    void setNormalIcon(const QPixmap &icon);
    void setHoverIcon(const QPixmap &icon);
    void setCheckedIcon(const QPixmap &icon);
    void setSelectedIcon(const QPixmap &icon);

    QChar fontIcon() const;
    void setFontIcon(const QChar &ch);

    QString text() const;
    void setText(const QString &text);

    QString tip() const;
    void setTip(const QString &tip);

    bool isExpand() const;
    void setExpand(const bool &expand);

    bool isVisiable() const;
    void setVisiable(const bool &visiable);

    bool isEnabled() const;
    void setEnable(const bool &enable);

    Qt::CheckState checkState() const;
    bool isChecked() const;
    bool setChecked(bool check);

    bool isLastVisiableItem() const;
    bool isChildItem() const;
    bool isParentItem() const;
    QEXTNavigationListItem *parentItem() const;
    bool setParentItem(QEXTNavigationListItem *parent);

    int childItemsCount() const;
    int visiableChildItemsCount() const;
    QList<QEXTNavigationListItem *> childItems() const;
    QList<QEXTNavigationListItem *> visiableChildItems() const;

signals:
    void itemAboutToDestroyed(QEXTNavigationListItem *item);
    void iconChanged(QEXTNavigationListItem *item);
    void fontIconChanged(QEXTNavigationListItem *item);
    void textChanged(QEXTNavigationListItem *item);
    void tipChanged(QEXTNavigationListItem *item);
    void expandChanged(QEXTNavigationListItem *item);
    void enableChanged(QEXTNavigationListItem *item);
    void checkChanged(QEXTNavigationListItem *item);

    void visiableAboutToBeChanged(QEXTNavigationListItem *item);
    void visiableChanged(QEXTNavigationListItem *item);

    void childItemAboutToBeInserted(QEXTNavigationListItem *item, QEXTNavigationListItem *parent);
    void childItemInserted(QEXTNavigationListItem *item, QEXTNavigationListItem *parent);

    void childItemAboutToBeRemoved(QEXTNavigationListItem *item, QEXTNavigationListItem *parent);
    void childItemRemoved(QEXTNavigationListItem *item, QEXTNavigationListItem *parent);

protected Q_SLOTS:
    void onChildItemAboutToBeDestroyed(QEXTNavigationListItem *item);

protected:
    QScopedPointer<QEXTNavigationListItemPrivate> d_ptr;

private:
    friend class QEXTNavigationListModel;
    QEXT_DECL_PRIVATE(QEXTNavigationListItem)
    QEXT_DECL_DISABLE_COPY(QEXTNavigationListItem)
};


class QEXTNavigationListModelPrivate;
class QEXT_WIDGETS_API QEXTNavigationListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit QEXTNavigationListModel(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavigationListModel();

    QEXTNavigationListItem *checkedItem() const;
    QList<QEXTNavigationListItem *> allItems() const;
    QList<QEXTNavigationListItem *> parentItems() const;
    QList<QEXTNavigationListItem *> visiableItems() const;

public slots:
    void setItems(const QStringList &items);
    void setItems(const QList<QEXTNavigationListItem *> &items);
    void expandCollapseItem(const QModelIndex &index);

signals:
    void checkedItemChanged(QEXTNavigationListItem *item);

protected slots:
    void onItemAboutToDestroyed(QEXTNavigationListItem *item);
    void onItemChanged(QEXTNavigationListItem *item);
    void onItemEnableChanged(QEXTNavigationListItem *item);
    void onItemExpandChanged(QEXTNavigationListItem *item);
    void onItemCheckChanged(QEXTNavigationListItem *item);
    void onItemVisiableAboutToBeChanged(QEXTNavigationListItem *item);
    void onItemVisiableChanged(QEXTNavigationListItem *item);
    void onChildItemAboutToBeInserted(QEXTNavigationListItem *item, QEXTNavigationListItem *parent);
    void onChildItemInserted(QEXTNavigationListItem *item, QEXTNavigationListItem *parent);
    void onChildItemAboutToBeRemoved(QEXTNavigationListItem *item, QEXTNavigationListItem *parent);
    void onChildItemRemoved(QEXTNavigationListItem *item, QEXTNavigationListItem *parent);

protected:
    int rowCount(const QModelIndex &parent) const QEXT_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const QEXT_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const QEXT_DECL_OVERRIDE;

    QScopedPointer<QEXTNavigationListModelPrivate> d_ptr;

private:
    QEXT_DECL_PRIVATE(QEXTNavigationListModel)
    QEXT_DECL_DISABLE_COPY(QEXTNavigationListModel)
};


class QEXTNavigationListViewPrivate;
class QEXT_WIDGETS_API QEXTNavigationListView : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool itemRightIconVisible READ itemRightIconVisible WRITE setItemRightIconVisible)
    Q_PROPERTY(bool itemTipVisible READ itemTipVisible WRITE setItemTipVisible)
    Q_PROPERTY(int itemTipWidth READ itemTipWidth WRITE setItemTipWidth)

    Q_PROPERTY(bool itemSeparateVisible READ itemSeparateVisible WRITE setItemSeparateVisible)
    Q_PROPERTY(int itemSeparateHeight READ itemSeparateHeight WRITE setItemSeparateHeight)
    Q_PROPERTY(QColor itemSeparateColor READ itemSeparateColor WRITE setItemSeparateColor)

    Q_PROPERTY(bool itemLineLeft READ itemLineLeft WRITE setItemLineLeft)
    Q_PROPERTY(bool itemLineVisible READ itemLineVisible WRITE setItemLineVisible)
    Q_PROPERTY(int itemLineWidth READ itemLineWidth WRITE setItemLineWidth)
    Q_PROPERTY(QColor itemLineColor READ itemLineColor WRITE setItemLineColor)

    Q_PROPERTY(bool itemTriangleLeft READ itemTriangleLeft WRITE setItemTriangleLeft)
    Q_PROPERTY(bool itemTriangleVisible READ itemTriangleVisible WRITE setItemTriangleVisible)
    Q_PROPERTY(int itemTriangleWidth READ itemTriangleWidth WRITE setItemTriangleWidth)
    Q_PROPERTY(QColor itemTriangleColor READ itemTriangleColor WRITE setItemTriangleColor)

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

    Q_PROPERTY(int parentItemIconMargin READ parentItemIconMargin WRITE setParentItemIconMargin)
    Q_PROPERTY(int parentItemMargin READ parentItemMargin WRITE setParentItemMargin)
    Q_PROPERTY(int parentItemFontSize READ parentItemFontSize WRITE setParentItemFontSize)
    Q_PROPERTY(int parentItemHeight READ parentItemHeight WRITE setParentItemHeight)
    Q_PROPERTY(QColor parentItemNormalBackgroundColor READ parentItemNormalBackgroundColor WRITE setParentItemNormalBackgroundColor)
    Q_PROPERTY(QColor parentItemCheckedBackgroundColor READ parentItemCheckedBackgroundColor WRITE setParentItemCheckedBackgroundColor)
    Q_PROPERTY(QColor parentItemSelectedBackgroundColor READ parentItemSelectedBackgroundColor WRITE setParentItemSelectedBackgroundColor)
    Q_PROPERTY(QColor parentItemHoverBackgroundColor READ parentItemHoverBackgroundColor WRITE setParentItemHoverBackgroundColor)
    Q_PROPERTY(QColor parentItemNormalTextColor READ parentItemNormalTextColor WRITE setParentItemNormalTextColor)
    Q_PROPERTY(QColor parentItemCheckedTextColor READ parentItemCheckedTextColor WRITE setParentItemCheckedTextColor)
    Q_PROPERTY(QColor parentItemSelectedTextColor READ parentItemSelectedTextColor WRITE setParentItemSelectedTextColor)
    Q_PROPERTY(QColor parentItemHoverTextColor READ parentItemHoverTextColor WRITE setParentItemHoverTextColor)

    Q_PROPERTY(int childItemIconMargin READ childItemIconMargin WRITE setChildItemIconMargin)
    Q_PROPERTY(int childItemMargin READ childItemMargin WRITE setChildItemMargin)
    Q_PROPERTY(int childItemFontSize READ childItemFontSize WRITE setChildItemFontSize)
    Q_PROPERTY(int childItemHeight READ childItemHeight WRITE setChildItemHeight)
    Q_PROPERTY(QColor childItemNormalBackgroundColor READ childItemNormalBackgroundColor WRITE setChildItemNormalBackgroundColor)
    Q_PROPERTY(QColor childItemCheckedBackgroundColor READ childItemCheckedBackgroundColor WRITE setChildItemBackgroundCheckedColor)
    Q_PROPERTY(QColor childItemSelectedBackgroundColor READ childItemSelectedBackgroundColor WRITE setChildItemSelectedBackgroundColor)
    Q_PROPERTY(QColor childItemHoverBackgroundColor READ childItemHoverBackgroundColor WRITE setChildItemHoverBackgroundColor)
    Q_PROPERTY(QColor childItemNormalTextColor READ childItemNormalTextColor WRITE setChildItemNormalTextColor)
    Q_PROPERTY(QColor childItemCheckedTextColor READ childItemCheckedTextColor WRITE setChildItemCheckedTextColor)
    Q_PROPERTY(QColor childItemSelectedTextColor READ childItemSelectedTextColor WRITE setChildItemSelectedTextColor)
    Q_PROPERTY(QColor childItemHoverTextColor READ childItemHoverTextColor WRITE setChildItemHoverTextColor)

    Q_PROPERTY(ExpendMode m_expendMode READ expendMode WRITE setExpendMode)

public:
    //节点展开模式
    enum ExpendMode
    {
        ExpendMode_SingleClick = 0, //单击模式
        ExpendMode_DoubleClick = 1, //双击模式
        ExpendMode_NoClick = 2,     //不可单击双击
    };
    Q_ENUMS(ExpendMode)

    explicit QEXTNavigationListView(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavigationListView();

    QListView *view() const;
    QEXTNavigationListModel *model() const;

    QEXTNavigationListItem * selectedItem() const;
    QEXTNavigationListItem * checkedItem() const;
    QList<QEXTNavigationListItem *> allItems() const;
    QList<QEXTNavigationListItem *> parentItems() const;
    QList<QEXTNavigationListItem *> visiableItems() const;

    bool itemRightIconVisible() const;
    bool itemTipVisible() const;
    int itemTipWidth() const;

    bool itemSeparateVisible() const;
    int itemSeparateHeight() const;
    QColor itemSeparateColor() const;

    bool itemLineLeft() const;
    bool itemLineVisible() const;
    int itemLineWidth() const;
    QColor itemLineColor() const;

    bool itemTriangleLeft() const;
    bool itemTriangleVisible() const;
    int itemTriangleWidth() const;
    QColor itemTriangleColor() const;

    QColor backgroundColor() const;

    int parentItemIconMargin() const;
    int parentItemMargin() const;
    int parentItemFontSize() const;
    int parentItemHeight() const;
    QColor parentItemNormalBackgroundColor() const;
    QColor parentItemCheckedBackgroundColor() const;
    QColor parentItemSelectedBackgroundColor() const;
    QColor parentItemHoverBackgroundColor() const;
    QColor parentItemNormalTextColor() const;
    QColor parentItemCheckedTextColor() const;
    QColor parentItemSelectedTextColor() const;
    QColor parentItemHoverTextColor() const;

    int childItemIconMargin() const;
    int childItemMargin() const;
    int childItemFontSize() const;
    int childItemHeight() const;
    QColor childItemNormalBackgroundColor() const;
    QColor childItemCheckedBackgroundColor() const;
    QColor childItemSelectedBackgroundColor() const;
    QColor childItemHoverBackgroundColor() const;
    QColor childItemNormalTextColor() const;
    QColor childItemCheckedTextColor() const;
    QColor childItemSelectedTextColor() const;
    QColor childItemHoverTextColor() const;

    ExpendMode expendMode() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public Q_SLOTS:
    void setModel(QEXTNavigationListModel *model);

    //设置节点数据
    QList<QEXTNavigationListItem *> setItems(const QString &items);
    QList<QEXTNavigationListItem *> setItems(const QStringList &items);
    void setItems(const QList<QEXTNavigationListItem *> &items);

    bool setCurrentRow(int row);
    bool setSelectedItem(QEXTNavigationListItem *item);
    void setItemRightIconVisible(bool visible);

    void setItemTipVisible(bool visible);
    void setItemTipWidth(int width);

    //设置行分隔符 是否显示+高度+颜色
    void setItemSeparateVisible(bool visible);
    void setItemSeparateHeight(int height);
    void setItemSeparateColor(const QColor &color);

    //设置线条 位置+可见+宽度+颜色
    void setItemLineLeft(bool inLeft);
    void setItemLineVisible(bool visible);
    void setItemLineWidth(int width);
    void setItemLineColor(const QColor &color);

    //设置三角形 位置+可见+宽度+颜色
    void setItemTriangleLeft(bool inLeft);
    void setItemTriangleVisible(bool visible);
    void setItemTriangleWidth(int width);
    void setItemTriangleColor(const QColor &color);

    void setBackgroundColor(const QColor &color);

    //设置父节点 图标边距+左侧边距+字体大小+节点高度+颜色集合
    void setParentItemIconMargin(int margin);
    void setParentItemMargin(int margin);
    void setParentItemFontSize(int size);
    void setParentItemHeight(int height);
    void setParentItemNormalBackgroundColor(const QColor &color);
    void setParentItemCheckedBackgroundColor(const QColor &color);
    void setParentItemSelectedBackgroundColor(const QColor &color);
    void setParentItemHoverBackgroundColor(const QColor &color);
    void setParentItemNormalTextColor(const QColor &color);
    void setParentItemCheckedTextColor(const QColor &color);
    void setParentItemSelectedTextColor(const QColor &color);
    void setParentItemHoverTextColor(const QColor &color);

    //设置子节点 图标边距+左侧边距+字体大小+节点高度+颜色集合
    void setChildItemIconMargin(int margin);
    void setChildItemMargin(int margin);
    void setChildItemFontSize(int size);
    void setChildItemHeight(int height);
    void setChildItemNormalBackgroundColor(const QColor &color);
    void setChildItemBackgroundCheckedColor(const QColor &color);
    void setChildItemSelectedBackgroundColor(const QColor &color);
    void setChildItemHoverBackgroundColor(const QColor &color);
    void setChildItemNormalTextColor(const QColor &color);
    void setChildItemCheckedTextColor(const QColor &color);
    void setChildItemSelectedTextColor(const QColor &color);
    void setChildItemHoverTextColor(const QColor &color);

    //设置节点展开模式
    void setExpendMode(const ExpendMode &mode);

signals:
    void itemPressed(QEXTNavigationListItem *item);
    void checkedItemChanged(QEXTNavigationListItem *item);
    void selectedItemChanged(QEXTNavigationListItem *item);

protected:
    void paintEvent(QPaintEvent *event) QEXT_DECL_OVERRIDE;

    QScopedPointer<QEXTNavigationListViewPrivate> d_ptr;

private Q_SLOTS:
    void onItemPressed(const QModelIndex &index);

private:
    QEXT_DECL_PRIVATE(QEXTNavigationListView)
    QEXT_DECL_DISABLE_COPY(QEXTNavigationListView)
};

#endif // _QEXTNAVIGATIONLISTVIEW_H
