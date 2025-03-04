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
#include <QMutableStringListIterator>
#endif

QExtNavigationListItemPrivate::QExtNavigationListItemPrivate(QExtNavigationListItem *q)
    : q_ptr(q)
{
    m_enable = true;
    m_checkd = false;
    m_expand = false;
    m_visiable = true;
}

QExtNavigationListItemPrivate::~QExtNavigationListItemPrivate()
{
    m_childItems.clear();
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
    d->m_text = text;
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QPixmap &icon,
                                               QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->m_text = text;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QPixmap &icon,
                                               bool expand, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->m_text = text;
    d->m_expand = expand;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QString &tip,
                                               const QPixmap &icon, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->m_text = text;
    d->m_tip = tip;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QString &tip,
                                               const QPixmap &icon, bool expand, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_expand = expand;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QChar &fontChar,
                                               QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->m_text = text;
    d->m_fontIcon = fontChar;
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QChar &fontChar,
                                               bool expand, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->m_text = text;
    d->m_fontIcon = fontChar;
    d->m_expand = expand;
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QString &tip,
                                               const QChar &fontChar, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_fontIcon = fontChar;
    this->setParentItem(parent);
}

QExtNavigationListItem::QExtNavigationListItem(const QString &text, const QString &tip,
                                               const QChar &fontChar, bool expand, QExtNavigationListItem *parent)
    : QObject()
    , dd_ptr(new QExtNavigationListItemPrivate(this))
{
    Q_D(QExtNavigationListItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_fontIcon = fontChar;
    d->m_expand = expand;
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
    return d->m_normalIcon;
}

QPixmap QExtNavigationListItem::hoverIcon() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_hoverIcon;
}

QPixmap QExtNavigationListItem::checkedIcon() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_checkedIcon;
}

QPixmap QExtNavigationListItem::selectedIcon() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_selectedIcon;
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
    d->m_normalIcon = icon;
    emit this->iconChanged(this);
}

void QExtNavigationListItem::setHoverIcon(const QPixmap &icon)
{
    Q_D(QExtNavigationListItem);
    d->m_hoverIcon = icon;
    emit this->iconChanged(this);
}

void QExtNavigationListItem::setCheckedIcon(const QPixmap &icon)
{
    Q_D(QExtNavigationListItem);
    d->m_checkedIcon = icon;
    emit this->iconChanged(this);
}

void QExtNavigationListItem::setSelectedIcon(const QPixmap &icon)
{
    Q_D(QExtNavigationListItem);
    d->m_selectedIcon = icon;
    emit this->iconChanged(this);
}

QChar QExtNavigationListItem::fontIcon() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_fontIcon;
}

void QExtNavigationListItem::setFontIcon(const QChar &ch)
{
    Q_D(QExtNavigationListItem);
    if (ch != d->m_fontIcon)
    {
        d->m_fontIcon = ch;
        emit this->fontIconChanged(this);
    }
}

QString QExtNavigationListItem::text() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_text;
}

void QExtNavigationListItem::setText(const QString &text)
{
    Q_D(QExtNavigationListItem);
    if (text != d->m_text)
    {
        d->m_text = text;
        emit this->textChanged(this);
    }
}

QString QExtNavigationListItem::tip() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_tip;
}

void QExtNavigationListItem::setTip(const QString &tip)
{
    Q_D(QExtNavigationListItem);
    if (tip != d->m_tip)
    {
        d->m_tip = tip;
        emit this->tipChanged(this);
    }
}

bool QExtNavigationListItem::isExpand() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_expand;
}

void QExtNavigationListItem::setExpand(const bool &expand)
{
    Q_D(QExtNavigationListItem);
    if (expand != d->m_expand)
    {
        d->m_expand = expand;
        emit this->expandChanged(this);
    }
}

bool QExtNavigationListItem::isVisible() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_visiable;
}

void QExtNavigationListItem::setVisible(const bool &visiable)
{
    Q_D(QExtNavigationListItem);
    if (visiable != d->m_visiable)
    {
        if (!visiable)
        {
            QList<QExtNavigationListItem *>::const_iterator iter;
            for (iter = d->m_childItems.begin(); iter != d->m_childItems.end(); ++iter)
            {
                (*iter)->setChecked(false);
            }
        }
        emit this->visiableAboutToBeChanged(this);
        d->m_visiable = visiable;
        emit this->visiableChanged(this);
    }
}

bool QExtNavigationListItem::isEnabled() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_enable;
}

void QExtNavigationListItem::setEnable(const bool &enable)
{
    Q_D(QExtNavigationListItem);
    if (enable != d->m_enable)
    {
        d->m_enable = enable;
        emit this->enableChanged(this);
    }
}

