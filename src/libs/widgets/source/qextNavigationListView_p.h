/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2018 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTNAVIGATIONLISTVIEW_P_H
#define _QEXTNAVIGATIONLISTVIEW_P_H

#include <qextNavigationListView.h>

#include <QPointer>
#include <QPainter>
#include <QListView>
#include <QAbstractListModel>
#include <QStyledItemDelegate>

class QExtNavigationListItem;
class QEXT_WIDGETS_API QExtNavigationListItemPrivate
{
public:
    explicit QExtNavigationListItemPrivate(QExtNavigationListItem *q);
    virtual ~QExtNavigationListItemPrivate();

    QExtNavigationListItem * const q_ptr;

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
    QPointer<QExtNavigationListItem> m_parent;
    QList<QExtNavigationListItem *> m_childItems;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtNavigationListItemPrivate)
    QEXT_DECL_PUBLIC(QExtNavigationListItem)
};

class QEXTNavListView : public QListView
{
    Q_OBJECT
public:
    explicit QEXTNavListView(QWidget *parent = QEXT_NULLPTR) : QListView(parent) { }
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
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

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
    void refreshVisibleList();
    void initAllItemsConnection();
    void initItemConnection(QExtNavigationListItem *item);

    QPointer<QExtNavigationListItem> m_checkedItem;
    QList<QExtNavigationListItem *> m_parentItemList;
    QList<QExtNavigationListItem *> m_visiableItemList;
    QSet<QExtNavigationListItem *> m_allItemSet;

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
    QList<QExtNavigationListItem *> m_items;

    QPointer<QExtNavigationListItem> m_selectedItem;

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
