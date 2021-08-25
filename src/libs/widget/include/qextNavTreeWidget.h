#ifndef QEXTNAVTREEWIDGET_H
#define QEXTNAVTREEWIDGET_H

/**
 * 树状导航栏控件 作者:feiyangqingyun(QQ:517216493) 2018-8-15
 * 1:设置节点数据相当方便,按照对应格式填入即可,分隔符,
 * 2:可设置提示信息 是否显示+宽度
 * 3:可设置行分隔符 是否显示+高度+颜色
 * 4:可设置选中节点线条突出显示+颜色+左侧右侧位置
 * 5:可设置选中节点三角形突出显示+颜色+左侧右侧位置
 * 6:可设置父节点的 选中颜色+悬停颜色+默认颜色
 * 7:可设置子节点的 选中颜色+悬停颜色+默认颜色
 * 8:可设置父节点文字的 图标边距+左侧距离+字体大小+高度
 * 9:可设置子节点文字的 图标边距+左侧距离+字体大小+高度
 * 10:可设置节点展开模式 单击+双击+禁用
 */

#include <qextWidgetGlobal.h>
#include <qextobject.h>

#include <QPointer>
#include <QListView>
#include <QTreeView>
#include <QStringList>
#include <QAbstractListModel>
#include <QStyledItemDelegate>

#if (QT_VERSION < QT_VERSION_CHECK(5, 7, 0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QEXTNavTreeWidget;

