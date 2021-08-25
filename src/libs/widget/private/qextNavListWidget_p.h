#ifndef QEXTNAVLISTVIEW_P_H
#define QEXTNAVLISTVIEW_P_H

#include <qextWidgetGlobal.h>
#include <qextNavListWidget.h>

#include <qextobject_p.h>

#include <QPointer>
#include <QPainter>
#include <QListView>
#include <QAbstractListModel>
#include <QStyledItemDelegate>

class QEXTNavListWidgetItem;
class QEXT_WIDGET_API QEXTNavListWidgetItemPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTNavListWidgetItemPrivate(QEXTNavListWidgetItem *qq);
    virtual ~QEXTNavListWidgetItemPrivate();

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
    QPointer<QEXTNavListWidgetItem> m_parent;
    QList<QEXTNavListWidgetItem *> m_childItems;

private:
    QEXT_DECL_PUBLIC(QEXTNavListWidgetItem)
    QEXT_DISABLE_COPY_MOVE(QEXTNavListWidgetItemPrivate)
};

class QEXTNavListView : public QListView
{
    Q_OBJECT
public:
    explicit QEXTNavListView(QWidget *parent = QEXT_DECL_NULLPTR) : QListView(parent) { }
    ~QEXTNavListView() {}
};

class QEXTNavListWidgetPrivate;
class QEXT_WIDGET_API QEXTNavListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QEXTNavListDelegate(QEXTNavListWidgetPrivate *navData);
    ~QEXTNavListDelegate();

protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_DECL_OVERRIDE;

private:
    QEXTNavListWidgetPrivate *m_navData;
    QFont m_iconFont;
};


class QEXTNavListModel;
class QEXT_WIDGET_API QEXTNavListModelPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTNavListModelPrivate(QEXTNavListModel *qq);
    ~QEXTNavListModelPrivate();

    void deleteAllItems();
    void refreshVisiableList();
    void initAllItemsConnection();
    void initItemConnection(QEXTNavListWidgetItem *item);

    QPointer<QEXTNavListWidgetItem> m_checkedItem;
    QList<QEXTNavListWidgetItem *> m_parentItemList;
    QList<QEXTNavListWidgetItem *> m_visiableItemList;
    QSet<QEXTNavListWidgetItem *> m_allItemSet;

private:
    QEXT_DECL_PUBLIC(QEXTNavListModel)
    QEXT_DISABLE_COPY_MOVE(QEXTNavListModelPrivate)
};


class QEXTNavListWidget;
class QEXT_WIDGET_API QEXTNavListWidgetPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTNavListWidgetPrivate(QEXTNavListWidget *qq);
    ~QEXTNavListWidgetPrivate();

    QFont itemFont() const;

    QStringList m_stringItems;
    QList<QEXTNavListWidgetItem *> m_items;

    QPointer<QEXTNavListWidgetItem> m_selectedItem;

    QPointer<QEXTNavListModel> m_model;
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

    QEXTNavListWidget::ExpendMode m_expendMode; //节点展开模式 单击/双击/禁用

private:
    QEXT_DECL_PUBLIC(QEXTNavListWidget)
    QEXT_DISABLE_COPY_MOVE(QEXTNavListWidgetPrivate)
};

#endif // QEXTNAVLISTVIEW_P_H
