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

#ifndef _QEXTNAVIGATIONLISTVIEW_H
#define _QEXTNAVIGATIONLISTVIEW_H

#include <qextWidgetGlobal.h>

#include <QScopedPointer>
#include <QStringList>
#include <QListView>
#include <QList>

class QExtNavigationListItemPrivate;
class QEXT_WIDGETS_API QExtNavigationListItem : public QObject
{
    Q_OBJECT

public:
    explicit QExtNavigationListItem(QExtNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QExtNavigationListItem(const QString &text, QExtNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QExtNavigationListItem(const QString &text, const QPixmap &icon, QExtNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QExtNavigationListItem(const QString &text, const QPixmap &icon, bool expand, QExtNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QExtNavigationListItem(const QString &text, const QString &tip, const QPixmap &icon, QExtNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QExtNavigationListItem(const QString &text, const QString &tip, const QPixmap &icon, bool expand, QExtNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QExtNavigationListItem(const QString &text, const QChar &fontChar, QExtNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QExtNavigationListItem(const QString &text, const QChar &fontChar, bool expand, QExtNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QExtNavigationListItem(const QString &text, const QString &tip, const QChar &fontChar, QExtNavigationListItem *parent = QEXT_DECL_NULLPTR);
    QExtNavigationListItem(const QString &text, const QString &tip, const QChar &fontChar, bool expand, QExtNavigationListItem *parent = QEXT_DECL_NULLPTR);
    ~QExtNavigationListItem();

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

    bool isVisible() const;
    void setVisible(const bool &visiable);

    bool isEnabled() const;
    void setEnable(const bool &enable);

    Qt::CheckState checkState() const;
    bool isChecked() const;
    bool setChecked(bool check);

    bool isLastVisibleItem() const;
    bool isChildItem() const;
    bool isParentItem() const;
    QExtNavigationListItem *parentItem() const;
    bool setParentItem(QExtNavigationListItem *parent);

    int childItemsCount() const;
    int visiableChildItemsCount() const;
    QList<QExtNavigationListItem *> childItems() const;
    QList<QExtNavigationListItem *> visiableChildItems() const;

signals:
    void itemAboutToDestroyed(QExtNavigationListItem *item);
    void iconChanged(QExtNavigationListItem *item);
    void fontIconChanged(QExtNavigationListItem *item);
    void textChanged(QExtNavigationListItem *item);
    void tipChanged(QExtNavigationListItem *item);
    void expandChanged(QExtNavigationListItem *item);
    void enableChanged(QExtNavigationListItem *item);
    void checkChanged(QExtNavigationListItem *item);

    void visiableAboutToBeChanged(QExtNavigationListItem *item);
    void visiableChanged(QExtNavigationListItem *item);

    void childItemAboutToBeInserted(QExtNavigationListItem *item, QExtNavigationListItem *parent);
    void childItemInserted(QExtNavigationListItem *item, QExtNavigationListItem *parent);

    void childItemAboutToBeRemoved(QExtNavigationListItem *item, QExtNavigationListItem *parent);
    void childItemRemoved(QExtNavigationListItem *item, QExtNavigationListItem *parent);

protected Q_SLOTS:
    void onChildItemAboutToBeDestroyed(QExtNavigationListItem *item);

protected:
    QScopedPointer<QExtNavigationListItemPrivate> dd_ptr;

private:
    friend class QEXTNavigationListModel;
    QEXT_DECL_DISABLE_COPY_MOVE(QExtNavigationListItem)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtNavigationListItem)
};


class QEXTNavigationListModelPrivate;
class QEXT_WIDGETS_API QEXTNavigationListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QEXTNavigationListModel(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavigationListModel();

    QExtNavigationListItem *checkedItem() const;
    QList<QExtNavigationListItem *> allItems() const;
    QList<QExtNavigationListItem *> parentItems() const;
    QList<QExtNavigationListItem *> visiableItems() const;

public slots:
    void setItems(const QStringList &items);
    void setItems(const QList<QExtNavigationListItem *> &items);
    void expandCollapseItem(const QModelIndex &index);

signals:
    void checkedItemChanged(QExtNavigationListItem *item);

protected slots:
    void onItemAboutToDestroyed(QExtNavigationListItem *item);
    void onItemChanged(QExtNavigationListItem *item);
    void onItemEnableChanged(QExtNavigationListItem *item);
    void onItemExpandChanged(QExtNavigationListItem *item);
    void onItemCheckChanged(QExtNavigationListItem *item);
    void onItemVisibleAboutToBeChanged(QExtNavigationListItem *item);
    void onItemVisibleChanged(QExtNavigationListItem *item);
    void onChildItemAboutToBeInserted(QExtNavigationListItem *item, QExtNavigationListItem *parent);
    void onChildItemInserted(QExtNavigationListItem *item, QExtNavigationListItem *parent);
    void onChildItemAboutToBeRemoved(QExtNavigationListItem *item, QExtNavigationListItem *parent);
    void onChildItemRemoved(QExtNavigationListItem *item, QExtNavigationListItem *parent);

protected:
    int rowCount(const QModelIndex &parent) const QEXT_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const QEXT_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const QEXT_DECL_OVERRIDE;

    QScopedPointer<QEXTNavigationListModelPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTNavigationListModel)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTNavigationListModel)
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
    enum ExpendMode
    {
        ExpendMode_SingleClick = 0,
        ExpendMode_DoubleClick = 1,
        ExpendMode_NoClick = 2,
    };
    Q_ENUMS(ExpendMode)

    explicit QEXTNavigationListView(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTNavigationListView();

    QListView *view() const;
    QEXTNavigationListModel *model() const;

    QExtNavigationListItem * selectedItem() const;
    QExtNavigationListItem * checkedItem() const;
    QList<QExtNavigationListItem *> allItems() const;
    QList<QExtNavigationListItem *> parentItems() const;
    QList<QExtNavigationListItem *> visiableItems() const;

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

    QList<QExtNavigationListItem *> setItems(const QString &items);
    QList<QExtNavigationListItem *> setItems(const QStringList &items);
    void setItems(const QList<QExtNavigationListItem *> &items);

    bool setCurrentRow(int row);
    bool setSelectedItem(QExtNavigationListItem *item);
    void setItemRightIconVisible(bool visible);

    void setItemTipVisible(bool visible);
    void setItemTipWidth(int width);

    void setItemSeparateVisible(bool visible);
    void setItemSeparateHeight(int height);
    void setItemSeparateColor(const QColor &color);

    void setItemLineLeft(bool inLeft);
    void setItemLineVisible(bool visible);
    void setItemLineWidth(int width);
    void setItemLineColor(const QColor &color);

    void setItemTriangleLeft(bool inLeft);
    void setItemTriangleVisible(bool visible);
    void setItemTriangleWidth(int width);
    void setItemTriangleColor(const QColor &color);

    void setBackgroundColor(const QColor &color);

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

    void setExpendMode(const ExpendMode &mode);

signals:
    void itemPressed(QExtNavigationListItem *item);
    void checkedItemChanged(QExtNavigationListItem *item);
    void selectedItemChanged(QExtNavigationListItem *item);

protected:
    void paintEvent(QPaintEvent *event) QEXT_DECL_OVERRIDE;

    QScopedPointer<QEXTNavigationListViewPrivate> dd_ptr;

private Q_SLOTS:
    void onItemPressed(const QModelIndex &index);

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTNavigationListView)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTNavigationListView)
};

#endif // _QEXTNAVIGATIONLISTVIEW_H
