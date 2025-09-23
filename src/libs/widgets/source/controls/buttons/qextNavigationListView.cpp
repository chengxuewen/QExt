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

#include <private/qextNavigationListView_p.h>

#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include <QFontDatabase>
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#   include <QMutableStringListIterator>
#endif

QExtNavigationListItemPrivate::QExtNavigationListItemPrivate(QExtNavigationListItem *q)
    : q_ptr(q)
{
    mEnable = true;
    mCheckd = false;
    mExpand = false;
    mVisiable = true;
}

QExtNavigationListItemPrivate::~QExtNavigationListItemPrivate()
{
    mChildItems.clear();
}

QExtNavigationListItem::QExtNavigationListItem(QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->mText = text;
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QPixmap &icon,
                                               QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->mText = text;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QPixmap &icon,
                                               bool expand, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->mText = text;
    d->mExpand = expand;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QString &tip,
                                               const QPixmap &icon, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->mText = text;
    d->mTip = tip;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QString &tip,
                                               const QPixmap &icon, bool expand, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->mText = text;
    d->mTip = tip;
    d->mExpand = expand;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QChar &fontChar,
                                               QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->mText = text;
    d->mFontIcon = fontChar;
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QChar &fontChar,
                                               bool expand, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->mText = text;
    d->mFontIcon = fontChar;
    d->mExpand = expand;
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QString &tip,
                                               const QChar &fontChar, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->mText = text;
    d->mTip = tip;
    d->mFontIcon = fontChar;
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QString &tip,
                                               const QChar &fontChar, bool expand, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->mText = text;
    d->mTip = tip;
    d->mFontIcon = fontChar;
    d->mExpand = expand;
    this->setParentItem(parent);
}

QExtNavigationListItem::~QExtNavigationListItem()
{
    this->setChecked(false);
    emit this->itemAboutToDestroyed(this);
}

QPixmap QExtNavigationListItem::normalIcon() const
{
    Q_D(const QExtNavigationListItem);
    return d->mNormalIcon;
}

QPixmap QExtNavigationListItem::hoverIcon() const
{
    Q_D(const QExtNavigationListItem);
    return d->mHoverIcon;
}

QPixmap QExtNavigationListItem::checkedIcon() const
{
    Q_D(const QExtNavigationListItem);
    return d->mCheckedIcon;
}

QPixmap QExtNavigationListItem::selectedIcon() const
{
    Q_D(const QExtNavigationListItem);
    return d->mSelectedIcon;
}

void QExtNavigationListItem::setIcon(const QPixmap &icon)
{
    this->setNormalIcon(icon);
    this->setHoverIcon(icon);
    this->setCheckedIcon(icon);
    this->setSelectedIcon(icon);
}

void QExtNavigationListItem::setNormalIcon(const QPixmap &icon)
{
    Q_D(QExtNavigationListItem);
    d->mNormalIcon = icon;
    emit this->iconChanged(this);
}

void QExtNavigationListItem::setHoverIcon(const QPixmap &icon)
{
    Q_D(QExtNavigationListItem);
    d->mHoverIcon = icon;
    emit this->iconChanged(this);
}

void QExtNavigationListItem::setCheckedIcon(const QPixmap &icon)
{
    Q_D(QExtNavigationListItem);
    d->mCheckedIcon = icon;
    emit this->iconChanged(this);
}

void QExtNavigationListItem::setSelectedIcon(const QPixmap &icon)
{
    Q_D(QExtNavigationListItem);
    d->mSelectedIcon = icon;
    emit this->iconChanged(this);
}

QVariant QExtNavigationListItem::userData() const
{
    Q_D(const QExtNavigationListItem);
    return d->mUserData;
}

void QExtNavigationListItem::setUserData(const QVariant &data)
{
    Q_D(QExtNavigationListItem);
    if (data != d->mUserData)
    {
        d->mUserData = data;
        emit this->userDataChanged(data);
    }
}

QChar QExtNavigationListItem::fontIcon() const
{
    Q_D(const QExtNavigationListItem);
    return d->mFontIcon;
}

void QExtNavigationListItem::setFontIcon(const QChar &ch)
{
    Q_D(QExtNavigationListItem);
    if (ch != d->mFontIcon)
    {
        d->mFontIcon = ch;
        emit this->fontIconChanged(this);
    }
}

QString QExtNavigationListItem::text() const
{
    Q_D(const QExtNavigationListItem);
    return d->mText;
}

void QExtNavigationListItem::setText(const QString &text)
{
    Q_D(QExtNavigationListItem);
    if (text != d->mText)
    {
        d->mText = text;
        emit this->textChanged(this);
    }
}

QString QExtNavigationListItem::tip() const
{
    Q_D(const QExtNavigationListItem);
    return d->mTip;
}

void QExtNavigationListItem::setTip(const QString &tip)
{
    Q_D(QExtNavigationListItem);
    if (tip != d->mTip)
    {
        d->mTip = tip;
        emit this->tipChanged(this);
    }
}

bool QExtNavigationListItem::isExpand() const
{
    Q_D(const QExtNavigationListItem);
    return d->mExpand;
}

void QExtNavigationListItem::setExpand(const bool &expand)
{
    Q_D(QExtNavigationListItem);
    if (expand != d->mExpand)
    {
        d->mExpand = expand;
        emit this->expandChanged(this);
    }
}

bool QExtNavigationListItem::isVisible() const
{
    Q_D(const QExtNavigationListItem);
    return d->mVisiable;
}

void QExtNavigationListItem::setVisible(const bool &visiable)
{
    Q_D(QExtNavigationListItem);
    if (visiable != d->mVisiable)
    {
        if (!visiable)
        {
            QList<QExtNavigationListItem *>::const_iterator iter;
            for (iter = d->mChildItems.begin(); iter != d->mChildItems.end(); ++iter)
            {
                (*iter)->setChecked(false);
            }
        }
        emit this->visiableAboutToBeChanged(this);
        d->mVisiable = visiable;
        emit this->visiableChanged(this);
    }
}

bool QExtNavigationListItem::isEnabled() const
{
    Q_D(const QExtNavigationListItem);
    return d->mEnable;
}

void QExtNavigationListItem::setEnable(const bool &enable)
{
    Q_D(QExtNavigationListItem);
    if (enable != d->mEnable)
    {
        d->mEnable = enable;
        emit this->enableChanged(this);
    }
}

Qt::CheckState QExtNavigationListItem::checkState() const
{
    Q_D(const QExtNavigationListItem);
    if (this->isParentItem())
    {
        QList<QExtNavigationListItem *>::const_iterator iter;
        for (iter = d->mChildItems.begin(); iter != d->mChildItems.end(); ++iter)
        {
            if ((*iter)->isChecked())
            {
                return Qt::PartiallyChecked;
            }
        }
        return Qt::Unchecked;
    }
    else
    {
        return d->mCheckd ? Qt::Checked : Qt::Unchecked;
    }
}

bool QExtNavigationListItem::isChecked() const
{
    return Qt::Checked == this->checkState();
}

bool QExtNavigationListItem::setChecked(bool check)
{
    Q_D(QExtNavigationListItem);
    if (!this->isVisible() && check)
    {
        qWarning() << "QExtNavigationListItem::setChecked(): item not visiable, can not set check";
        return false;
    }
    if (!this->isEnabled() && check)
    {
        qWarning() << "QExtNavigationListItem::setChecked(): item not enabled, can not set check";
        return false;
    }
    if (this->isParentItem())
    {
        qWarning() << "QExtNavigationListItem::setChecked(): item is parent, can not set check";
        return false;
    }
    if (check != d->mCheckd)
    {
        d->mCheckd = check;
        emit this->checkChanged(this);
    }
    return true;
}

