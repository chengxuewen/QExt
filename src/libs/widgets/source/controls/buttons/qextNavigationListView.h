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
    explicit QExtNavigationListItem(QExtNavigationListItem *parent = QEXT_NULLPTR);
    QExtNavigationListItem(const QString &text, QExtNavigationListItem *parent = QEXT_NULLPTR);
    QExtNavigationListItem(const QString &text, const QPixmap &icon, QExtNavigationListItem *parent = QEXT_NULLPTR);
    QExtNavigationListItem(const QString &text, const QPixmap &icon, bool expand, QExtNavigationListItem *parent = QEXT_NULLPTR);
    QExtNavigationListItem(const QString &text, const QString &tip, const QPixmap &icon, QExtNavigationListItem *parent = QEXT_NULLPTR);
    QExtNavigationListItem(const QString &text, const QString &tip, const QPixmap &icon, bool expand, QExtNavigationListItem *parent = QEXT_NULLPTR);
    QExtNavigationListItem(const QString &text, const QChar &fontChar, QExtNavigationListItem *parent = QEXT_NULLPTR);
    QExtNavigationListItem(const QString &text, const QChar &fontChar, bool expand, QExtNavigationListItem *parent = QEXT_NULLPTR);
    QExtNavigationListItem(const QString &text, const QString &tip, const QChar &fontChar, QExtNavigationListItem *parent = QEXT_NULLPTR);
    QExtNavigationListItem(const QString &text, const QString &tip, const QChar &fontChar, bool expand, QExtNavigationListItem *parent = QEXT_NULLPTR);
    ~QExtNavigationListItem() QEXT_OVERRIDE;

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

Q_SIGNALS:
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
    friend class QExtNavigationListModel;
    QEXT_DISABLE_COPY_MOVE(QExtNavigationListItem)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtNavigationListItem)
};


class QExtNavigationListModelPrivate;
class QEXT_WIDGETS_API QExtNavigationListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QExtNavigationListModel(QObject *parent = QEXT_NULLPTR);
    ~QExtNavigationListModel() QEXT_OVERRIDE;

    QExtNavigationListItem *checkedItem() const;
    QList<QExtNavigationListItem *> allItems() const;
    QList<QExtNavigationListItem *> parentItems() const;
    QList<QExtNavigationListItem *> visiableItems() const;

public Q_SLOTS:
    void setItems(const QStringList &items);
    void setItems(const QList<QExtNavigationListItem *> &items);
    void expandCollapseItem(const QModelIndex &index);

Q_SIGNALS:
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
    int rowCount(const QModelIndex &parent) const QEXT_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const QEXT_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const QEXT_OVERRIDE;

    QScopedPointer<QExtNavigationListModelPrivate> dd_ptr;

private:
    QEXT_DISABLE_COPY_MOVE(QExtNavigationListModel)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtNavigationListModel)
};


class QExtNavigationListViewPrivate;
class QEXT_WIDGETS_API QExtNavigationListView : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int itemTipWidth READ itemTipWidth WRITE setItemTipWidth NOTIFY itemTipWidthChanged)
    Q_PROPERTY(bool isItemTipVisible READ isItemTipVisible WRITE setItemTipVisible NOTIFY itemTipVisibleChanged)

    Q_PROPERTY(QColor itemSeparateColor READ itemSeparateColor WRITE setItemSeparateColor NOTIFY itemSeparateColorChanged)
    Q_PROPERTY(int itemSeparateHeight READ itemSeparateHeight WRITE setItemSeparateHeight NOTIFY itemSeparateHeightChanged)
    Q_PROPERTY(bool isItemSeparateVisible READ isItemSeparateVisible WRITE setItemSeparateVisible NOTIFY itemSeparateVisibleChanged)

    Q_PROPERTY(int itemLineWidth READ itemLineWidth WRITE setItemLineWidth NOTIFY itemLineWidthChanged)
    Q_PROPERTY(QColor itemLineColor READ itemLineColor WRITE setItemLineColor NOTIFY itemLineColorChanged)
    Q_PROPERTY(bool isItemLineVisible READ isItemLineVisible WRITE setItemLineVisible NOTIFY itemLineVisibleChanged)
    Q_PROPERTY(bool isItemLineLeftAlign READ isItemLineLeftAlign WRITE setItemLineLeftAlign NOTIFY itemLineLeftAlignChanged)

    Q_PROPERTY(int itemTriangleWidth READ itemTriangleWidth WRITE setItemTriangleWidth NOTIFY itemTriangleWidthChanged)
    Q_PROPERTY(QColor itemTriangleColor READ itemTriangleColor WRITE setItemTriangleColor NOTIFY itemTriangleColorChanged)
    Q_PROPERTY(bool isItemTriangleVisible READ isItemTriangleVisible WRITE setItemTriangleVisible NOTIFY itemTriangleVisibleChanged)
    Q_PROPERTY(bool isItemTriangleLeftAlign READ isItemTriangleLeftAlign WRITE setItemTriangleLeftAlign NOTIFY itemTriangleLeftAlignChanged)

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

    Q_PROPERTY(ExpendMode expendMode READ expendMode WRITE setExpendMode NOTIFY expendModeChanged)

