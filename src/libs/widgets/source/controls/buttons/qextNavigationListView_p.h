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

    QPixmap mHoverIcon;
    QPixmap mNormalIcon;
    QPixmap mCheckedIcon;
    QPixmap mSelectedIcon;

    QString mTip;
    QString mText;
    QChar mFontIcon;

    bool mExpand;
    bool mCheckd;
    bool mEnable;
    bool mVisiable;
    QVariant mUserData;

    QPointer<QExtNavigationListItem> mParent;
    QList<QExtNavigationListItem *> mChildItems;

private:
    QEXT_DISABLE_COPY_MOVE(QExtNavigationListItemPrivate)
    QEXT_DECL_PUBLIC(QExtNavigationListItem)
};

class QExtNavListView : public QListView
{
    Q_OBJECT
    QEXT_DISABLE_COPY_MOVE(QExtNavListView)
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
    QEXT_DISABLE_COPY_MOVE(QExtNavListDelegate)
    QFont mIconFont;
    QExtNavigationListViewPrivate *mNavData;
    QExtNavigationListView * const mNavListView;
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

    QSet<QExtNavigationListItem *> mAllItemSet;
    QPointer<QExtNavigationListItem> mCheckedItem;
    QList<QExtNavigationListItem *> mParentItemList;
    QList<QExtNavigationListItem *> mVisiableItemList;

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

    QScopedPointer<QPushButton> mPushButton;

    QStringList mStringItems;
    QList<QExtNavigationListItem *> mItems;

    QPointer<QExtNavigationListItem> mSelectedItem;

    QPointer<QExtNavigationListModel> mModel;
    QScopedPointer<QExtNavListView> mListView;
    QScopedPointer<QExtNavListDelegate> mDelegate;

    int mItemLineTipWidth;
    bool mItenLineTipVisible;

    int mItemSeparateHeight;
    bool mItemSeparateVisible;
    QExtOptional<QColor> mItemSeparateColor;

    int mItemLineWidth;
    bool mItemLineVisible;
    bool mItemLineLeftAlign;
    QExtOptional<QColor> mItemLineColor;

    int mItemTriangleWidth;
    bool mItemTriangleVisible;
    bool mItemTriangleLeftAlign;
    QExtOptional<QColor> mItemTriangleColor;

    int mItemMargins[2];
    int mItemHeights[2];
    int mItemFontSizes[2];
    int mItemIconMargins[2];

    QExtOptional<QColor> mBackgroundColor;
    QExtOptional<QColor> mItemTextColors[2][QExtNavigationListView::ItemStateNum];
    QExtOptional<QColor> mItemBackgroundColors[2][QExtNavigationListView::ItemStateNum];

    QExtNavigationListView::ExpendMode mExpendMode;

private:
    QEXT_DISABLE_COPY_MOVE(QExtNavigationListViewPrivate)
    QEXT_DECL_PUBLIC(QExtNavigationListView)
};

#endif // _QEXTNAVIGATIONLISTVIEW_P_H
