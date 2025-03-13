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
#include <qextOptional.h>

#include <QPointer>
#include <QPainter>
#include <QListView>
#include <QPushButton>
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
    QEXT_DISABLE_COPY_MOVE(QExtNavigationListItemPrivate)
    QEXT_DECL_PUBLIC(QExtNavigationListItem)
};

class QExtNavListView : public QListView
{
    Q_OBJECT
public:
    explicit QExtNavListView(QWidget *parent = QEXT_NULLPTR) : QListView(parent) { }
    ~QExtNavListView() QEXT_OVERRIDE {}
};

class QExtNavigationListViewPrivate;
class QEXT_WIDGETS_API QExtNavListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QExtNavListDelegate(QExtNavigationListViewPrivate *navData);
    ~QExtNavListDelegate() QEXT_OVERRIDE {}

protected:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;

private:
    QFont m_iconFont;
    QExtNavigationListViewPrivate *m_navData;
    QExtNavigationListView * const m_navListView;
};


class QExtNavigationListModel;
class QEXT_WIDGETS_API QExtNavigationListModelPrivate
{
public:
    explicit QExtNavigationListModelPrivate(QExtNavigationListModel *q);
    virtual ~QExtNavigationListModelPrivate();

    QExtNavigationListModel * const q_ptr;

    void deleteAllItems();
    void refreshVisibleList();
    void initAllItemsConnection();
    void initItemConnection(QExtNavigationListItem *item);

    QSet<QExtNavigationListItem *> m_allItemSet;
    QPointer<QExtNavigationListItem> m_checkedItem;
    QList<QExtNavigationListItem *> m_parentItemList;
    QList<QExtNavigationListItem *> m_visiableItemList;

private:
    QEXT_DISABLE_COPY_MOVE(QExtNavigationListModelPrivate)
    QEXT_DECL_PUBLIC(QExtNavigationListModel)
};


class QExtNavigationListView;
class QEXT_WIDGETS_API QExtNavigationListViewPrivate
{
public:
    explicit QExtNavigationListViewPrivate(QExtNavigationListView *q);
    virtual ~QExtNavigationListViewPrivate();

    const QFont &buttonFont() const;
    const QPalette &buttonPalette() const;
    const QPalette &listViewPalette() const;

    QExtNavigationListView * const q_ptr;

    QScopedPointer<QPushButton> m_pushButton;

    QStringList m_stringItems;
    QList<QExtNavigationListItem *> m_items;

    QPointer<QExtNavigationListItem> m_selectedItem;

    QPointer<QExtNavigationListModel> m_model;
    QScopedPointer<QExtNavListView> m_listView;
    QScopedPointer<QExtNavListDelegate> m_delegate;

    int m_itemLineTipWidth;
    bool m_itenLineTipVisible;

    int m_itemSeparateHeight;
    bool m_itemSeparateVisible;
    QExtOptional<QColor> m_itemSeparateColor;

    int m_itemLineWidth;
    bool m_itemLineVisible;
    bool m_itemLineLeftAlign;
    QExtOptional<QColor> m_itemLineColor;

    int m_itemTriangleWidth;
    bool m_itemTriangleVisible;
    bool m_itemTriangleLeftAlign;
    QExtOptional<QColor> m_itemTriangleColor;

    int m_itemMargins[2];
    int m_itemHeights[2];
    int m_itemFontSizes[2];
    int m_itemIconMargins[2];

    QExtOptional<QColor> m_backgroundColor;
    QExtOptional<QColor> m_itemTextColors[2][QExtNavigationListView::ItemStateNum];
    QExtOptional<QColor> m_itemBackgroundColors[2][QExtNavigationListView::ItemStateNum];

    QExtNavigationListView::ExpendMode m_expendMode;

private:
    QEXT_DISABLE_COPY_MOVE(QExtNavigationListViewPrivate)
    QEXT_DECL_PUBLIC(QExtNavigationListView)
};

#endif // _QEXTNAVIGATIONLISTVIEW_P_H