bool QExtNavigationListItem::isLastVisibleItem() const
{
    Q_D(const QExtNavigationListItem);
    if (!d->mParent.isNull() && d->mVisiable)
    {
        return this == d->mParent->visiableChildItems().last();
    }
    return false;
}

bool QExtNavigationListItem::isChildItem() const
{
    Q_D(const QExtNavigationListItem);
    return !d->mParent.isNull();
}

bool QExtNavigationListItem::isParentItem() const
{
    Q_D(const QExtNavigationListItem);
    return d->mParent.isNull();
}

QExtNavigationListItem *QExtNavigationListItem::parentItem() const
{
    Q_D(const QExtNavigationListItem);
    return d->mParent.data();
}

bool QExtNavigationListItem::setParentItem(QExtNavigationListItem *parent)
{
    Q_D(QExtNavigationListItem);
    if (this == parent)
    {
        qWarning() << "QExtNavigationListItem::setParentItem(): parent can not equal to item self";
        return false;
    }
    if (!d->mChildItems.isEmpty())
    {
        qWarning() << "QExtNavigationListItem::setParentItem(): current item is parent item, can not set parent";
        return false;
    }
    if (d->mParent.data() != parent)
    {
        QExtNavigationListItem *oldParent = d->mParent.data();
        d->mParent = parent;

        if (oldParent)
        {
            emit oldParent->childItemAboutToBeRemoved(this, oldParent);
            oldParent->d_func()->mChildItems.removeOne(this);
            this->disconnect(oldParent);
            emit oldParent->childItemRemoved(this, oldParent);
        }

        if (parent)
        {
            emit parent->childItemAboutToBeInserted(this, parent);
            parent->d_func()->mChildItems.append(this);
            connect(this, SIGNAL(itemAboutToDestroyed(QExtNavigationListItem*)),
                    parent, SLOT(onChildItemAboutToBeDestroyed(QExtNavigationListItem*)));
            emit parent->childItemInserted(this, parent);
        }

        return true;
    }
    return false;
}

int QExtNavigationListItem::childItemsCount() const
{
    Q_D(const QExtNavigationListItem);
    return d->mChildItems.count();
}

int QExtNavigationListItem::visiableChildItemsCount() const
{
    return this->visiableChildItems().count();
}

QList<QExtNavigationListItem *> QExtNavigationListItem::childItems() const
{
    Q_D(const QExtNavigationListItem);
    return d->mChildItems;
}

QList<QExtNavigationListItem *> QExtNavigationListItem::visiableChildItems() const
{
    Q_D(const QExtNavigationListItem);
    QList<QExtNavigationListItem *> result;
    QList<QExtNavigationListItem *>::const_iterator iter;
    for (iter = d->mChildItems.begin(); iter != d->mChildItems.end(); ++iter)
    {
        if ((*iter)->isVisible())
        {
            result.append(*iter);
        }
    }
    return result;
}

void QExtNavigationListItem::onChildItemAboutToBeDestroyed(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListItem);
    if (item && d->mChildItems.contains(item))
    {
        emit this->childItemAboutToBeRemoved(item, this);
        d->mChildItems.removeOne(item);
        emit this->childItemRemoved(item, this);
    }
}



QExtNavListDelegate::QExtNavListDelegate(QExtNavigationListViewPrivate *navData)
    : QStyledItemDelegate()
    , mNavData(navData)
    , mNavListView(navData->q_ptr)
{

    QFontDatabase fontDb;
    if (!fontDb.families().contains("FontAwesome"))
    {
        Q_INIT_RESOURCE(qextWidgets);
        int fontId = fontDb.addApplicationFont(":/QExtWidgets/font/fontawesome-webfont.ttf");
        QStringList fontName = fontDb.applicationFontFamilies(fontId);
        if (fontName.count() == 0)
        {
            qDebug() << "load fontawesome-webfont.ttf error";
        }
    }

    if (fontDb.families().contains("FontAwesome"))
    {
        mIconFont = QFont("FontAwesome");
#if (QT_VERSION >= QT_VERSION_CHECK(4, 8, 0))
        mIconFont.setHintingPreference(QFont::PreferNoHinting);
#endif
    }
}

QSize QExtNavListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QExtNavigationListItem *item = (QExtNavigationListItem *)index.data(Qt::UserRole).toLongLong();

    QSize size(50, mNavListView->itemHeight(item->isParentItem()));
    return size;
}

void QExtNavListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QPalette &buttonPalette = mNavData->buttonPalette();
    const QPalette &listViewPalette = mNavData->listViewPalette();
    painter->setRenderHint(QPainter::Antialiasing);
    QExtNavigationListItem *item = (QExtNavigationListItem *)index.data(Qt::UserRole).toLongLong();

    QRect optionRect = option.rect;
    int x = optionRect.x();
    int y = optionRect.y();
    int width = optionRect.width();
    int height = optionRect.height();


    bool parent = item->isParentItem();
    bool hasChildItems = (0 != item->visiableChildItemsCount());
    bool checked = item->isChecked();
    bool enabled = item->isEnabled();
    bool parentEnabled = item->parentItem() ? item->parentItem()->isEnabled() : enabled;

    int fontSize = mNavListView->itemFontSize(parent);
    QPixmap icon;
    QColor bgColor, textColor, tipBgColor, tipTextColor, iconColor;
    if (checked)
    {
        bgColor = mNavListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Checked);
        textColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Checked);
        tipBgColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Checked);
        tipTextColor = mNavListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Checked);
        iconColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Checked);
        icon = item->checkedIcon();
    }
    else if (option.state & QStyle::State_Selected && enabled && parentEnabled)
    {
        bgColor = mNavListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Selected);
        textColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Selected);
        tipBgColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Selected);
        tipTextColor = mNavListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Selected);
        iconColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Selected);
        icon = item->selectedIcon();
    }
    else if (option.state & QStyle::State_MouseOver && enabled && parentEnabled)
    {
        bgColor = mNavListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Hovered);
        textColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Hovered);
        tipBgColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Checked);
        tipTextColor = mNavListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Checked);
        iconColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Hovered);
        icon = item->hoverIcon();
    }
    else
    {
        bgColor = mNavListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Normal);
        textColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Normal);
        tipBgColor = mNavListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Checked);
        tipTextColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Checked);
        iconColor = mNavListView->itemTextColor(parent, QExtNavigationListView::ItemState_Normal);
        icon = item->normalIcon();
    }
    if (!enabled || !parentEnabled)
    {
        bgColor.setAlpha(100);
        textColor.setAlpha(100);
        tipBgColor.setAlpha(100);
        tipTextColor.setAlpha(100);
    }

    painter->fillRect(optionRect, bgColor);

    int lineWidth = mNavData->mItemLineWidth;
    if (!parent && mNavData->mItemLineVisible && lineWidth > 0)
    {
        if (checked)
        {
            float offset = (float)lineWidth / 2;

            QPointF pointTop(x, y + offset);
            QPointF pointBottom(x, height + y - offset);
            if (!mNavData->mItemLineLeftAlign)
            {
                pointTop.setX(width);
                pointBottom.setX(width);
            }

            painter->setPen(QPen(mNavListView->itemLineColor(), lineWidth));
            painter->drawLine(pointTop, pointBottom);
        }
    }

    int triangleWidth = mNavData->mItemTriangleWidth;
    if (!parent && mNavData->mItemTriangleVisible && triangleWidth > 0)
    {
        if (checked)
        {
            QFont font = mIconFont;
            font.setPixelSize(fontSize + triangleWidth);
            painter->setFont(font);
            painter->setPen(mNavListView->itemTriangleColor());
            if (mNavData->mItemTriangleLeftAlign)
            {
                painter->drawText(optionRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf0da));
            }
            else
            {
                painter->drawText(optionRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf0d9));
            }
        }
    }

    if (mNavData->mItemSeparateVisible)
    {
        if (item->isParentItem() || (item->isChildItem() && item->isLastVisibleItem()))
        {
            painter->setPen(QPen(mNavListView->itemSeparateColor(), mNavData->mItemSeparateHeight));
            painter->drawLine(QPointF(x, y + height), QPointF(x + width, y + height));
        }
    }

    QString text = item->text();
    if (!text.isEmpty())
    {
        int margin = mNavListView->itemMargin(true);
        if (item->isChildItem())
        {
            margin = mNavListView->itemMargin(false);
            fontSize = mNavListView->itemFontSize(false);
        }

        QRect textRect = optionRect;
        textRect.setWidth(width - margin);
        textRect.setX(x + margin);

        QFont font = mNavData->buttonFont();
        font.setPixelSize(fontSize);
        painter->setFont(font);
        painter->setPen(textColor);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }

    QString tip = item->tip();
    if (mNavData->mItenLineTipVisible && !tip.isEmpty())
    {
        if (tip.toInt() > 0)
        {
            tip = tip.toInt() > 999 ? "999+" : tip;
        }
        else if (tip.length() > 2)
        {
            tip = tip.left(2) + " .";
        }

        int radius = height / 4;
        QRect tipRect = optionRect;
        tipRect.setHeight(radius * 2);
        tipRect.moveCenter(optionRect.center());
        tipRect.setLeft(optionRect.right() - mNavData->mItemLineTipWidth - 5);
        tipRect.setRight(optionRect.right() - 5);

        QFont font = mNavData->buttonFont();
        font.setPixelSize(fontSize - 2);
        painter->setFont(font);

        painter->setPen(Qt::NoPen);
        painter->setBrush(tipBgColor);
        painter->drawRoundedRect(tipRect, radius, radius);

        painter->setPen(tipTextColor);
        painter->setBrush(Qt::NoBrush);
        painter->drawText(tipRect, Qt::AlignCenter, tip);
    }

    QRect iconRect = optionRect;
    iconRect.setLeft(mNavListView->itemIconMargin(parent));

    QFont font = mIconFont;
    font.setPixelSize(fontSize);
    painter->setFont(font);
    painter->setPen(textColor);

    if (!icon.isNull())
    {
        QRect pixmapRect =  QRect(iconRect.x(), iconRect.y() + (iconRect.height() - fontSize) / 2, fontSize, fontSize);
        QPixmap pixmap = icon.scaled(iconRect.width(), iconRect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap(pixmapRect, pixmap, pixmap.rect());
    }
    else if (!item->fontIcon().isNull())
    {
        painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, item->fontIcon());
    }
    else if (parent && hasChildItems)
    {
        if (!item->isExpand())
        {
            painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf067));
        }
        else
        {
            painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf068));
        }
    }
}



QExtNavigationListModelPrivate::QExtNavigationListModelPrivate(QExtNavigationListModel *q)
    : q_ptr(q)
{

}

QExtNavigationListModelPrivate::~QExtNavigationListModelPrivate()
{
    this->deleteAllItems();
    mParentItemList.clear();
    mVisiableItemList.clear();
}

void QExtNavigationListModelPrivate::deleteAllItems()
{
    QSet<QExtNavigationListItem *>::iterator iter;
    for (iter = mAllItemSet.begin(); iter != mAllItemSet.end(); ++iter)
    {
        (*iter)->disconnect();
        (*iter)->deleteLater();
    }
    mAllItemSet.clear();
}

void QExtNavigationListModelPrivate::refreshVisibleList()
{
    mVisiableItemList.clear();
    QList<QExtNavigationListItem *>::iterator iter;
    for (iter = mParentItemList.begin(); iter != mParentItemList.end(); ++iter)
    {
        if ((*iter)->isVisible())
        {
            mVisiableItemList.append(*iter);
            if ((*iter)->isExpand())
            {
                QList<QExtNavigationListItem *> childItems = (*iter)->visiableChildItems();
                if (!childItems.isEmpty())
                {
                    mVisiableItemList.append(childItems);
                }
            }
        }
    }
}

void QExtNavigationListModelPrivate::initAllItemsConnection()
{
    QSet<QExtNavigationListItem *>::iterator iter;
    for (iter = mAllItemSet.begin(); iter != mAllItemSet.end(); ++iter)
    {
        QExtNavigationListItem *item = *iter;
        this->initItemConnection(item);
    }
}