class QEXTNavTreeItemPrivate;
class QEXTNavTreeItem : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    QEXTNavTreeItem(QEXTNavTreeItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavTreeItem(const QString &text, const QIcon &icon, QEXTNavTreeItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavTreeItem(const QString &text, const QIcon &icon, bool expand, QEXTNavTreeItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavTreeItem(const QString &text, const QString &tip, const QIcon &icon, QEXTNavTreeItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavTreeItem(const QString &text, const QString &tip, const QIcon &icon, bool expand, QEXTNavTreeItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavTreeItem(const QString &text, const QChar &fontChar, QEXTNavTreeItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavTreeItem(const QString &text, const QChar &fontChar, bool expand, QEXTNavTreeItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavTreeItem(const QString &text, const QString &tip, const QChar &fontChar, QEXTNavTreeItem *parent = QEXT_DECL_NULLPTR);
    QEXTNavTreeItem(const QString &text, const QString &tip, const QChar &fontChar, bool expand, QEXTNavTreeItem *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavTreeItem();

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    QChar fontChar() const;
    void setFontIcon(const QChar &ch);

    QString text() const;
    void setText(const QString &text);

    QString tip() const;
    void setTip(const QString &tip);

    bool isExpand() const;
    void setExpand(const bool &expand);

    int level() const;

    bool isLastItem() const;
    bool isChildItem() const;
    bool isParentItem() const;
    QEXTNavTreeItem *parentItem() const;
    void setParentItem(QEXTNavTreeItem *parent);

    int childItemsCount() const;
    QList<QEXTNavTreeItem *> childItems() const;
    void addChildItems(const QList<QEXTNavTreeItem *> &items);
    void addChildItem(QEXTNavTreeItem *item);
    void prependChildItem(QEXTNavTreeItem *item);
    void removeChildItem(QEXTNavTreeItem *item);
    void insertChildItem(QEXTNavTreeItem *preItem, QEXTNavTreeItem *item);

    int indexOfParentItem() const;

signals:
    void iconChanged(QEXTNavTreeItem *item);
    void fontIconChanged(QEXTNavTreeItem *item);
    void textChanged(QEXTNavTreeItem *item);
    void tipChanged(QEXTNavTreeItem *item);
    void expandChanged(QEXTNavTreeItem *item);

    void parentItemAboutToBeChanged(QEXTNavTreeItem *oldParent, QEXTNavTreeItem *newParent);
    void parentItemChanged(QEXTNavTreeItem *oldParent, QEXTNavTreeItem *newParent);

    void childItemAboutToBeInserted(QEXTNavTreeItem *item, QEXTNavTreeItem *parent);
    void childItemInserted(QEXTNavTreeItem *item, QEXTNavTreeItem *parent);

    void childItemAboutToBeRemoved(QEXTNavTreeItem *item, QEXTNavTreeItem *parent);
    void childItemRemoved(QEXTNavTreeItem *item, QEXTNavTreeItem *parent);

private:
    friend class QEXTNavTreeModel;
    QEXT_DECL_PRIVATE(QEXTNavTreeItem)
    QEXT_DISABLE_COPY_MOVE(QEXTNavTreeItem)
};


class QEXT_WIDGET_API QEXTNavTreeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QEXTNavTreeDelegate(QEXTNavTreeWidget *parent);
    ~QEXTNavTreeDelegate();

protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QEXTNavTreeWidget *m_navListView;
    QFont m_iconFont;
};

class QEXT_WIDGET_API QEXTNavTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    QEXTNavTreeModel(QEXTNavTreeWidget *parent);
    ~QEXTNavTreeModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const QEXT_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const QEXT_DECL_OVERRIDE;
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const QEXT_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const QEXT_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const QEXT_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const QEXT_DECL_OVERRIDE;

public slots:
    void setItems(const QStringList &items);
    void setItems(const QList<QEXTNavTreeItem *> &items);
    void expandItem(const QModelIndex &index);

protected:
    QModelIndex indexFromItem(QEXTNavTreeItem *item) const;
    QEXTNavTreeItem *itemFromIndex(const QModelIndex &index) const;
    QEXTNavTreeItem *itemFromText(const QString &text) const;

    QList<QEXTNavTreeItem *> rootItems() const;
    QList<QEXTNavTreeItem *> allItems() const;

    void iterateItems(const QList<QEXTNavTreeItem *> &items);
    void initItems();

private slots:
    void onItemExpandeChanged(QEXTNavTreeItem *item);

    void onParentItemAboutToBeChanged(QEXTNavTreeItem *oldParent, QEXTNavTreeItem *newParent);
    void onParentItemChanged(QEXTNavTreeItem *oldParent, QEXTNavTreeItem *newParent);

    void onChildItemAboutToBeInserted(QEXTNavTreeItem *item, QEXTNavTreeItem *parent);
    void onChildItemInserted(QEXTNavTreeItem *item, QEXTNavTreeItem *parent);

    void onChildItemAboutToBeRemoved(QEXTNavTreeItem *item, QEXTNavTreeItem *parent);
    void onChildItemRemoved(QEXTNavTreeItem *item, QEXTNavTreeItem *parent);

private:
    friend class QEXTNavTreeWidget;

    QEXTNavTreeWidget *m_navListView;
    QSet<QEXTNavTreeItem *> m_itemSet;
    QList<QEXTNavTreeItem *> m_childItemList;
    QList<QEXTNavTreeItem *> m_rootItemList;
    QMap<QString, QEXTNavTreeItem *> m_textItemMap;
};

class QEXT_WIDGET_API QEXTNavTreeWidget : public QTreeView
{
    Q_OBJECT
    Q_ENUMS(ExpendModeType)

    Q_PROPERTY(bool m_rightIconVisible READ isItemRightIconVisible WRITE setRightIconVisible)
    Q_PROPERTY(bool m_tipVisible READ isItemTipVisible WRITE setTipVisible)
    Q_PROPERTY(int m_tipWidth READ itemTipWidth WRITE setTipWidth)

    Q_PROPERTY(bool m_separateVisible READ isITemSeparateVisible WRITE setSeparateVisible)
    Q_PROPERTY(int m_separateHeight READ itemSeparateHeight WRITE setSeparateHeight)
    Q_PROPERTY(QColor m_separateColor READ itemSeparateColor WRITE setSeparateColor)

    Q_PROPERTY(bool m_lineLeft READ isItemLineInLeft WRITE setLineLeft)
    Q_PROPERTY(bool m_lineVisible READ isItemLineVisible WRITE setLineVisible)
    Q_PROPERTY(int m_lineWidth READ itemIineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor m_lineColor READ itemLineColor WRITE setLineColor)

    Q_PROPERTY(bool m_triangleLeft READ isItemTriangleInLeft WRITE setTriangleLeft)
    Q_PROPERTY(bool m_triangleVisible READ ItemTriangleVisible WRITE setTriangleVisible)
    Q_PROPERTY(int m_triangleWidth READ itemTriangleWidth WRITE setTriangleWidth)
    Q_PROPERTY(QColor m_triangleColor READ itemTriangleColor WRITE setTriangleColor)

    Q_PROPERTY(int m_parentIconMargin READ rootItemIconMargin WRITE setParentIconMargin)
    Q_PROPERTY(int m_parentMargin READ rootItemMargin WRITE setParentMargin)
    Q_PROPERTY(int m_parentFontSize READ rootItemFontSize WRITE setParentFontSize)
    Q_PROPERTY(int m_parentHeight READ rootItemHeight WRITE setParentHeight)
    Q_PROPERTY(QColor rootItemBackgroundNormalColor READ rootItemBackgroundNormalColor WRITE setParentBgNormalColor)
    Q_PROPERTY(QColor rootItemBackgroundSelectedColor READ rootItemBackgroundSelectedColor WRITE setParentBgSelectedColor)
    Q_PROPERTY(QColor rootItemBackgroundHoverColor READ rootItemBackgroundHoverColor WRITE setParentBgHoverColor)
    Q_PROPERTY(QColor rootItemTextNormalColor READ rootItemTextNormalColor WRITE setParentTextNormalColor)
    Q_PROPERTY(QColor rootItemTextSelectedColor READ rootItemTextSelectedColor WRITE setParentTextSelectedColor)
    Q_PROPERTY(QColor rootItemTextHoverColor READ rootItemTextHoverColor WRITE setParentTextHoverColor)

    Q_PROPERTY(int m_childIconMargin READ childItemIconMargin WRITE setChildIconMargin)
    Q_PROPERTY(int m_childMargin READ childItemMargin WRITE setChildMargin)
    Q_PROPERTY(int m_childFontSize READ childItemFontSize WRITE setChildFontSize)
    Q_PROPERTY(int m_childHeight READ childItemHeight WRITE setChildHeight)
    Q_PROPERTY(QColor m_childBkgNormalColor READ childItemBackgroundNormalColor WRITE setChildBgNormalColor)
    Q_PROPERTY(QColor m_childBkgSelectedColor READ childItemBackgroundSelectedColor WRITE setChildBgSelectedColor)
    Q_PROPERTY(QColor childItemBackgroundHoverColor READ childItemBackgroundHoverColor WRITE setChildBgHoverColor)
    Q_PROPERTY(QColor childItemTextNormalColor READ childItemTextNormalColor WRITE setChildTextNormalColor)
    Q_PROPERTY(QColor childItemTextSelectedColor READ childItemTextSelectedColor WRITE setChildTextSelectedColor)
    Q_PROPERTY(QColor childItemTextHoverColor READ childItemTextHoverColor WRITE setChildTextHoverColor)

    Q_PROPERTY(ExpendModeType expendMode READ expendMode WRITE setExpendMode)

public:
    enum ExpendModeType
    {
        ExpendMode_SingleClick = 0, //单击模式
        ExpendMode_DoubleClick = 1, //双击模式
        ExpendMode_NoClick = 2,     //不可单击双击
    };

    QEXTNavTreeWidget(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavTreeWidget();

    QList<QEXTNavTreeItem *> allItems() const;
    QList<QEXTNavTreeItem *> rootItems() const;

    QEXTNavTreeItem *activeItem() const;

    bool isItemRightIconVisible() const;
    bool isItemTipVisible() const;
    int itemTipWidth() const;

    bool isITemSeparateVisible() const;
    int itemSeparateHeight() const;
    QColor itemSeparateColor() const;

    bool isItemLineInLeft() const;
    bool isItemLineVisible() const;
    int itemIineWidth() const;
    QColor itemLineColor() const;

    bool isItemTriangleInLeft() const;
    bool ItemTriangleVisible() const;
    int itemTriangleWidth() const;
    QColor itemTriangleColor() const;

    int rootItemIconMargin() const;
    int rootItemMargin() const;
    int rootItemFontSize() const;
    int rootItemHeight() const;
    QColor rootItemBackgroundNormalColor() const;
    QColor rootItemBackgroundSelectedColor() const;
    QColor rootItemBackgroundHoverColor() const;
    QColor rootItemTextNormalColor() const;
    QColor rootItemTextSelectedColor() const;
    QColor rootItemTextHoverColor() const;

    int childItemIconMargin() const;
    int childItemMargin() const;
    int childItemFontSize() const;
    int childItemHeight() const;
    QColor childItemBackgroundNormalColor() const;
    QColor childItemBackgroundSelectedColor() const;
    QColor childItemBackgroundHoverColor() const;
    QColor childItemTextNormalColor() const;
    QColor childItemTextSelectedColor() const;
    QColor childItemTextHoverColor() const;

    ExpendModeType expendMode() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    //设置节点数据
    void setItems(const QList<QEXTNavTreeItem *> &items);
    void setItems(const QString &items);
    //设置选中指定行
    void setCurrentItem(QEXTNavTreeItem *item);
    void setCurrentItem(const QString &text);
    //设置父节点右侧图标是否显示
    void setRightIconVisible(bool rightIconVisible);

    //设置提示信息 是否显示+宽度
    void setTipVisible(bool tipVisible);
    void setTipWidth(int tipWidth);

    //设置行分隔符 是否显示+高度+颜色
    void setSeparateVisible(bool separateVisible);
    void setSeparateHeight(int separateHeight);
    void setSeparateColor(const QColor &separateColor);

    //设置线条 位置+可见+宽度+颜色
    void setLineLeft(bool lineLeft);
    void setLineVisible(bool lineVisible);
    void setLineWidth(int lineWidth);
    void setLineColor(const QColor &lineColor);

    //设置三角形 位置+可见+宽度+颜色
    void setTriangleLeft(bool triangleLeft);
    void setTriangleVisible(bool triangleVisible);
    void setTriangleWidth(int triangleWidth);
    void setTriangleColor(const QColor &triangleColor);

    //设置父节点 图标边距+左侧边距+字体大小+节点高度+颜色集合
    void setParentIconMargin(int parentIconMargin);
    void setParentMargin(int parentMargin);
    void setParentFontSize(int parentFontSize);
    void setParentHeight(int parentHeight);
    void setParentBgNormalColor(const QColor &parentBgNormalColor);
    void setParentBgSelectedColor(const QColor &parentBgSelectedColor);
    void setParentBgHoverColor(const QColor &parentBgHoverColor);
    void setParentTextNormalColor(const QColor &parentTextNormalColor);
    void setParentTextSelectedColor(const QColor &parentTextSelectedColor);
    void setParentTextHoverColor(const QColor &parentTextHoverColor);

    //设置子节点 图标边距+左侧边距+字体大小+节点高度+颜色集合
    void setChildIconMargin(int childIconMargin);
    void setChildMargin(int childMargin);
    void setChildFontSize(int childFontSize);
    void setChildHeight(int childHeight);
    void setChildBgNormalColor(const QColor &childBgNormalColor);
    void setChildBgSelectedColor(const QColor &childBgSelectedColor);
    void setChildBgHoverColor(const QColor &childBgHoverColor);
    void setChildTextNormalColor(const QColor &childTextNormalColor);
    void setChildTextSelectedColor(const QColor &childTextSelectedColor);
    void setChildTextHoverColor(const QColor &childTextHoverColor);

    //设置节点展开模式
    void setExpendMode(const ExpendModeType &expendMode);

signals:
    void itemPressed(QEXTNavTreeItem *item);

private slots:
    void onItemPressed(const QModelIndex &index);

private:
    QString m_itemsString;
    QEXTNavTreeModel *m_model;         //数据模型
    QEXTNavTreeDelegate *m_delegate;   //数据委托
    QList<QEXTNavTreeItem *> m_itemsList;
    QEXTNavTreeItem *m_activeItem;

    bool m_mouseHovered;
    int m_itemIndentation;

    bool m_rightIconVisible; //右侧图标是否显示
    bool m_tipVisible;       //是否显示提示信息
    int m_tipWidth;          //提示信息宽度

    bool m_separateVisible; //是否显示行分隔符
    int m_separateHeight;   //行分隔符高度
    QColor m_separateColor; //行分隔符颜色

    bool m_lineLeft;    //是否显示在左侧
    bool m_lineVisible; //是否显示线条
    int m_lineWidth;    //线条宽度
    QColor m_lineColor; //线条颜色

    bool m_triangleLeft;    //是否显示在左侧
    bool m_triangleVisible; //是否显示三角形
    int m_triangleWidth;    //三角形宽度
    QColor m_triangleColor; //三角形颜色

    int m_parentIconMargin;         //父节点图标边距
    int m_parentMargin;             //父节点边距
    int m_parentFontSize;           //父节点字体大小
    int m_parentHeight;             //父节点高度
    QColor m_parentBkgNormalColor;     //父节点正常背景色
    QColor m_parentBkgSelectedColor;   //父节点选中背景色
    QColor m_parentBkgHoverColor;      //父节点悬停背景色
    QColor m_parentTextNormalColor;   //父节点正常文字颜色
    QColor m_parentTextSelectedColor; //父节点选中文字颜色
    QColor m_parentTextHoverColor;    //父节点悬停文字颜色

    int m_childIconMargin;           //子节点图标边距
    int m_childMargin;               //子节点边距
    int m_childFontSize;             //子节点字体大小
    int m_childHeight;               //子节点高度
    QColor m_childBkgNormalColor;     //子节点正常背景色
    QColor m_childBkgSelectedColor;   //子节点选中背景色
    QColor m_childBkgHoverColor;      //子节点悬停背景色
    QColor m_childTextNormalColor;   //子节点正常文字颜色
    QColor m_childTextSelectedColor; //子节点选中文字颜色
    QColor m_childTextHoverColor;    //子节点悬停文字颜色

    ExpendModeType m_expendMode; //节点展开模式 单击/双击/禁用
};

#endif // QEXTNAVTREEWIDGET_H
