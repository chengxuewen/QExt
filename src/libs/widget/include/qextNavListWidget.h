#ifndef QEXTNAVLISTWIDGET_H
#define QEXTNAVLISTWIDGET_H

#include <qextWidgetGlobal.h>

#include <qextObject.h>

/**
 * feiyangqingyun(QQ:517216493) 2018-8-15
 */

/**
 * @brief feiyangqingyun(QQ:517216493) 2018-8-15
 *
 * @bug
 *      1.Multiple model case sometions appear item background color is drawn in black
 */



#ifndef Q_WS_QWS
    #if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
        #include <QtDesigner/QDesignerExportWidget>
    #else
        #include <QtUiPlugin/QDesignerExportWidget>
    #endif
#endif

#include <QStringList>
#include <QListView>
#include <QList>

class QEXTNavListWidgetItemPrivate;
class QEXT_WIDGET_API QEXTNavListWidgetItem : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    explicit QEXTNavListWidgetItem(QEXTNavListWidgetItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavListWidgetItem(const QString &text, QEXTNavListWidgetItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavListWidgetItem(const QString &text, const QPixmap &icon, QEXTNavListWidgetItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavListWidgetItem(const QString &text, const QPixmap &icon, bool expand, QEXTNavListWidgetItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavListWidgetItem(const QString &text, const QString &tip, const QPixmap &icon, QEXTNavListWidgetItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavListWidgetItem(const QString &text, const QString &tip, const QPixmap &icon, bool expand, QEXTNavListWidgetItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavListWidgetItem(const QString &text, const QChar &fontChar, QEXTNavListWidgetItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavListWidgetItem(const QString &text, const QChar &fontChar, bool expand, QEXTNavListWidgetItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavListWidgetItem(const QString &text, const QString &tip, const QChar &fontChar, QEXTNavListWidgetItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavListWidgetItem(const QString &text, const QString &tip, const QChar &fontChar, bool expand, QEXTNavListWidgetItem *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavListWidgetItem();

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
    QEXTNavListWidgetItem *parentItem() const;
    bool setParentItem(QEXTNavListWidgetItem *parent);

    int childItemsCount() const;
    int visiableChildItemsCount() const;
    QList<QEXTNavListWidgetItem *> childItems() const;
    QList<QEXTNavListWidgetItem *> visiableChildItems() const;

signals:
    void itemAboutToDestroyed(QEXTNavListWidgetItem *item);
    void iconChanged(QEXTNavListWidgetItem *item);
    void fontIconChanged(QEXTNavListWidgetItem *item);
    void textChanged(QEXTNavListWidgetItem *item);
    void tipChanged(QEXTNavListWidgetItem *item);
    void expandChanged(QEXTNavListWidgetItem *item);
    void enableChanged(QEXTNavListWidgetItem *item);
    void checkChanged(QEXTNavListWidgetItem *item);

    void visiableAboutToBeChanged(QEXTNavListWidgetItem *item);
    void visiableChanged(QEXTNavListWidgetItem *item);

    void childItemAboutToBeInserted(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent);
    void childItemInserted(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent);

    void childItemAboutToBeRemoved(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent);
    void childItemRemoved(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent);

protected slots:
    void onChildItemAboutToBeDestroyed(QEXTNavListWidgetItem *item);

private:
    friend class QEXTNavListModel;
    QEXT_DECL_PRIVATE(QEXTNavListWidgetItem)
    QEXT_DISABLE_COPY_MOVE(QEXTNavListWidgetItem)
};


class QEXTNavListModelPrivate;
class QEXT_WIDGET_API QEXTNavListModel : public QAbstractListModel, public QEXTObject
{
    Q_OBJECT
public:
    explicit QEXTNavListModel(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavListModel();

    QEXTNavListWidgetItem *checkedItem() const;
    QList<QEXTNavListWidgetItem *> allItems() const;
    QList<QEXTNavListWidgetItem *> parentItems() const;
    QList<QEXTNavListWidgetItem *> visiableItems() const;

public slots:
    void setItems(const QStringList &items);
    void setItems(const QList<QEXTNavListWidgetItem *> &items);
    void expandCollapseItem(const QModelIndex &index);

signals:
    void checkedItemChanged(QEXTNavListWidgetItem *item);

protected slots:
    void onItemAboutToDestroyed(QEXTNavListWidgetItem *item);
    void onItemChanged(QEXTNavListWidgetItem *item);
    void onItemEnableChanged(QEXTNavListWidgetItem *item);
    void onItemExpandChanged(QEXTNavListWidgetItem *item);
    void onItemCheckChanged(QEXTNavListWidgetItem *item);
    void onItemVisiableAboutToBeChanged(QEXTNavListWidgetItem *item);
    void onItemVisiableChanged(QEXTNavListWidgetItem *item);
    void onChildItemAboutToBeInserted(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent);
    void onChildItemInserted(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent);
    void onChildItemAboutToBeRemoved(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent);
    void onChildItemRemoved(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent);

protected:
    int rowCount(const QModelIndex &parent) const QEXT_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const QEXT_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTNavListModel)
    QEXT_DISABLE_COPY_MOVE(QEXTNavListModel)
};


class QEXTNavListWidgetPrivate;
class QEXT_WIDGET_API QEXTNavListWidget : public QWidget, public QEXTObject
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

    explicit QEXTNavListWidget(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavListWidget();

    QListView *view() const;
    QEXTNavListModel *model() const;

    QEXTNavListWidgetItem * selectedItem() const;
    QEXTNavListWidgetItem * checkedItem() const;
    QList<QEXTNavListWidgetItem *> allItems() const;
    QList<QEXTNavListWidgetItem *> parentItems() const;
    QList<QEXTNavListWidgetItem *> visiableItems() const;

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

public slots:
    void setModel(QEXTNavListModel *model);

    //设置节点数据
    QList<QEXTNavListWidgetItem *> setItems(const QString &items);
    QList<QEXTNavListWidgetItem *> setItems(const QStringList &items);
    void setItems(const QList<QEXTNavListWidgetItem *> &items);

    bool setCurrentRow(int row);
    bool setSelectedItem(QEXTNavListWidgetItem *item);
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
    void itemPressed(QEXTNavListWidgetItem *item);
    void checkedItemChanged(QEXTNavListWidgetItem *item);
    void selectedItemChanged(QEXTNavListWidgetItem *item);

protected:
    void paintEvent(QPaintEvent *event) QEXT_DECL_OVERRIDE;

private slots:
    void onItemPressed(const QModelIndex &index);

private:
    QEXT_DECL_PRIVATE(QEXTNavListWidget)
    QEXT_DISABLE_COPY_MOVE(QEXTNavListWidget)
};

#endif // QEXTNAVLISTWIDGET_H