void QExtNavigationListModelPrivate::initItemConnection(QExtNavigationListItem *item)
{
    Q_Q(QExtNavigationListModel);
    item->disconnect(q);
    QObject::connect(item, SIGNAL(itemAboutToDestroyed(QExtNavigationListItem*)),
                     q, SLOT(onItemAboutToDestroyed(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(iconChanged(QExtNavigationListItem*)),
                     q, SLOT(onItemChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(fontIconChanged(QExtNavigationListItem*)),
                     q, SLOT(onItemChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(textChanged(QExtNavigationListItem*)),
                     q, SLOT(onItemChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(tipChanged(QExtNavigationListItem*)),
                     q, SLOT(onItemChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(enableChanged(QExtNavigationListItem*)),
                     q, SLOT(onItemChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(expandChanged(QExtNavigationListItem*)),
                     q, SLOT(onItemExpandChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(checkChanged(QExtNavigationListItem*)),
                     q, SLOT(onItemCheckChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(visiableAboutToBeChanged(QExtNavigationListItem*)),
                     q, SLOT(onItemVisibleAboutToBeChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(visiableChanged(QExtNavigationListItem*)),
                     q, SLOT(onItemVisibleChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(childItemAboutToBeInserted(QExtNavigationListItem*,QExtNavigationListItem*)),
                     q, SLOT(onChildItemAboutToBeInserted(QExtNavigationListItem*,QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(childItemInserted(QExtNavigationListItem*,QExtNavigationListItem*)),
                     q, SLOT(onChildItemInserted(QExtNavigationListItem*,QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(childItemAboutToBeRemoved(QExtNavigationListItem*,QExtNavigationListItem*)),
                     q, SLOT(onChildItemAboutToBeRemoved(QExtNavigationListItem*,QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(childItemRemoved(QExtNavigationListItem*,QExtNavigationListItem*)),
                     q, SLOT(onChildItemRemoved(QExtNavigationListItem*,QExtNavigationListItem*)));
}


QExtNavigationListModel::QExtNavigationListModel(QObject *parent)
    : QAbstractListModel(parent), dd_ptr(new QExtNavigationListModelPrivate(this))
{

}

QExtNavigationListModel::~QExtNavigationListModel()
{

}

QExtNavigationListItem *QExtNavigationListModel::checkedItem() const
{
    Q_D(const QExtNavigationListModel);
    return d->mCheckedItem.data();
}

QList<QExtNavigationListItem *> QExtNavigationListModel::allItems() const
{
    Q_D(const QExtNavigationListModel);
    return d->mAllItemSet.values();
}

QList<QExtNavigationListItem *> QExtNavigationListModel::parentItems() const
{
    Q_D(const QExtNavigationListModel);
    return d->mParentItemList;
}

QList<QExtNavigationListItem *> QExtNavigationListModel::visiableItems() const
{
    Q_D(const QExtNavigationListModel);
    return d->mVisiableItemList;
}

int QExtNavigationListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const QExtNavigationListModel);
    return d->mVisiableItemList.size();
}

QVariant QExtNavigationListModel::data(const QModelIndex &index, int role) const
{
    Q_D(const QExtNavigationListModel);
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= d->mVisiableItemList.size() || index.row() < 0)
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return d->mVisiableItemList.at(index.row())->text();
    }
    if (role == Qt::BackgroundRole)
    {
        return QColor(Qt::red);
    }
    else if (role == Qt::UserRole)
    {
        return (quint64)(d->mVisiableItemList.at(index.row()));
    }

    return QVariant();
}

Qt::ItemFlags QExtNavigationListModel::flags(const QModelIndex &index) const
{
    Q_D(const QExtNavigationListModel);
    if (index.isValid())
    {
        int row = index.row();
        if (row >= 0 && row < d->mVisiableItemList.size())
        {
            QExtNavigationListItem *item = d->mVisiableItemList.at(row);
            QExtNavigationListItem *parentItem = item->parentItem();
            if (!item->isEnabled() || (parentItem && !parentItem->isEnabled()))
            {
                return item->isParentItem() ? Qt::ItemIsEnabled : Qt::NoItemFlags;
            }
        }
    }
    return QAbstractListModel::flags(index);
}

void QExtNavigationListModel::setItems(const QStringList &items)
{
    if (!items.isEmpty())
    {
        this->beginResetModel();

        bool ok;
        QStringList itemStringList = items;
        QList<QExtNavigationListItem *> parentItemList;
        QMutableStringListIterator iter(itemStringList);
        while (iter.hasNext())
        {
            QString item = iter.next();
            QStringList list = item.split("|");
            if (list.count() < 5)
            {
                qWarning() << QString("QExtNavigationListModel::setItems(): item string %1 invalid").arg(item);
                iter.remove();
                continue;
            }
            QString text = list.at(0);
            QString parentText = list.at(1);
            QString expand = list.at(2);
            QString tip = list.at(3);
            QString icon = list.at(4);
            icon = icon.replace("0x", "");
            if (parentText.isEmpty())
            {
                QExtNavigationListItem *parentItem = new QExtNavigationListItem;
                parentItemList.append(parentItem);
                parentItem->setExpand(expand.toInt());
                parentItem->setText(text);
                parentItem->setTip(tip);
                if (!icon.isEmpty())
                {
                    parentItem->setFontIcon(QChar(icon.toInt(&ok, 16)));
                }
                iter.remove();

                QMutableStringListIterator childIter(itemStringList);
                while (childIter.hasNext())
                {
                    QString childItem = childIter.next();
                    QStringList childList = childItem.split("|");
                    if (childList.count() < 5)
                    {
                        qWarning() << QString("QExtNavigationListModel::setItems(): item string %1 invalid").arg(item);
                        childIter.remove();
                        continue;
                    }
                    QString childText = childList.at(0);
                    QString childParentText = childList.at(1);
                    QString childTip = childList.at(3);
                    QString childIcon = childList.at(4);
                    childIcon = childIcon.replace("0x", "");
                    if (text == childParentText)
                    {
                        QExtNavigationListItem *childItem = new QExtNavigationListItem;
                        childItem->setText(childText);
                        childItem->setTip(childTip);
                        if (!childIcon.isEmpty())
                        {
                            childItem->setFontIcon(QChar(childIcon.toInt(&ok, 16)));
                        }
                        childItem->setParentItem(parentItem);
                        childIter.remove();
                    }
                }
            }
        }

        QMutableStringListIterator checkIter(itemStringList);
        while (checkIter.hasNext())
        {
            QString item = checkIter.next();
            QStringList list = item.split("|");
            if (list.count() < 5)
            {
                qWarning() << QString("QExtNavigationListModel::setItems(): item string %1 invalid").arg(item);
                checkIter.remove();
                continue;
            }
            QString text = list.at(0);
            QString parentText = list.at(1);
            QString expand = list.at(2);
            QString tip = list.at(3);
            QString icon = list.at(4);
            icon = icon.replace("0x", "");
            QExtNavigationListItem *parentItem = new QExtNavigationListItem;
            parentItemList.append(parentItem);
            parentItem->setExpand(expand.toInt());
            parentItem->setText(text);
            parentItem->setTip(tip);
            if (!icon.isEmpty())
            {
                parentItem->setFontIcon(QChar(icon.toInt(&ok, 16)));
            }
            checkIter.remove();
            qWarning() << QString("QExtNavigationListModel::setItems(): item string %1 parent %2 not exist").
                          arg(item).arg(parentText);
        }
        this->setItems(parentItemList);

        this->endResetModel();
    }
}


void QExtNavigationListModel::setItems(const QList<QExtNavigationListItem *> &items)
{
    Q_D(QExtNavigationListModel);
    if (!items.isEmpty())
    {
        this->beginResetModel();

        QSet<QExtNavigationListItem *> cacheItemSet;
        d->mVisiableItemList.clear();
        d->mParentItemList.clear();

        QList<QExtNavigationListItem *>::const_iterator iter;
        for (iter = items.begin(); iter != items.end(); ++iter)
        {
            QExtNavigationListItem *item = *iter;
            if (item->isParentItem())
            {
                cacheItemSet.insert(item);
                d->mParentItemList.append(item);
                if (d->mAllItemSet.contains(item))
                {
                    d->mAllItemSet.remove(item);
                }

                QList<QExtNavigationListItem *> childItems = item->childItems();
                QList<QExtNavigationListItem *>::iterator childIter;
                for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                {
                    QExtNavigationListItem *childItem = *childIter;
                    cacheItemSet.insert(childItem);
                    if (d->mAllItemSet.contains(childItem))
                    {
                        d->mAllItemSet.remove(childItem);
                    }
                }
            }
        }

        d->deleteAllItems();
        d->mAllItemSet = cacheItemSet;
        d->refreshVisibleList();
        d->initAllItemsConnection();

        this->endResetModel();
    }
}

void QExtNavigationListModel::expandCollapseItem(const QModelIndex &index)
{
    Q_D(QExtNavigationListModel);
    QExtNavigationListItem *item = d->mVisiableItemList.at(index.row());
    if (0 != item->visiableChildItemsCount())
    {
        item->setExpand(!item->isExpand());
    }
}

void QExtNavigationListModel::onItemAboutToDestroyed(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListModel);
    if (item->isParentItem())
    {
        d->mAllItemSet.remove(item);
        d->mParentItemList.removeOne(item);
        if (item->isVisible())
        {
            int row = d->mVisiableItemList.indexOf(item);
            int count = item->visiableChildItemsCount();
            this->beginRemoveRows(QModelIndex(), row, row + count);
            d->mVisiableItemList.removeOne(item);

            QList<QExtNavigationListItem *>::iterator iter;
            QList<QExtNavigationListItem *> childItems = item->childItems();
            for (iter = childItems.begin(); iter != childItems.end(); ++iter)
            {
                QExtNavigationListItem *childItem = *iter;
                if (childItem->parentItem() == item)
                {
                    d->mAllItemSet.remove(childItem);
                    d->mVisiableItemList.removeOne(childItem);
                    childItem->disconnect();
                    childItem->deleteLater();
                }
            }

            this->endRemoveRows();
        }
    }
}

void QExtNavigationListModel::onItemChanged(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListModel);
    int row = d->mVisiableItemList.indexOf(item);
    QModelIndex index = this->index(row, 0);
    emit this->dataChanged(index, index);
}

void QExtNavigationListModel::onItemEnableChanged(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListModel);
    if (item->isVisible())
    {
        int row = d->mVisiableItemList.indexOf(item);
        int count = item->isParentItem() ? item->visiableChildItemsCount() : 0;
        QModelIndex index1 = this->index(row, 0);
        QModelIndex index2 = this->index(row + count, 0);
        emit this->dataChanged(index1, index2);
    }
}

void QExtNavigationListModel::onItemExpandChanged(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListModel);
    QList<QExtNavigationListItem *> visiableItems = item->visiableChildItems();
    int count = visiableItems.count();
    int index = d->mVisiableItemList.indexOf(item);
    if (item->isExpand())
    {
        this->beginInsertRows(QModelIndex(), index + 1, index + count);
        for (int i = 0; i < count; ++i)
        {
            d->mVisiableItemList.insert(index + 1 + i, visiableItems.at(i));
        }
        this->endInsertRows();
    }
    else
    {
        this->beginRemoveRows(QModelIndex(), index + 1, index + count);
        for (int i = 0; i < count; ++i)
        {
            d->mVisiableItemList.removeAt(index + 1);
        }
        this->endRemoveRows();
    }
}

void QExtNavigationListModel::onItemCheckChanged(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListModel);
    int row = d->mVisiableItemList.indexOf(item);
    QModelIndex index = this->index(row, 0);
    emit this->dataChanged(index, index);

    if (item->isChecked())
    {
        if (item != d->mCheckedItem.data())
        {
            QExtNavigationListItem *oldCheckedItem = d->mCheckedItem.data();
            d->mCheckedItem = item;
            if (oldCheckedItem)
            {
                oldCheckedItem->setChecked(false);
            }
            emit this->checkedItemChanged(item);
        }
    }
    else
    {
        if (item == d->mCheckedItem.data())
        {
            emit this->checkedItemChanged((QExtNavigationListItem *)QEXT_NULLPTR);
        }
    }
}

void QExtNavigationListModel::onItemVisibleAboutToBeChanged(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListModel);
    if (item->isVisible())
    {
        int row = d->mVisiableItemList.indexOf(item);
        int count = item->isExpand() ? item->visiableChildItemsCount() : 0;
        this->beginRemoveRows(QModelIndex(), row, row + count);
    }
    else
    {
        QList<QExtNavigationListItem *> visiableChildItems = item->visiableChildItems();
        int visiableChildcount = (item->isExpand() && item->isParentItem() && item->isVisible()) ? visiableChildItems.size() : 0;
        int row = 0;
        bool located = false;
        QList<QExtNavigationListItem *>::iterator iter;
        for (iter = d->mParentItemList.begin(); iter != d->mParentItemList.end(); ++iter)
        {
            if (located)
            {
                break;
            }
            if ((*iter)->isVisible())
            {
                if (item == *iter)
                {
                    break;
                }
                row++;
                if ((*iter)->isExpand())
                {
                    QList<QExtNavigationListItem *>::iterator childIter;
                    QList<QExtNavigationListItem *> childItems = (*iter)->childItems();
                    for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                    {
                        if (item == *childIter && (*iter)->isVisible())
                        {
                            located = true;
                            break;
                        }
                        row++;
                    }
                }
            }
        }
        this->beginInsertRows(QModelIndex(), row, row + visiableChildcount);
    }
}

void QExtNavigationListModel::onItemVisibleChanged(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListModel);
    if (item->isVisible())
    {
        int row = 0;
        bool located = false;
        QList<QExtNavigationListItem *>::iterator iter;
        for (iter = d->mParentItemList.begin(); iter != d->mParentItemList.end(); ++iter)
        {
            if (located)
            {
                break;
            }
            if ((*iter)->isVisible())
            {
                QList<QExtNavigationListItem *> childItems = (*iter)->childItems();
                if (item == *iter)
                {
                    d->mVisiableItemList.insert(row++, *iter);
                    if ((*iter)->isExpand())
                    {
                        QList<QExtNavigationListItem *>::iterator childIter;
                        for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                        {
                            if ((*childIter)->isVisible())
                            {
                                d->mVisiableItemList.insert(row++, *childIter);
                            }
                        }
                        break;
                    }
                }
                row++;

                if ((*iter)->isExpand())
                {
                    QList<QExtNavigationListItem *>::iterator childIter;
                    for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                    {
                        if (item == *childIter && (*childIter)->isVisible())
                        {
                            d->mVisiableItemList.insert(row++, *childIter);
                            located = true;
                            break;
                        }
                        row++;
                    }
                }
            }
        }
        this->endInsertRows();
    }
    else
    {
        int row = d->mVisiableItemList.indexOf(item);
        int count = (item->isExpand() && item->isParentItem()) ? item->visiableChildItemsCount() : 0;
        d->mVisiableItemList.removeAt(row);
        for (int i = 0; i < count; ++i)
        {
            d->mVisiableItemList.removeAt(row);
        }
        this->endRemoveRows();
    }
}

void QExtNavigationListModel::onChildItemAboutToBeInserted(QExtNavigationListItem *item, QExtNavigationListItem *parent)
{
    Q_D(QExtNavigationListModel);
    if (item->isVisible() && parent->isVisible())
    {
        int index = d->mVisiableItemList.indexOf(parent);
        int row = parent->visiableChildItemsCount() + 1;
        this->beginInsertRows(QModelIndex(), index + row + 1, index + row + 1);
    }
}

void QExtNavigationListModel::onChildItemInserted(QExtNavigationListItem *item, QExtNavigationListItem *parent)
{
    Q_D(QExtNavigationListModel);
    if (item->isVisible() && parent->isVisible())
    {
        int index = d->mVisiableItemList.indexOf(parent);
        int row = parent->visiableChildItemsCount();
        d->mVisiableItemList.insert(index + row + 1, item);
        this->endInsertRows();
    }
}

void QExtNavigationListModel::onChildItemAboutToBeRemoved(QExtNavigationListItem *item, QExtNavigationListItem *parent)
{
    Q_D(QExtNavigationListModel);
    if (d->mVisiableItemList.contains(item))
    {
        int row = d->mVisiableItemList.indexOf(parent);
        this->beginRemoveRows(QModelIndex(), row, row);
    }
}

void QExtNavigationListModel::onChildItemRemoved(QExtNavigationListItem *item, QExtNavigationListItem *parent)
{
    Q_D(QExtNavigationListModel);
    d->mAllItemSet.remove(item);
    if (d->mVisiableItemList.contains(item))
    {
        d->mVisiableItemList.removeOne(item);
        this->endRemoveRows();
    }
}



QExtNavigationListViewPrivate::QExtNavigationListViewPrivate(QExtNavigationListView *q)
    : q_ptr(q)
    , mPushButton(new QPushButton(q))
{
    mPushButton->setVisible(false);

    mItemLineTipWidth = 40;
    mItenLineTipVisible = true;

    mItemSeparateHeight = 1;
    mItemSeparateVisible = true;

    mItemLineWidth = 6;
    mItemLineVisible = true;
    mItemLineLeftAlign = true;

    mItemTriangleWidth = 6;
    mItemTriangleVisible = true;
    mItemTriangleLeftAlign = false;

    mItemMargins[false] = 35;
    mItemHeights[false] = 30;
    mItemFontSizes[false] = 12;
    mItemIconMargins[false] = 15;
    mItemMargins[true] = 30;
    mItemHeights[true] = 35;
    mItemFontSizes[true] = 12;
    mItemIconMargins[true] = 10;

    mExpendMode = QExtNavigationListView::ExpendMode_SingleClick;

    mDelegate.reset(new QExtNavListDelegate(this));
    mListView.reset(new QExtNavListView);
    mListView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mListView->setMouseTracking(true);
    mListView->setAutoFillBackground(true);
    mListView->setItemDelegate(mDelegate.data());
}

QExtNavigationListViewPrivate::~QExtNavigationListViewPrivate()
{
    if (!mModel.isNull())
    {
        mModel->deleteLater();
    }
}

const QFont &QExtNavigationListViewPrivate::buttonFont() const
{
    return mPushButton->font();
}

const QPalette &QExtNavigationListViewPrivate::buttonPalette() const
{
    return mPushButton->palette();
}

const QPalette &QExtNavigationListViewPrivate::listViewPalette() const
{
    return q_ptr->palette();
}


QExtNavigationListView::QExtNavigationListView(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtNavigationListViewPrivate(this))
{
    qRegisterMetaType<QExtNavigationListView::ExpendMode>("QExtNavigationListView::ExpendMode");
    qRegisterMetaType<QExtNavigationListView::ItemState>("QExtNavigationListView::ItemState");
    Q_D(QExtNavigationListView);
    QVBoxLayout *layout = new QVBoxLayout;
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    layout->setMargin(0);
#endif
    layout->addWidget(d->mListView.data());
    this->setLayout(layout);
    this->setModel(new QExtNavigationListModel);
    connect(d->mListView.data(), SIGNAL(pressed(QModelIndex)), this, SLOT(onItemPressed(QModelIndex)));
}

QExtNavigationListView::~QExtNavigationListView()
{

}

QListView *QExtNavigationListView::view() const
{
    Q_D(const QExtNavigationListView);
    return d->mListView.data();
}

QExtNavigationListModel *QExtNavigationListView::model() const
{
    Q_D(const QExtNavigationListView);
    return d->mModel.data();
}

QExtNavigationListItem *QExtNavigationListView::selectedItem() const
{
    Q_D(const QExtNavigationListView);
    return d->mSelectedItem.data();
}

QExtNavigationListItem *QExtNavigationListView::checkedItem() const
{
    Q_D(const QExtNavigationListView);
    return d->mModel->checkedItem();
}

QList<QExtNavigationListItem *> QExtNavigationListView::allItems() const
{
    Q_D(const QExtNavigationListView);
    return d->mModel->allItems();
}

QList<QExtNavigationListItem *> QExtNavigationListView::parentItems() const
{
    Q_D(const QExtNavigationListView);
    return d->mModel->parentItems();
}

QList<QExtNavigationListItem *> QExtNavigationListView::visiableItems() const
{
    Q_D(const QExtNavigationListView);
    return d->mModel->visiableItems();
}

void QExtNavigationListView::onItemPressed(const QModelIndex &index)
{
    QExtNavigationListItem *item = (QExtNavigationListItem *)index.data(Qt::UserRole).toLongLong();
    if (item)
    {
        if (item->isChildItem())
        {
            this->setSelectedItem(item);
        }
        emit this->itemPressed(item);
    }
}

bool QExtNavigationListView::isItemTipVisible() const
{
    Q_D(const QExtNavigationListView);
    return d->mItenLineTipVisible;
}

int QExtNavigationListView::itemTipWidth() const
{
    Q_D(const QExtNavigationListView);
    return d->mItemLineTipWidth;
}

bool QExtNavigationListView::isItemSeparateVisible() const
{
    Q_D(const QExtNavigationListView);
    return d->mItemSeparateVisible;
}

int QExtNavigationListView::itemSeparateHeight() const
{
    Q_D(const QExtNavigationListView);
    return d->mItemSeparateHeight;
}

QColor QExtNavigationListView::itemSeparateColor() const
{
    Q_D(const QExtNavigationListView);
    if (d->mItemSeparateColor.has_value())
    {
        return d->mItemSeparateColor.value();
    }
    else
    {
        return d->buttonPalette().color(QPalette::Active, QPalette::ButtonText);
    }
}

bool QExtNavigationListView::isItemLineLeftAlign() const
{
    Q_D(const QExtNavigationListView);
    return d->mItemLineLeftAlign;
}

bool QExtNavigationListView::isItemLineVisible() const
{
    Q_D(const QExtNavigationListView);
    return d->mItemLineVisible;
}

int QExtNavigationListView::itemLineWidth() const
{
    Q_D(const QExtNavigationListView);
    return d->mItemLineWidth;
}

QColor QExtNavigationListView::itemLineColor() const
{
    Q_D(const QExtNavigationListView);
    if (d->mItemLineColor.has_value())
    {
        return d->mItemLineColor.value();
    }
    else
    {
        return this->itemTextColor(false, ItemState_Normal);
    }
}

bool QExtNavigationListView::isItemTriangleLeftAlign() const
{
    Q_D(const QExtNavigationListView);
    return d->mItemTriangleLeftAlign;
}

bool QExtNavigationListView::isItemTriangleVisible() const
{
    Q_D(const QExtNavigationListView);
    return d->mItemTriangleVisible;
}

int QExtNavigationListView::itemTriangleWidth() const
{
    Q_D(const QExtNavigationListView);
    return d->mItemTriangleWidth;
}

QColor QExtNavigationListView::itemTriangleColor() const
{
    Q_D(const QExtNavigationListView);
    if (d->mItemTriangleColor.has_value())
    {
        return d->mItemTriangleColor.value();
    }
    else
    {
        return this->palette().color(QPalette::Active, QPalette::Window);
    }
}

QColor QExtNavigationListView::backgroundColor() const
{
    Q_D(const QExtNavigationListView);
    if (d->mBackgroundColor.has_value())
    {
        return d->mBackgroundColor.value();
    }
    else
    {
        return this->palette().color(QPalette::Active, QPalette::Window);
    }
}

QColor QExtNavigationListView::itemTextColor(bool isParent, ItemState state) const
{
    Q_D(const QExtNavigationListView);
    if (d->mItemTextColors[isParent][state].has_value())
    {
        return d->mItemTextColors[isParent][state].value();
    }
    else
    {
        const QPalette &buttonPalette = d->buttonPalette();
        switch (state)
        {
        case ItemState_Selected:
        {
            return isParent ? buttonPalette.color(QPalette::Active, QPalette::BrightText)
                            : buttonPalette.color(QPalette::Active, QPalette::ButtonText);
        }
        case ItemState_Checked:
        {
            return isParent ? buttonPalette.color(QPalette::Active, QPalette::BrightText)
                            : buttonPalette.color(QPalette::Active, QPalette::ButtonText);
        }
        case ItemState_Hovered:
        {
            return buttonPalette.color(QPalette::Active, QPalette::ButtonText);
        }
        case ItemState_Normal:
        {
            return buttonPalette.color(QPalette::Active, QPalette::ButtonText);
        }
        default:
            break;
        }
    }
    return QColor();
}

QColor QExtNavigationListView::itemBackgroundColor(bool isParent, ItemState state) const
{
    Q_D(const QExtNavigationListView);
    if (d->mItemBackgroundColors[isParent][state].has_value())
    {
        return d->mItemBackgroundColors[isParent][state].value();
    }
    else
    {
        const QPalette &buttonPalette = d->buttonPalette();
        const QPalette &listViewPalette = d->listViewPalette();
        switch (state)
        {
        case ItemState_Selected:
        {
            return isParent ? buttonPalette.color(QPalette::Active, QPalette::ButtonText)
                            : buttonPalette.color(QPalette::Active, QPalette::ButtonText);
        }
        case ItemState_Checked:
        {
            QColor color = isParent ? buttonPalette.color(QPalette::Active, QPalette::ButtonText)
                                    : buttonPalette.color(QPalette::Active, QPalette::ButtonText);
            color.setAlphaF(0.2);
            return color;
        }
        case ItemState_Hovered:
        {
            QColor color = isParent ? buttonPalette.color(QPalette::Active, QPalette::ButtonText)
                                    : buttonPalette.color(QPalette::Active, QPalette::ButtonText);
            color.setAlphaF(0.2);
            return color;
        }
        case ItemState_Normal:
        {
            if (isParent)
            {
                QColor color = buttonPalette.color(QPalette::Active, QPalette::ButtonText);
                color.setAlphaF(0.2);
                return color;
            }
            else
            {
                return listViewPalette.color(QPalette::Active, QPalette::Window);
            }
        }
        default:
            break;
        }
    }
    return QColor();
}

int QExtNavigationListView::itemHeight(bool isParent) const
{
    Q_D(const QExtNavigationListView);
    return d->mItemHeights[isParent];
}

int QExtNavigationListView::itemMargin(bool isParent) const
{
    Q_D(const QExtNavigationListView);
    return d->mItemMargins[isParent];
}

int QExtNavigationListView::itemFontSize(bool isParent) const
{
    Q_D(const QExtNavigationListView);
    return d->mItemFontSizes[isParent];
}

int QExtNavigationListView::itemIconMargin(bool isParent) const
{
    Q_D(const QExtNavigationListView);
    return d->mItemIconMargins[isParent];
}

void QExtNavigationListView::expandAll()
{
    Q_D(QExtNavigationListView);
    QList<QExtNavigationListItem *> parentItems = d->mModel->parentItems();
    QList<QExtNavigationListItem *>::Iterator iter(parentItems.begin());
    while (parentItems.end() != iter)
    {
        (*iter)->setExpand(true);
        iter++;
    }
}

void QExtNavigationListView::collapseAll()
{
    Q_D(QExtNavigationListView);
    QList<QExtNavigationListItem *> parentItems = d->mModel->parentItems();
    QList<QExtNavigationListItem *>::Iterator iter(parentItems.begin());
    while (parentItems.end() != iter)
    {
        (*iter)->setExpand(false);
        iter++;
    }
}

QExtNavigationListView::ExpendMode QExtNavigationListView::expendMode() const
{
    Q_D(const QExtNavigationListView);
    return d->mExpendMode;
}

QSize QExtNavigationListView::sizeHint() const
{
    return QSize(200, 300);
}

QSize QExtNavigationListView::minimumSizeHint() const
{
    return QSize(20, 20);
}

void QExtNavigationListView::setModel(QExtNavigationListModel *model)
{
    Q_D(QExtNavigationListView);
    if (d->mModel.data() != model)
    {
        if (!d->mModel.isNull())
        {
            disconnect(d->mListView.data(), SIGNAL(clicked(QModelIndex)),
                       model, SLOT(expandCollapseItem(QModelIndex)));
            disconnect(d->mModel.data(), SIGNAL(checkedItemChanged(QExtNavigationListItem*)),
                       this, SIGNAL(checkedItemChanged(QExtNavigationListItem*)));
            d->mModel->deleteLater();
            d->mModel = QEXT_NULLPTR;
            d->mListView->setModel(d->mModel.data());
        }
        if (model)
        {
            d->mModel = model;
            d->mListView->setModel(d->mModel.data());
            connect(d->mListView.data(), SIGNAL(clicked(QModelIndex)),
                    model, SLOT(expandCollapseItem(QModelIndex)));
            connect(d->mModel.data(), SIGNAL(checkedItemChanged(QExtNavigationListItem*)),
                    this, SIGNAL(checkedItemChanged(QExtNavigationListItem*)));
        }
    }
}

QList<QExtNavigationListItem *> QExtNavigationListView::setItems(const QString &items)
{
    Q_D(QExtNavigationListView);
    QStringList item = items.split(",");
    if (d->mStringItems != item)
    {
        d->mStringItems = item;
        d->mModel->setItems(item);
    }
    return d->mModel->parentItems();
}

QList<QExtNavigationListItem *> QExtNavigationListView::setItems(const QStringList &items)
{
    Q_D(QExtNavigationListView);
    if (d->mStringItems != items)
    {
        d->mStringItems = items;
        d->mModel->setItems(items);
    }
    return d->mModel->parentItems();
}

void QExtNavigationListView::setItems(const QList<QExtNavigationListItem *> &items)
{
    Q_D(QExtNavigationListView);
    if (d->mItems != items)
    {
        d->mItems = items;
        d->mModel->setItems(items);
    }
}

bool QExtNavigationListView::setCurrentRow(int row)
{
    Q_D(QExtNavigationListView);
    QList<QExtNavigationListItem *> visiableItems = d->mModel->visiableItems();
    if (row >= 0 && row < visiableItems.size())
    {
        QExtNavigationListItem *item = visiableItems.at(row);
        if (d->mSelectedItem.data() != item)
        {
            d->mSelectedItem = item;
            d->mListView->setCurrentIndex(d->mModel->index(row, 0));
            emit this->selectedItemChanged(item);
        }
        return true;
    }
    else
    {
        qWarning() << "QExtNavigationListView::setCurrentRow(): row out of range in visiableItems";
        return false;
    }
}

bool QExtNavigationListView::setSelectedItem(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListView);
    QList<QExtNavigationListItem *> visiableItems = d->mModel->visiableItems();
    if (visiableItems.contains(item))
    {
        QList<QExtNavigationListItem *>::iterator iter;
        for (iter = visiableItems.begin(); iter != visiableItems.end(); ++iter)
        {
            if ((*iter)->isChildItem())
            {
                (*iter)->setChecked(*iter == item);
                if (d->mSelectedItem.data() != item)
                {
                    d->mSelectedItem = item;
                    int row = visiableItems.indexOf(item);
                    d->mListView->setCurrentIndex(d->mModel->index(row, 0));
                    emit this->selectedItemChanged(item);
                }
            }
        }
        return true;
    }
    else
    {
        qWarning() << "QExtNavigationListView::setSelectedItem(): item not visiable, can not set selected";
        return false;
    }
}

void QExtNavigationListView::setItemTipVisible(bool visible)
{
    Q_D(QExtNavigationListView);
    if (visible != d->mItenLineTipVisible)
    {
        d->mItenLineTipVisible = visible;
        emit this->itemTipVisibleChanged(visible);
        this->update();
    }
}

void QExtNavigationListView::setItemTipWidth(int width)
{
    Q_D(QExtNavigationListView);
    if (width != d->mItemLineTipWidth)
    {
        d->mItemLineTipWidth = width;
        emit this->itemTipWidthChanged(width);
        this->update();
    }
}

void QExtNavigationListView::setItemSeparateVisible(bool visible)
{
    Q_D(QExtNavigationListView);
    if (visible != d->mItemSeparateVisible)
    {
        d->mItemSeparateVisible = visible;
        emit this->itemSeparateVisibleChanged(visible);
        this->update();
    }
}

void QExtNavigationListView::setItemSeparateHeight(int height)
{
    Q_D(QExtNavigationListView);
    if (height != d->mItemSeparateHeight)
    {
        d->mItemSeparateHeight = height;
        emit this->itemSeparateHeightChanged(height);
        this->update();
    }
}

void QExtNavigationListView::setItemSeparateColor(const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->mItemSeparateColor)
    {
        d->mItemSeparateColor = color;
        emit this->itemSeparateColorChanged(color);
        this->update();
    }
}

void QExtNavigationListView::setItemLineLeftAlign(bool leftAlign)
{
    Q_D(QExtNavigationListView);
    if (leftAlign != d->mItemLineLeftAlign)
    {
        d->mItemLineLeftAlign = leftAlign;
        emit this->itemLineLeftAlignChanged(leftAlign);
        this->update();
    }
}

void QExtNavigationListView::setItemLineVisible(bool visible)
{
    Q_D(QExtNavigationListView);
    if (visible != d->mItemLineVisible)
    {
        d->mItemLineVisible = visible;
        emit this->itemLineVisibleChanged(visible);
        this->update();
    }
}

void QExtNavigationListView::setItemLineWidth(int width)
{
    Q_D(QExtNavigationListView);
    if (width != d->mItemLineWidth)
    {
        d->mItemLineWidth = width;
        emit this->itemLineWidthChanged(width);
        this->update();
    }
}

void QExtNavigationListView::setItemLineColor(const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->mItemLineColor)
    {
        d->mItemLineColor = color;
        emit this->itemLineColorChanged(color);
        this->update();
    }
}

void QExtNavigationListView::setItemTriangleLeftAlign(bool leftAlign)
{
    Q_D(QExtNavigationListView);
    if (leftAlign != d->mItemTriangleLeftAlign)
    {
        d->mItemTriangleLeftAlign = leftAlign;
        emit this->itemTriangleLeftAlignChanged(leftAlign);
        this->update();
    }
}

void QExtNavigationListView::setItemTriangleVisible(bool visible)
{
    Q_D(QExtNavigationListView);
    if (visible != d->mItemTriangleVisible)
    {
        d->mItemTriangleVisible = visible;
        emit this->itemTriangleVisibleChanged(visible);
        this->update();
    }
}

void QExtNavigationListView::setItemTriangleWidth(int width)
{
    Q_D(QExtNavigationListView);
    if (width != d->mItemTriangleWidth)
    {
        d->mItemTriangleWidth = width;
        emit this->itemTriangleWidthChanged(width);
        this->update();
    }
}

void QExtNavigationListView::setItemTriangleColor(const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->mItemTriangleColor)
    {
        d->mItemTriangleColor = color;
        emit this->itemTriangleColorChanged(color);
        this->update();
    }
}

void QExtNavigationListView::setItemMargin(bool isParent, int margin)
{
    Q_D(QExtNavigationListView);
    if (margin != d->mItemMargins[isParent])
    {
        d->mItemMargins[isParent] = margin;
        emit this->itemMarginChanged(isParent, margin);
        this->update();
    }
}

void QExtNavigationListView::setItemFontSize(bool isParent, int size)
{
    Q_D(QExtNavigationListView);
    if (size != d->mItemFontSizes[isParent])
    {
        d->mItemFontSizes[isParent] = size;
        emit this->itemFontSizeChanged(isParent, size);
        this->update();
    }
}

void QExtNavigationListView::setItemHeight(bool isParent, int height)
{
    Q_D(QExtNavigationListView);
    if (height != d->mItemHeights[isParent])
    {
        d->mItemHeights[isParent] = height;
        emit this->itemHeightChanged(isParent, height);
        this->update();
    }
}

void QExtNavigationListView::setItemIconMargin(bool isParent, int margin)
{
    Q_D(QExtNavigationListView);
    if (margin != d->mItemIconMargins[isParent])
    {
        d->mItemIconMargins[isParent] = margin;
        emit this->itemIconMarginChanged(isParent, margin);
        this->update();
    }
}

void QExtNavigationListView::setBackgroundColor(const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->mBackgroundColor)
    {
        d->mBackgroundColor = color;
        QString styleSheet = QString("background-color: rgba(%1, %2, %3, %4);")
                                 .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
        d->mListView->setStyleSheet(styleSheet);
        emit this->backgroundColorChanged(color);
    }
}

void QExtNavigationListView::setItemTextColor(bool isParent, ItemState state, const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->mItemTextColors[isParent][state])
    {
        d->mItemTextColors[isParent][state] = color;
        emit this->itemTextColorChanged(isParent, state, color);
        this->update();
    }
}

