#ifndef _QEXTNAVIGATIONLISTVIEW_P_H
#define _QEXTNAVIGATIONLISTVIEW_P_H

#include <qextWidgetGlobal.h>
#include <qextNavigationListView.h>

#include <QPointer>
#include <QPainter>
#include <QListView>
#include <QAbstractListModel>
#include <QStyledItemDelegate>

class QEXTNavigationListItem;
class QEXT_WIDGETS_API QEXTNavigationListItemPrivate
{
public:
    explicit QEXTNavigationListItemPrivate(QEXTNavigationListItem *q);
    virtual ~QEXTNavigationListItemPrivate();

    QEXTNavigationListItem * const q_ptr;

    QPixmap m_normalIcon;
    QPixmap m_hoverIcon;
    QPixmap m_checkedIcon;
    QPixmap m_selectedIcon;
    QChar m_fontIcon;
    QString m_text;
    QString m_tip;
    bool m_expand;
    bool m_visiable;
    bool m_enable;
    bool m_checkd;
    QPointer<QEXTNavigationListItem> m_parent;
    QList<QEXTNavigationListItem *> m_childItems;

private:
    QEXT_DECL_PUBLIC(QEXTNavigationListItem)
    QEXT_DECL_DISABLE_COPY(QEXTNavigationListItemPrivate)
};

class QEXTNavListView : public QListView
{
    Q_OBJECT
public:
    explicit QEXTNavListView(QWidget *parent = QEXT_DECL_NULLPTR) : QListView(parent) { }
    ~QEXTNavListView() {}
};

class QEXTNavigationListViewPrivate;
class QEXT_WIDGETS_API QEXTNavListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QEXTNavListDelegate(QEXTNavigationListViewPrivate *navData);
    ~QEXTNavListDelegate();

protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_DECL_OVERRIDE;

private:
    QEXTNavigationListViewPrivate *m_navData;
    QFont m_iconFont;
};


class QEXTNavigationListModel;
class QEXT_WIDGETS_API QEXTNavigationListModelPrivate
{
public:
    explicit QEXTNavigationListModelPrivate(QEXTNavigationListModel *q);
    virtual ~QEXTNavigationListModelPrivate();

    QEXTNavigationListModel * const q_ptr;

    void deleteAllItems();
    void refreshVisiableList();
    void initAllItemsConnection();
    void initItemConnection(QEXTNavigationListItem *item);

    QPointer<QEXTNavigationListItem> m_checkedItem;
    QList<QEXTNavigationListItem *> m_parentItemList;
    QList<QEXTNavigationListItem *> m_visiableItemList;
    QSet<QEXTNavigationListItem *> m_allItemSet;

private:
    QEXT_DECL_PUBLIC(QEXTNavigationListModel)
    QEXT_DECL_DISABLE_COPY(QEXTNavigationListModelPrivate)
};


class QEXTNavigationListView;
class QEXT_WIDGETS_API QEXTNavigationListViewPrivate
{
public:
    explicit QEXTNavigationListViewPrivate(QEXTNavigationListView *q);
    virtual ~QEXTNavigationListViewPrivate();

    QEXTNavigationListView * const q_ptr;

    QFont itemFont() const;

    QStringList m_stringItems;
    QList<QEXTNavigationListItem *> m_items;

    QPointer<QEXTNavigationListItem> m_selectedItem;

    QPointer<QEXTNavigationListModel> m_model;
    QScopedPointer<QEXTNavListView> m_listView;
    QScopedPointer<QEXTNavListDelegate> m_delegate;

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

    int m_parentIconMargin;           //父节点图标边距
    int m_parentMargin;               //父节点边距
    int m_parentFontSize;             //父节点字体大小
    int m_parentHeight;               //父节点高度
    QColor m_parentBackgroundNormalColor;     //父节点正常背景色
    QColor m_parentBackgroundCheckedColor;   //父节点checked背景色
    QColor m_parentBackgroundSelectedColor;   //父节点选中背景色
    QColor m_parentBackgroundHoverColor;      //父节点悬停背景色
    QColor m_parentTextNormalColor;   //父节点正常文字颜色
    QColor m_parentTextCheckedColor; //父节点check文字颜色
    QColor m_parentTextSelectedColor; //父节点选中文字颜色
    QColor m_parentTextHoverColor;    //父节点悬停文字颜色

    int m_childIconMargin;           //子节点图标边距
    int m_childMargin;               //子节点边距
    int m_childFontSize;             //子节点字体大小
    int m_childHeight;               //子节点高度
    QColor m_childBackgroundNormalColor;     //子节点正常背景色
    QColor m_childBackgroundCheckedColor;   //子节点checked背景色
    QColor m_childBackgroundSelectedColor;   //子节点选中背景色
    QColor m_childBackgroundHoverColor;      //子节点悬停背景色
    QColor m_childTextNormalColor;   //子节点正常文字颜色
    QColor m_childTextCheckedColor; //子节点checked文字颜色
    QColor m_childTextSelectedColor; //子节点选中文字颜色
    QColor m_childTextHoverColor;    //子节点悬停文字颜色

    QColor m_backgroundColor;

    QEXTNavigationListView::ExpendMode m_expendMode; //节点展开模式 单击/双击/禁用

private:
    QEXT_DECL_PUBLIC(QEXTNavigationListView)
    QEXT_DECL_DISABLE_COPY(QEXTNavigationListViewPrivate)
};

#endif // _QEXTNAVIGATIONLISTVIEW_P_H