Qt::CheckState QExtNavigationListItem::checkState() const
{
    Q_D(const QExtNavigationListItem);
    if (this->isParentItem())
    {
        QList<QExtNavigationListItem *>::const_iterator iter;
        for (iter = d->m_childItems.begin(); iter != d->m_childItems.end(); ++iter)
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
        return d->m_checkd ? Qt::Checked : Qt::Unchecked;
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
    if (check != d->m_checkd)
    {
        d->m_checkd = check;
        emit this->checkChanged(this);
    }
    return true;
}

bool QExtNavigationListItem::isLastVisibleItem() const
{
    Q_D(const QExtNavigationListItem);
    if (!d->m_parent.isNull() && d->m_visiable)
    {
        return this == d->m_parent->visiableChildItems().last();
    }
    return false;
}

bool QExtNavigationListItem::isChildItem() const
{
    Q_D(const QExtNavigationListItem);
    return !d->m_parent.isNull();
}

bool QExtNavigationListItem::isParentItem() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_parent.isNull();
}

QExtNavigationListItem *QExtNavigationListItem::parentItem() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_parent.data();
}

bool QExtNavigationListItem::setParentItem(QExtNavigationListItem *parent)
{
    Q_D(QExtNavigationListItem);
    if (this == parent)
    {
        qWarning() << "QExtNavigationListItem::setParentItem(): parent can not equal to item self";
        return false;
    }
    if (!d->m_childItems.isEmpty())
    {
        qWarning() << "QExtNavigationListItem::setParentItem(): current item is parent item, can not set parent";
        return false;
    }
    if (d->m_parent.data() != parent)
    {
        QExtNavigationListItem *oldParent = d->m_parent.data();
        d->m_parent = parent;

        if (oldParent)
        {
            emit oldParent->childItemAboutToBeRemoved(this, oldParent);
            oldParent->d_func()->m_childItems.removeOne(this);
            this->disconnect(oldParent);
            emit oldParent->childItemRemoved(this, oldParent);
        }

        if (parent)
        {
            emit parent->childItemAboutToBeInserted(this, parent);
            parent->d_func()->m_childItems.append(this);
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
    return d->m_childItems.count();
}

int QExtNavigationListItem::visiableChildItemsCount() const
{
    return this->visiableChildItems().count();
}

QList<QExtNavigationListItem *> QExtNavigationListItem::childItems() const
{
    Q_D(const QExtNavigationListItem);
    return d->m_childItems;
}

QList<QExtNavigationListItem *> QExtNavigationListItem::visiableChildItems() const
{
    Q_D(const QExtNavigationListItem);
    QList<QExtNavigationListItem *> result;
    QList<QExtNavigationListItem *>::const_iterator iter;
    for (iter = d->m_childItems.begin(); iter != d->m_childItems.end(); ++iter)
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
    if (item && d->m_childItems.contains(item))
    {
        emit this->childItemAboutToBeRemoved(item, this);
        d->m_childItems.removeOne(item);
        emit this->childItemRemoved(item, this);
    }
}



QExtNavListDelegate::QExtNavListDelegate(QExtNavigationListViewPrivate *navData)
    : QStyledItemDelegate()
    , m_navData(navData)
    , m_navListView(navData->q_ptr)
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
        m_iconFont = QFont("FontAwesome");
#if (QT_VERSION >= QT_VERSION_CHECK(4, 8, 0))
        m_iconFont.setHintingPreference(QFont::PreferNoHinting);
#endif
    }
}

QSize QExtNavListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QExtNavigationListItem *item = (QExtNavigationListItem *)index.data(Qt::UserRole).toLongLong();

    QSize size(50, m_navListView->itemHeight(item->isParentItem()));
    return size;
}

void QExtNavListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QPalette &buttonPalette = m_navData->buttonPalette();
    const QPalette &listViewPalette = m_navData->listViewPalette();
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

    int fontSize = m_navListView->itemFontSize(parent);
    QPixmap icon;
    QColor bgColor, textColor, tipBgColor, tipTextColor, iconColor;
    if (checked)
    {
        bgColor = m_navListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Checked);
        textColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Checked);
        tipBgColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Checked);
        tipTextColor = m_navListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Checked);
        iconColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Checked);
        icon = item->checkedIcon();
    }
    else if (option.state & QStyle::State_Selected && enabled && parentEnabled)
    {
        bgColor = m_navListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Selected);
        textColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Selected);
        tipBgColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Selected);
        tipTextColor = m_navListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Selected);
        iconColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Selected);
        icon = item->selectedIcon();
    }
    else if (option.state & QStyle::State_MouseOver && enabled && parentEnabled)
    {
        bgColor = m_navListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Hovered);
        textColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Hovered);
        tipBgColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Checked);
        tipTextColor = m_navListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Checked);
        iconColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Hovered);
        icon = item->hoverIcon();
    }
    else
    {
        bgColor = m_navListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Normal);
        textColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Normal);
        tipBgColor = m_navListView->itemBackgroundColor(parent, QExtNavigationListView::ItemState_Checked);
        tipTextColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Checked);
        iconColor = m_navListView->itemTextColor(parent, QExtNavigationListView::ItemState_Normal);
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

    int lineWidth = m_navData->m_itemLineWidth;
    if (!parent && m_navData->m_itemLineVisible && lineWidth > 0)
    {
        if (checked)
        {
            float offset = (float)lineWidth / 2;

            QPointF pointTop(x, y + offset);
            QPointF pointBottom(x, height + y - offset);
            if (!m_navData->m_itemLineLeftAlign)
            {
                pointTop.setX(width);
                pointBottom.setX(width);
            }

            painter->setPen(QPen(m_navListView->itemLineColor(), lineWidth));
            painter->drawLine(pointTop, pointBottom);
        }
    }

    int triangleWidth = m_navData->m_itemTriangleWidth;
    if (!parent && m_navData->m_itemTriangleVisible && triangleWidth > 0)
    {
        if (checked)
        {
            QFont font = m_iconFont;
            font.setPixelSize(fontSize + triangleWidth);
            painter->setFont(font);
            painter->setPen(m_navListView->itemTriangleColor());
            if (m_navData->m_itemTriangleLeftAlign)
            {
                painter->drawText(optionRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf0da));
            }
            else
            {
                painter->drawText(optionRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf0d9));
            }
        }
    }

    if (m_navData->m_itemSeparateVisible)
    {
        if (item->isParentItem() || (item->isChildItem() && item->isLastVisibleItem()))
        {
            painter->setPen(QPen(m_navListView->itemSeparateColor(), m_navData->m_itemSeparateHeight));
            painter->drawLine(QPointF(x, y + height), QPointF(x + width, y + height));
        }
    }

    QString text = item->text();
    if (!text.isEmpty())
    {
        int margin = m_navListView->itemMargin(true);
        if (item->isChildItem())
        {
            margin = m_navListView->itemMargin(false);
            fontSize = m_navListView->itemFontSize(false);
        }

        QRect textRect = optionRect;
        textRect.setWidth(width - margin);
        textRect.setX(x + margin);

        QFont font = m_navData->buttonFont();
        font.setPixelSize(fontSize);
        painter->setFont(font);
        painter->setPen(textColor);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }

    QString tip = item->tip();
    if (m_navData->m_itenLineTipVisible && !tip.isEmpty())
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
        tipRect.setLeft(optionRect.right() - m_navData->m_itemLineTipWidth - 5);
        tipRect.setRight(optionRect.right() - 5);

        QFont font = m_navData->buttonFont();
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
    iconRect.setLeft(m_navListView->itemIconMargin(parent));

    QFont font = m_iconFont;
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
    m_parentItemList.clear();
    m_visiableItemList.clear();
}

void QExtNavigationListModelPrivate::deleteAllItems()
{
    QSet<QExtNavigationListItem *>::iterator iter;
    for (iter = m_allItemSet.begin(); iter != m_allItemSet.end(); ++iter)
    {
        (*iter)->disconnect();
        (*iter)->deleteLater();
    }
    m_allItemSet.clear();
}

void QExtNavigationListModelPrivate::refreshVisibleList()
{
    m_visiableItemList.clear();
    QList<QExtNavigationListItem *>::iterator iter;
    for (iter = m_parentItemList.begin(); iter != m_parentItemList.end(); ++iter)
    {
        if ((*iter)->isVisible())
        {
            m_visiableItemList.append(*iter);
            if ((*iter)->isExpand())
            {
                QList<QExtNavigationListItem *> childItems = (*iter)->visiableChildItems();
                if (!childItems.isEmpty())
                {
                    m_visiableItemList.append(childItems);
                }
            }
        }
    }
}

void QExtNavigationListModelPrivate::initAllItemsConnection()
{
    QSet<QExtNavigationListItem *>::iterator iter;
    for (iter = m_allItemSet.begin(); iter != m_allItemSet.end(); ++iter)
    {
        QExtNavigationListItem *item = *iter;
        this->initItemConnection(item);
    }
}