void QExtNavigationListView::setItemBackgroundColor(bool isParent, ItemState state, const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->mItemBackgroundColors[isParent][state])
    {
        d->mItemBackgroundColors[isParent][state] = color;
        emit this->itemBackgroundColorChanged(isParent, state, color);
        this->update();
    }
}

void QExtNavigationListView::setExpendMode(QExtNavigationListView::ExpendMode mode)
{
    Q_D(QExtNavigationListView);
    if (d->mExpendMode != mode)
    {
        d->mExpendMode = mode;
        if (mode == ExpendMode_SingleClick)
        {
            disconnect(d->mListView.data(), SIGNAL(doubleClicked(QModelIndex)),
                       d->mModel.data(), SLOT(expandCollapseItem(QModelIndex)));
            connect(d->mListView.data(), SIGNAL(clicked(QModelIndex)),
                    d->mModel.data(), SLOT(expandCollapseItem(QModelIndex)));
        }
        else if (mode == ExpendMode_DoubleClick)
        {
            disconnect(d->mListView.data(), SIGNAL(clicked(QModelIndex)),
                       d->mModel.data(), SLOT(expandCollapseItem(QModelIndex)));
            connect(d->mListView.data(), SIGNAL(doubleClicked(QModelIndex)),
                    d->mModel.data(), SLOT(expandCollapseItem(QModelIndex)));
        }
        else if (mode == ExpendMode_NoClick)
        {
            disconnect(d->mListView.data(), SIGNAL(clicked(QModelIndex)),
                       d->mModel.data(), SLOT(expandCollapseItem(QModelIndex)));
            disconnect(d->mListView.data(), SIGNAL(doubleClicked(QModelIndex)),
                       d->mModel.data(), SLOT(expandCollapseItem(QModelIndex)));
        }
        emit this->expendModeChanged(mode);
    }
}

void QExtNavigationListView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QWidget::paintEvent(event);
}