public:
    enum ExpendMode
    {
        ExpendMode_SingleClick = 0,
        ExpendMode_DoubleClick,
        ExpendMode_NoClick,
    };
    Q_ENUM(ExpendMode)

    enum ItemState
    {
        ItemState_Selected = 0,
        ItemState_Checked,
        ItemState_Hovered,
        ItemState_Normal
    };
    Q_ENUM(ItemState)
    QEXT_STATIC_CONSTANT(int, ItemStateNum = 4);

    explicit QExtNavigationListView(QWidget *parent = QEXT_NULLPTR);
    ~QExtNavigationListView() QEXT_OVERRIDE;

    QListView *view() const;
    QExtNavigationListModel *model() const;

    QExtNavigationListItem * selectedItem() const;
    QExtNavigationListItem * checkedItem() const;
    QList<QExtNavigationListItem *> allItems() const;
    QList<QExtNavigationListItem *> parentItems() const;
    QList<QExtNavigationListItem *> visiableItems() const;

    int itemTipWidth() const;
    bool isItemTipVisible() const;

    int itemSeparateHeight() const;
    QColor itemSeparateColor() const;
    bool isItemSeparateVisible() const;

    int itemLineWidth() const;
    QColor itemLineColor() const;
    bool isItemLineVisible() const;
    bool isItemLineLeftAlign() const;

    int itemTriangleWidth() const;
    QColor itemTriangleColor() const;
    bool isItemTriangleVisible() const;
    bool isItemTriangleLeftAlign() const;

    QColor backgroundColor() const;
    QColor itemTextColor(bool isParent, ItemState state) const;
    QColor itemBackgroundColor(bool isParent, ItemState state) const;

    int itemHeight(bool isParent) const;
    int itemMargin(bool isParent) const;
    int itemFontSize(bool isParent) const;
    int itemIconMargin(bool isParent) const;

    ExpendMode expendMode() const;

    QSize sizeHint() const QEXT_OVERRIDE;
    QSize minimumSizeHint() const QEXT_OVERRIDE;

Q_SIGNALS:
    void itemTipWidthChanged(int width);
    void itemTipVisibleChanged(bool visible);

    void itemSeparateHeightChanged(int height);
    void itemSeparateVisibleChanged(bool visible);
    void itemSeparateColorChanged(const QColor &color);

    void itemLineWidthChanged(int width);
    void itemLineVisibleChanged(bool visible);
    void itemLineLeftAlignChanged(bool leftAlign);
    void itemLineColorChanged(const QColor &color);

    void itemTriangleWidthChanged(int width);
    void itemTriangleVisibleChanged(bool visible);
    void itemTriangleLeftAlignChanged(bool leftAlign);
    void itemTriangleColorChanged(const QColor &color);

    void itemMarginChanged(bool isParent, int margin);
    void itemFontSizeChanged(bool isParent, int size);
    void itemHeightChanged(bool isParent, int height);
    void itemIconMarginChanged(bool isParent, int margin);

    void backgroundColorChanged(const QColor &color);
    void itemTextColorChanged(bool isParent, ItemState state, const QColor &color);
    void itemBackgroundColorChanged(bool isParent, ItemState state, const QColor &color);

    void expendModeChanged(ExpendMode mode);

public Q_SLOTS:
    void setModel(QExtNavigationListModel *model);

    QList<QExtNavigationListItem *> setItems(const QString &items);
    QList<QExtNavigationListItem *> setItems(const QStringList &items);
    void setItems(const QList<QExtNavigationListItem *> &items);

    bool setCurrentRow(int row);
    bool setSelectedItem(QExtNavigationListItem *item);

    void setItemTipWidth(int width);
    void setItemTipVisible(bool visible);

    void setItemSeparateHeight(int height);
    void setItemSeparateVisible(bool visible);
    void setItemSeparateColor(const QColor &color);

    void setItemLineWidth(int width);
    void setItemLineVisible(bool visible);
    void setItemLineLeftAlign(bool leftAlign);
    void setItemLineColor(const QColor &color);

    void setItemTriangleWidth(int width);
    void setItemTriangleVisible(bool visible);
    void setItemTriangleLeftAlign(bool leftAlign);
    void setItemTriangleColor(const QColor &color);

    void setItemMargin(bool isParent, int margin);
    void setItemFontSize(bool isParent, int size);
    void setItemHeight(bool isParent, int height);
    void setItemIconMargin(bool isParent, int margin);

    void setBackgroundColor(const QColor &color);
    void setItemTextColor(bool isParent, ItemState state, const QColor &color);
    void setItemBackgroundColor(bool isParent, ItemState state, const QColor &color);

    void setExpendMode(ExpendMode mode);

Q_SIGNALS:
    void itemPressed(QExtNavigationListItem *item);
    void checkedItemChanged(QExtNavigationListItem *item);
    void selectedItemChanged(QExtNavigationListItem *item);

protected:
    void paintEvent(QPaintEvent *event) QEXT_OVERRIDE;

    QScopedPointer<QExtNavigationListViewPrivate> dd_ptr;

private Q_SLOTS:
    void onItemPressed(const QModelIndex &index);

private:
    QEXT_DISABLE_COPY_MOVE(QExtNavigationListView)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtNavigationListView)
};

#endif // _QEXTNAVIGATIONLISTVIEW_H