void QExtNavigationListModelPrivate::initItemConnection(QExtNavigationListItem *item)
{
    Q_Q(QExtNavigationListModel);
    item->disconnect(q);
    QObject::connect(item, SIGNAL(itemAboutToDestroyed(QExtNavigationListItem*)), q, SLOT(onItemAboutToDestroyed(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(iconChanged(QExtNavigationListItem*)), q, SLOT(onItemChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(fontIconChanged(QExtNavigationListItem*)), q, SLOT(onItemChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(textChanged(QExtNavigationListItem*)), q, SLOT(onItemChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(tipChanged(QExtNavigationListItem*)), q, SLOT(onItemChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(enableChanged(QExtNavigationListItem*)), q, SLOT(onItemChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(expandChanged(QExtNavigationListItem*)), q, SLOT(onItemExpandChanged(QExtNavigationListItem*)));
    QObject::connect(item, SIGNAL(checkChanged(QExtNavigationListItem*)), q, SLOT(onItemCheckChanged(QExtNavigationListItem*)));
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
    return d->m_checkedItem.data();
}

QList<QExtNavigationListItem *> QExtNavigationListModel::allItems() const
{
    Q_D(const QExtNavigationListModel);
    return d->m_allItemSet.values();
}

QList<QExtNavigationListItem *> QExtNavigationListModel::parentItems() const
{
    Q_D(const QExtNavigationListModel);
    return d->m_parentItemList;
}

QList<QExtNavigationListItem *> QExtNavigationListModel::visiableItems() const
{
    Q_D(const QExtNavigationListModel);
    return d->m_visiableItemList;
}

int QExtNavigationListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const QExtNavigationListModel);
    return d->m_visiableItemList.size();
}

QVariant QExtNavigationListModel::data(const QModelIndex &index, int role) const
{
    Q_D(const QExtNavigationListModel);
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= d->m_visiableItemList.size() || index.row() < 0)
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return d->m_visiableItemList.at(index.row())->text();
    }
    if (role == Qt::BackgroundRole)
    {
        return QColor(Qt::red);
    }
    else if (role == Qt::UserRole)
    {
        return (quint64)(d->m_visiableItemList.at(index.row()));
    }

    return QVariant();
}

Qt::ItemFlags QExtNavigationListModel::flags(const QModelIndex &index) const
{
    Q_D(const QExtNavigationListModel);
    if (index.isValid())
    {
        int row = index.row();
        if (row >= 0 && row < d->m_visiableItemList.size())
        {
            QExtNavigationListItem *item = d->m_visiableItemList.at(row);
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
        d->m_visiableItemList.clear();
        d->m_parentItemList.clear();

        QList<QExtNavigationListItem *>::const_iterator iter;
        for (iter = items.begin(); iter != items.end(); ++iter)
        {
            QExtNavigationListItem *item = *iter;
            if (item->isParentItem())
            {
                cacheItemSet.insert(item);
                d->m_parentItemList.append(item);
                if (d->m_allItemSet.contains(item))
                {
                    d->m_allItemSet.remove(item);
                }

                QList<QExtNavigationListItem *> childItems = item->childItems();
                QList<QExtNavigationListItem *>::iterator childIter;
                for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                {
                    QExtNavigationListItem *childItem = *childIter;
                    cacheItemSet.insert(childItem);
                    if (d->m_allItemSet.contains(childItem))
                    {
                        d->m_allItemSet.remove(childItem);
                    }
                }
            }
        }

        d->deleteAllItems();
        d->m_allItemSet = cacheItemSet;
        d->refreshVisibleList();
        d->initAllItemsConnection();

        this->endResetModel();
    }
}

void QExtNavigationListModel::expandCollapseItem(const QModelIndex &index)
{
    Q_D(QExtNavigationListModel);
    QExtNavigationListItem *item = d->m_visiableItemList.at(index.row());
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
        d->m_allItemSet.remove(item);
        d->m_parentItemList.removeOne(item);
        if (item->isVisible())
        {
            int row = d->m_visiableItemList.indexOf(item);
            int count = item->visiableChildItemsCount();
            this->beginRemoveRows(QModelIndex(), row, row + count);
            d->m_visiableItemList.removeOne(item);

            QList<QExtNavigationListItem *>::iterator iter;
            QList<QExtNavigationListItem *> childItems = item->childItems();
            for (iter = childItems.begin(); iter != childItems.end(); ++iter)
            {
                QExtNavigationListItem *childItem = *iter;
                if (childItem->parentItem() == item)
                {
                    d->m_allItemSet.remove(childItem);
                    d->m_visiableItemList.removeOne(childItem);
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
    int row = d->m_visiableItemList.indexOf(item);
    QModelIndex index = this->index(row, 0);
    emit this->dataChanged(index, index);
}

void QExtNavigationListModel::onItemEnableChanged(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListModel);
    if (item->isVisible())
    {
        int row = d->m_visiableItemList.indexOf(item);
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
    int index = d->m_visiableItemList.indexOf(item);
    if (item->isExpand())
    {
        this->beginInsertRows(QModelIndex(), index + 1, index + count);
        for (int i = 0; i < count; ++i)
        {
            d->m_visiableItemList.insert(index + 1 + i, visiableItems.at(i));
        }
        this->endInsertRows();
    }
    else
    {
        this->beginRemoveRows(QModelIndex(), index + 1, index + count);
        for (int i = 0; i < count; ++i)
        {
            d->m_visiableItemList.removeAt(index + 1);
        }
        this->endRemoveRows();
    }
}

void QExtNavigationListModel::onItemCheckChanged(QExtNavigationListItem *item)
{
    Q_D(QExtNavigationListModel);
    int row = d->m_visiableItemList.indexOf(item);
    QModelIndex index = this->index(row, 0);
    emit this->dataChanged(index, index);

    if (item->isChecked())
    {
        if (item != d->m_checkedItem.data())
        {
            QExtNavigationListItem *oldCheckedItem = d->m_checkedItem.data();
            d->m_checkedItem = item;
            if (oldCheckedItem)
            {
                oldCheckedItem->setChecked(false);
            }
            emit this->checkedItemChanged(item);
        }
    }
    else
    {
        if (item == d->m_checkedItem.data())
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
        int row = d->m_visiableItemList.indexOf(item);
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
        for (iter = d->m_parentItemList.begin(); iter != d->m_parentItemList.end(); ++iter)
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
        for (iter = d->m_parentItemList.begin(); iter != d->m_parentItemList.end(); ++iter)
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
                    d->m_visiableItemList.insert(row++, *iter);
                    if ((*iter)->isExpand())
                    {
                        QList<QExtNavigationListItem *>::iterator childIter;
                        for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                        {
                            if ((*childIter)->isVisible())
                            {
                                d->m_visiableItemList.insert(row++, *childIter);
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
                            d->m_visiableItemList.insert(row++, *childIter);
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
        int row = d->m_visiableItemList.indexOf(item);
        int count = (item->isExpand() && item->isParentItem()) ? item->visiableChildItemsCount() : 0;
        d->m_visiableItemList.removeAt(row);
        for (int i = 0; i < count; ++i)
        {
            d->m_visiableItemList.removeAt(row);
        }
        this->endRemoveRows();
    }
}

void QExtNavigationListModel::onChildItemAboutToBeInserted(QExtNavigationListItem *item, QExtNavigationListItem *parent)
{
    Q_D(QExtNavigationListModel);
    if (item->isVisible() && parent->isVisible())
    {
        int index = d->m_visiableItemList.indexOf(parent);
        int row = parent->visiableChildItemsCount() + 1;
        this->beginInsertRows(QModelIndex(), index + row + 1, index + row + 1);
    }
}

void QExtNavigationListModel::onChildItemInserted(QExtNavigationListItem *item, QExtNavigationListItem *parent)
{
    Q_D(QExtNavigationListModel);
    if (item->isVisible() && parent->isVisible())
    {
        int index = d->m_visiableItemList.indexOf(parent);
        int row = parent->visiableChildItemsCount();
        d->m_visiableItemList.insert(index + row + 1, item);
        this->endInsertRows();
    }
}

void QExtNavigationListModel::onChildItemAboutToBeRemoved(QExtNavigationListItem *item, QExtNavigationListItem *parent)
{
    Q_D(QExtNavigationListModel);
    if (d->m_visiableItemList.contains(item))
    {
        int row = d->m_visiableItemList.indexOf(parent);
        this->beginRemoveRows(QModelIndex(), row, row);
    }
}

void QExtNavigationListModel::onChildItemRemoved(QExtNavigationListItem *item, QExtNavigationListItem *parent)
{
    Q_D(QExtNavigationListModel);
    d->m_allItemSet.remove(item);
    if (d->m_visiableItemList.contains(item))
    {
        d->m_visiableItemList.removeOne(item);
        this->endRemoveRows();
    }
}



QExtNavigationListViewPrivate::QExtNavigationListViewPrivate(QExtNavigationListView *q)
    : q_ptr(q)
    , m_pushButton(new QPushButton(q))
{
    m_pushButton->setVisible(false);

    m_itemLineTipWidth = 40;
    m_itenLineTipVisible = true;

    m_itemSeparateHeight = 1;
    m_itemSeparateVisible = true;

    m_itemLineWidth = 6;
    m_itemLineVisible = true;
    m_itemLineLeftAlign = true;

    m_itemTriangleWidth = 6;
    m_itemTriangleVisible = true;
    m_itemTriangleLeftAlign = false;

    m_itemMargins[false] = 35;
    m_itemHeights[false] = 30;
    m_itemFontSizes[false] = 12;
    m_itemIconMargins[false] = 15;
    m_itemMargins[true] = 30;
    m_itemHeights[true] = 35;
    m_itemFontSizes[true] = 12;
    m_itemIconMargins[true] = 10;

    m_expendMode = QExtNavigationListView::ExpendMode_SingleClick;

    m_delegate.reset(new QExtNavListDelegate(this));
    m_listView.reset(new QExtNavListView);
    m_listView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_listView->setMouseTracking(true);
    m_listView->setAutoFillBackground(true);
    m_listView->setItemDelegate(m_delegate.data());
}

QExtNavigationListViewPrivate::~QExtNavigationListViewPrivate()
{
    if (!m_model.isNull())
    {
        m_model->deleteLater();
    }
}

const QFont &QExtNavigationListViewPrivate::buttonFont() const
{
    return m_pushButton->font();
}

const QPalette &QExtNavigationListViewPrivate::buttonPalette() const
{
    return m_pushButton->palette();
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
    layout->setMargin(0);
    layout->addWidget(d->m_listView.data());
    this->setLayout(layout);
    this->setModel(new QExtNavigationListModel);
    connect(d->m_listView.data(), SIGNAL(pressed(QModelIndex)), this, SLOT(onItemPressed(QModelIndex)));
}

QExtNavigationListView::~QExtNavigationListView()
{

}

QListView *QExtNavigationListView::view() const
{
    Q_D(const QExtNavigationListView);
    return d->m_listView.data();
}

QExtNavigationListModel *QExtNavigationListView::model() const
{
    Q_D(const QExtNavigationListView);
    return d->m_model.data();
}

QExtNavigationListItem *QExtNavigationListView::selectedItem() const
{
    Q_D(const QExtNavigationListView);
    return d->m_selectedItem.data();
}

QExtNavigationListItem *QExtNavigationListView::checkedItem() const
{
    Q_D(const QExtNavigationListView);
    return d->m_model->checkedItem();
}

QList<QExtNavigationListItem *> QExtNavigationListView::allItems() const
{
    Q_D(const QExtNavigationListView);
    return d->m_model->allItems();
}

QList<QExtNavigationListItem *> QExtNavigationListView::parentItems() const
{
    Q_D(const QExtNavigationListView);
    return d->m_model->parentItems();
}

QList<QExtNavigationListItem *> QExtNavigationListView::visiableItems() const
{
    Q_D(const QExtNavigationListView);
    return d->m_model->visiableItems();
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
    return d->m_itenLineTipVisible;
}

int QExtNavigationListView::itemTipWidth() const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemLineTipWidth;
}

bool QExtNavigationListView::isItemSeparateVisible() const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemSeparateVisible;
}

int QExtNavigationListView::itemSeparateHeight() const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemSeparateHeight;
}

QColor QExtNavigationListView::itemSeparateColor() const
{
    Q_D(const QExtNavigationListView);
    if (d->m_itemSeparateColor.has_value())
    {
        return d->m_itemSeparateColor.value();
    }
    else
    {
        return d->buttonPalette().color(QPalette::Active, QPalette::ButtonText);
    }
}

bool QExtNavigationListView::isItemLineLeftAlign() const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemLineLeftAlign;
}

bool QExtNavigationListView::isItemLineVisible() const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemLineVisible;
}

int QExtNavigationListView::itemLineWidth() const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemLineWidth;
}

QColor QExtNavigationListView::itemLineColor() const
{
    Q_D(const QExtNavigationListView);
    if (d->m_itemLineColor.has_value())
    {
        return d->m_itemLineColor.value();
    }
    else
    {
        return this->itemTextColor(false, ItemState_Normal);
    }
}

bool QExtNavigationListView::isItemTriangleLeftAlign() const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemTriangleLeftAlign;
}

bool QExtNavigationListView::isItemTriangleVisible() const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemTriangleVisible;
}

int QExtNavigationListView::itemTriangleWidth() const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemTriangleWidth;
}

QColor QExtNavigationListView::itemTriangleColor() const
{
    Q_D(const QExtNavigationListView);
    if (d->m_itemTriangleColor.has_value())
    {
        return d->m_itemTriangleColor.value();
    }
    else
    {
        return this->palette().color(QPalette::Active, QPalette::Window);
    }
}

QColor QExtNavigationListView::backgroundColor() const
{
    Q_D(const QExtNavigationListView);
    if (d->m_backgroundColor.has_value())
    {
        return d->m_backgroundColor.value();
    }
    else
    {
        return this->palette().color(QPalette::Active, QPalette::Window);
    }
}

QColor QExtNavigationListView::itemTextColor(bool isParent, ItemState state) const
{
    Q_D(const QExtNavigationListView);
    if (d->m_itemTextColors[isParent][state].has_value())
    {
        return d->m_itemTextColors[isParent][state].value();
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
    if (d->m_itemBackgroundColors[isParent][state].has_value())
    {
        return d->m_itemBackgroundColors[isParent][state].value();
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
    return d->m_itemHeights[isParent];
}

int QExtNavigationListView::itemMargin(bool isParent) const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemMargins[isParent];
}

int QExtNavigationListView::itemFontSize(bool isParent) const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemFontSizes[isParent];
}

int QExtNavigationListView::itemIconMargin(bool isParent) const
{
    Q_D(const QExtNavigationListView);
    return d->m_itemIconMargins[isParent];
}

QExtNavigationListView::ExpendMode QExtNavigationListView::expendMode() const
{
    Q_D(const QExtNavigationListView);
    return d->m_expendMode;
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
    if (d->m_model.data() != model)
    {
        if (!d->m_model.isNull())
        {
            disconnect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)),
                       model, SLOT(expandCollapseItem(QModelIndex)));
            disconnect(d->m_model.data(), SIGNAL(checkedItemChanged(QExtNavigationListItem*)),
                       this, SIGNAL(checkedItemChanged(QExtNavigationListItem*)));
            d->m_model->deleteLater();
            d->m_model = QEXT_NULLPTR;
            d->m_listView->setModel(d->m_model.data());
        }
        if (model)
        {
            d->m_model = model;
            d->m_listView->setModel(d->m_model.data());
            connect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)),
                    model, SLOT(expandCollapseItem(QModelIndex)));
            connect(d->m_model.data(), SIGNAL(checkedItemChanged(QExtNavigationListItem*)),
                    this, SIGNAL(checkedItemChanged(QExtNavigationListItem*)));
        }
    }
}

