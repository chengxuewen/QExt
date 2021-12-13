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
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTNavigationListItemPrivate)
    QEXT_DECL_PUBLIC(QEXTNavigationListItem)
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
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTNavigationListModelPrivate)
    QEXT_DECL_PUBLIC(QEXTNavigationListModel)
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

    bool m_rightIconVisible;
    bool m_tipVisible;
    int m_tipWidth;

    bool m_separateVisible;
    int m_separateHeight;
    QColor m_separateColor;

    bool m_lineLeft;
    bool m_lineVisible;
    int m_lineWidth;
    QColor m_lineColor;

    bool m_triangleLeft;
    bool m_triangleVisible;
    int m_triangleWidth;
    QColor m_triangleColor;

    int m_parentIconMargin;
    int m_parentMargin;
    int m_parentFontSize;
    int m_parentHeight;
    QColor m_parentBackgroundNormalColor;
    QColor m_parentBackgroundCheckedColor;
    QColor m_parentBackgroundSelectedColor;
    QColor m_parentBackgroundHoverColor;
    QColor m_parentTextNormalColor;
    QColor m_parentTextCheckedColor;
    QColor m_parentTextSelectedColor;
    QColor m_parentTextHoverColor;

    int m_childIconMargin;
    int m_childMargin;
    int m_childFontSize;
    int m_childHeight;
    QColor m_childBackgroundNormalColor;
    QColor m_childBackgroundCheckedColor;
    QColor m_childBackgroundSelectedColor;
    QColor m_childBackgroundHoverColor;
    QColor m_childTextNormalColor;
    QColor m_childTextCheckedColor;
    QColor m_childTextSelectedColor;
    QColor m_childTextHoverColor;

    QColor m_backgroundColor;

    QEXTNavigationListView::ExpendMode m_expendMode;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTNavigationListViewPrivate)
    QEXT_DECL_PUBLIC(QEXTNavigationListView)
};

#endif // _QEXTNAVIGATIONLISTVIEW_P_H