QList<QExtNavigationListItem *> QExtNavigationListView::setItems(const QString &items)
{
    Q_D(QExtNavigationListView);
    QStringList item = items.split(",");
    if (d->m_stringItems != item)
    {
        d->m_stringItems = item;
        d->m_model->setItems(item);
    }
    return d->m_model->parentItems();
}

QList<QExtNavigationListItem *> QExtNavigationListView::setItems(const QStringList &items)
{
    Q_D(QExtNavigationListView);
    if (d->m_stringItems != items)
    {
        d->m_stringItems = items;
        d->m_model->setItems(items);
    }
    return d->m_model->parentItems();
}

void QExtNavigationListView::setItems(const QList<QExtNavigationListItem *> &items)
{
    Q_D(QExtNavigationListView);
    if (d->m_items != items)
    {
        d->m_items = items;
        d->m_model->setItems(items);
    }
}

bool QExtNavigationListView::setCurrentRow(int row)
{
    Q_D(QExtNavigationListView);
    QList<QExtNavigationListItem *> visiableItems = d->m_model->visiableItems();
    if (row >= 0 && row < visiableItems.size())
    {
        QExtNavigationListItem *item = visiableItems.at(row);
        if (d->m_selectedItem.data() != item)
        {
            d->m_selectedItem = item;
            d->m_listView->setCurrentIndex(d->m_model->index(row, 0));
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
    QList<QExtNavigationListItem *> visiableItems = d->m_model->visiableItems();
    if (visiableItems.contains(item))
    {
        QList<QExtNavigationListItem *>::iterator iter;
        for (iter = visiableItems.begin(); iter != visiableItems.end(); ++iter)
        {
            if ((*iter)->isChildItem())
            {
                (*iter)->setChecked(*iter == item);
                if (d->m_selectedItem.data() != item)
                {
                    d->m_selectedItem = item;
                    int row = visiableItems.indexOf(item);
                    d->m_listView->setCurrentIndex(d->m_model->index(row, 0));
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
    if (visible != d->m_itenLineTipVisible)
    {
        d->m_itenLineTipVisible = visible;
        emit this->itemTipVisibleChanged(visible);
        this->update();
    }
}

void QExtNavigationListView::setItemTipWidth(int width)
{
    Q_D(QExtNavigationListView);
    if (width != d->m_itemLineTipWidth)
    {
        d->m_itemLineTipWidth = width;
        emit this->itemTipWidthChanged(width);
        this->update();
    }
}

void QExtNavigationListView::setItemSeparateVisible(bool visible)
{
    Q_D(QExtNavigationListView);
    if (visible != d->m_itemSeparateVisible)
    {
        d->m_itemSeparateVisible = visible;
        emit this->itemSeparateVisibleChanged(visible);
        this->update();
    }
}

void QExtNavigationListView::setItemSeparateHeight(int height)
{
    Q_D(QExtNavigationListView);
    if (height != d->m_itemSeparateHeight)
    {
        d->m_itemSeparateHeight = height;
        emit this->itemSeparateHeightChanged(height);
        this->update();
    }
}

void QExtNavigationListView::setItemSeparateColor(const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->m_itemSeparateColor)
    {
        d->m_itemSeparateColor = color;
        emit this->itemSeparateColorChanged(color);
        this->update();
    }
}

void QExtNavigationListView::setItemLineLeftAlign(bool leftAlign)
{
    Q_D(QExtNavigationListView);
    if (leftAlign != d->m_itemLineLeftAlign)
    {
        d->m_itemLineLeftAlign = leftAlign;
        emit this->itemLineLeftAlignChanged(leftAlign);
        this->update();
    }
}

void QExtNavigationListView::setItemLineVisible(bool visible)
{
    Q_D(QExtNavigationListView);
    if (visible != d->m_itemLineVisible)
    {
        d->m_itemLineVisible = visible;
        emit this->itemLineVisibleChanged(visible);
        this->update();
    }
}

void QExtNavigationListView::setItemLineWidth(int width)
{
    Q_D(QExtNavigationListView);
    if (width != d->m_itemLineWidth)
    {
        d->m_itemLineWidth = width;
        emit this->itemLineWidthChanged(width);
        this->update();
    }
}

void QExtNavigationListView::setItemLineColor(const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->m_itemLineColor)
    {
        d->m_itemLineColor = color;
        emit this->itemLineColorChanged(color);
        this->update();
    }
}

void QExtNavigationListView::setItemTriangleLeftAlign(bool leftAlign)
{
    Q_D(QExtNavigationListView);
    if (leftAlign != d->m_itemTriangleLeftAlign)
    {
        d->m_itemTriangleLeftAlign = leftAlign;
        emit this->itemTriangleLeftAlignChanged(leftAlign);
        this->update();
    }
}

void QExtNavigationListView::setItemTriangleVisible(bool visible)
{
    Q_D(QExtNavigationListView);
    if (visible != d->m_itemTriangleVisible)
    {
        d->m_itemTriangleVisible = visible;
        emit this->itemTriangleVisibleChanged(visible);
        this->update();
    }
}

void QExtNavigationListView::setItemTriangleWidth(int width)
{
    Q_D(QExtNavigationListView);
    if (width != d->m_itemTriangleWidth)
    {
        d->m_itemTriangleWidth = width;
        emit this->itemTriangleWidthChanged(width);
        this->update();
    }
}

void QExtNavigationListView::setItemTriangleColor(const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->m_itemTriangleColor)
    {
        d->m_itemTriangleColor = color;
        emit this->itemTriangleColorChanged(color);
        this->update();
    }
}

void QExtNavigationListView::setItemMargin(bool isParent, int margin)
{
    Q_D(QExtNavigationListView);
    if (margin != d->m_itemMargins[isParent])
    {
        d->m_itemMargins[isParent] = margin;
        emit this->itemMarginChanged(isParent, margin);
        this->update();
    }
}

void QExtNavigationListView::setItemFontSize(bool isParent, int size)
{
    Q_D(QExtNavigationListView);
    if (size != d->m_itemFontSizes[isParent])
    {
        d->m_itemFontSizes[isParent] = size;
        emit this->itemFontSizeChanged(isParent, size);
        this->update();
    }
}

void QExtNavigationListView::setItemHeight(bool isParent, int height)
{
    Q_D(QExtNavigationListView);
    if (height != d->m_itemHeights[isParent])
    {
        d->m_itemHeights[isParent] = height;
        emit this->itemHeightChanged(isParent, height);
        this->update();
    }
}

void QExtNavigationListView::setItemIconMargin(bool isParent, int margin)
{
    Q_D(QExtNavigationListView);
    if (margin != d->m_itemIconMargins[isParent])
    {
        d->m_itemIconMargins[isParent] = margin;
        emit this->itemIconMarginChanged(isParent, margin);
        this->update();
    }
}

void QExtNavigationListView::setBackgroundColor(const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->m_backgroundColor)
    {
        d->m_backgroundColor = color;
        QString styleSheet = QString("background-color: rgba(%1, %2, %3, %4);")
                                 .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
        d->m_listView->setStyleSheet(styleSheet);
        emit this->backgroundColorChanged(color);
    }
}

void QExtNavigationListView::setItemTextColor(bool isParent, ItemState state, const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->m_itemTextColors[isParent][state])
    {
        d->m_itemTextColors[isParent][state] = color;
        emit this->itemTextColorChanged(isParent, state, color);
        this->update();
    }
}

void QExtNavigationListView::setItemBackgroundColor(bool isParent, ItemState state, const QColor &color)
{
    Q_D(QExtNavigationListView);
    if (color != d->m_itemBackgroundColors[isParent][state])
    {
        d->m_itemBackgroundColors[isParent][state] = color;
        emit this->itemBackgroundColorChanged(isParent, state, color);
        this->update();
    }
}

void QExtNavigationListView::setExpendMode(QExtNavigationListView::ExpendMode mode)
{
    Q_D(QExtNavigationListView);
    if (d->m_expendMode != mode)
    {
        d->m_expendMode = mode;
        if (mode == ExpendMode_SingleClick)
        {
            disconnect(d->m_listView.data(), SIGNAL(doubleClicked(QModelIndex)),
                       d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
            connect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)),
                    d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
        }
        else if (mode == ExpendMode_DoubleClick)
        {
            disconnect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)),
                       d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
            connect(d->m_listView.data(), SIGNAL(doubleClicked(QModelIndex)),
                    d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
        }
        else if (mode == ExpendMode_NoClick)
        {
            disconnect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)),
                       d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
            disconnect(d->m_listView.data(), SIGNAL(doubleClicked(QModelIndex)),
                       d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
        }
        emit this->expendModeChanged(mode);
    }
}

void QExtNavigationListView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QWidget::paintEvent(event);
}
