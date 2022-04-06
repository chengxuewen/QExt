#include <qextNavigationListView.h>
#include <qextNavigationListView_p.h>

#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include <QFontDatabase>
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include <QMutableStringListIterator>
#endif

QEXTNavigationListItemPrivate::QEXTNavigationListItemPrivate(QEXTNavigationListItem *q)
    : q_ptr(q)
{
    m_expand = false;
    m_visiable = true;
    m_enable = true;
    m_checkd = false;
}

QEXTNavigationListItemPrivate::~QEXTNavigationListItemPrivate()
{
    m_childItems.clear();
}

QEXTNavigationListItem::QEXTNavigationListItem(QEXTNavigationListItem *parent)
    : QObject(), dd_ptr(new QEXTNavigationListItemPrivate(this))
{
    Q_D(QEXTNavigationListItem);
    this->setParentItem(parent);
}

QEXTNavigationListItem::QEXTNavigationListItem(const QString &text, QEXTNavigationListItem *parent)
    : QObject(), dd_ptr(new QEXTNavigationListItemPrivate(this))
{
    Q_D(QEXTNavigationListItem);
    d->m_text = text;
    this->setParentItem(parent);
}

QEXTNavigationListItem::QEXTNavigationListItem(const QString &text, const QPixmap &icon,
                                             QEXTNavigationListItem *parent)
    : QObject(), dd_ptr(new QEXTNavigationListItemPrivate(this))
{
    Q_D(QEXTNavigationListItem);
    d->m_text = text;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QEXTNavigationListItem::QEXTNavigationListItem(const QString &text, const QPixmap &icon,
                                             bool expand, QEXTNavigationListItem *parent)
    : QObject(), dd_ptr(new QEXTNavigationListItemPrivate(this))
{
    Q_D(QEXTNavigationListItem);
    d->m_text = text;
    d->m_expand = expand;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QEXTNavigationListItem::QEXTNavigationListItem(const QString &text, const QString &tip,
                                             const QPixmap &icon, QEXTNavigationListItem *parent)
    : QObject(), dd_ptr(new QEXTNavigationListItemPrivate(this))
{
    Q_D(QEXTNavigationListItem);
    d->m_text = text;
    d->m_tip = tip;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QEXTNavigationListItem::QEXTNavigationListItem(const QString &text, const QString &tip,
                                             const QPixmap &icon, bool expand, QEXTNavigationListItem *parent)
    : QObject(), dd_ptr(new QEXTNavigationListItemPrivate(this))
{
    Q_D(QEXTNavigationListItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_expand = expand;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QEXTNavigationListItem::QEXTNavigationListItem(const QString &text, const QChar &fontChar,
                                             QEXTNavigationListItem *parent)
    : QObject(), dd_ptr(new QEXTNavigationListItemPrivate(this))
{
    Q_D(QEXTNavigationListItem);
    d->m_text = text;
    d->m_fontIcon = fontChar;
    this->setParentItem(parent);
}

QEXTNavigationListItem::QEXTNavigationListItem(const QString &text, const QChar &fontChar,
                                             bool expand, QEXTNavigationListItem *parent)
    : QObject(), dd_ptr(new QEXTNavigationListItemPrivate(this))
{
    Q_D(QEXTNavigationListItem);
    d->m_text = text;
    d->m_fontIcon = fontChar;
    d->m_expand = expand;
    this->setParentItem(parent);
}

QEXTNavigationListItem::QEXTNavigationListItem(const QString &text, const QString &tip,
                                             const QChar &fontChar, QEXTNavigationListItem *parent)
    : QObject(), dd_ptr(new QEXTNavigationListItemPrivate(this))
{
    Q_D(QEXTNavigationListItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_fontIcon = fontChar;
    this->setParentItem(parent);
}

QEXTNavigationListItem::QEXTNavigationListItem(const QString &text, const QString &tip,
                                             const QChar &fontChar, bool expand, QEXTNavigationListItem *parent)
    : QObject(), dd_ptr(new QEXTNavigationListItemPrivate(this))
{
    Q_D(QEXTNavigationListItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_fontIcon = fontChar;
    d->m_expand = expand;
    this->setParentItem(parent);
}

QEXTNavigationListItem::~QEXTNavigationListItem()
{
    this->setChecked(false);
    emit this->itemAboutToDestroyed(this);
}

QPixmap QEXTNavigationListItem::normalIcon() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_normalIcon;
}

QPixmap QEXTNavigationListItem::hoverIcon() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_hoverIcon;
}

QPixmap QEXTNavigationListItem::checkedIcon() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_checkedIcon;
}

QPixmap QEXTNavigationListItem::selectedIcon() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_selectedIcon;
}

void QEXTNavigationListItem::setIcon(const QPixmap &icon)
{
    this->setNormalIcon(icon);
    this->setHoverIcon(icon);
    this->setCheckedIcon(icon);
    this->setSelectedIcon(icon);
}

void QEXTNavigationListItem::setNormalIcon(const QPixmap &icon)
{
    Q_D(QEXTNavigationListItem);
    d->m_normalIcon = icon;
    emit this->iconChanged(this);
}

void QEXTNavigationListItem::setHoverIcon(const QPixmap &icon)
{
    Q_D(QEXTNavigationListItem);
    d->m_hoverIcon = icon;
    emit this->iconChanged(this);
}

void QEXTNavigationListItem::setCheckedIcon(const QPixmap &icon)
{
    Q_D(QEXTNavigationListItem);
    d->m_checkedIcon = icon;
    emit this->iconChanged(this);
}

void QEXTNavigationListItem::setSelectedIcon(const QPixmap &icon)
{
    Q_D(QEXTNavigationListItem);
    d->m_selectedIcon = icon;
    emit this->iconChanged(this);
}

QChar QEXTNavigationListItem::fontIcon() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_fontIcon;
}

void QEXTNavigationListItem::setFontIcon(const QChar &ch)
{
    Q_D(QEXTNavigationListItem);
    if (ch != d->m_fontIcon)
    {
        d->m_fontIcon = ch;
        emit this->fontIconChanged(this);
    }
}

QString QEXTNavigationListItem::text() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_text;
}

void QEXTNavigationListItem::setText(const QString &text)
{
    Q_D(QEXTNavigationListItem);
    if (text != d->m_text)
    {
        d->m_text = text;
        emit this->textChanged(this);
    }
}

QString QEXTNavigationListItem::tip() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_tip;
}

void QEXTNavigationListItem::setTip(const QString &tip)
{
    Q_D(QEXTNavigationListItem);
    if (tip != d->m_tip)
    {
        d->m_tip = tip;
        emit this->tipChanged(this);
    }
}

bool QEXTNavigationListItem::isExpand() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_expand;
}

void QEXTNavigationListItem::setExpand(const bool &expand)
{
    Q_D(QEXTNavigationListItem);
    if (expand != d->m_expand)
    {
        d->m_expand = expand;
        emit this->expandChanged(this);
    }
}

bool QEXTNavigationListItem::isVisible() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_visiable;
}

void QEXTNavigationListItem::setVisible(const bool &visiable)
{
    Q_D(QEXTNavigationListItem);
    if (visiable != d->m_visiable)
    {
        if (!visiable)
        {
            QList<QEXTNavigationListItem *>::const_iterator iter;
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

bool QEXTNavigationListItem::isEnabled() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_enable;
}

void QEXTNavigationListItem::setEnable(const bool &enable)
{
    Q_D(QEXTNavigationListItem);
    if (enable != d->m_enable)
    {
        d->m_enable = enable;
        emit this->enableChanged(this);
    }
}

Qt::CheckState QEXTNavigationListItem::checkState() const
{
    Q_D(const QEXTNavigationListItem);
    if (this->isParentItem())
    {
        QList<QEXTNavigationListItem *>::const_iterator iter;
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

bool QEXTNavigationListItem::isChecked() const
{
    return Qt::Checked == this->checkState();
}

bool QEXTNavigationListItem::setChecked(bool check)
{
    Q_D(QEXTNavigationListItem);
    if (!this->isVisible() && check)
    {
        qWarning() << "QEXTNavigationListItem::setChecked(): item not visiable, can not set check";
        return false;
    }
    if (!this->isEnabled() && check)
    {
        qWarning() << "QEXTNavigationListItem::setChecked(): item not enabled, can not set check";
        return false;
    }
    if (this->isParentItem())
    {
        qWarning() << "QEXTNavigationListItem::setChecked(): item is parent, can not set check";
        return false;
    }
    if (check != d->m_checkd)
    {
        d->m_checkd = check;
        emit this->checkChanged(this);
    }
    return true;
}

bool QEXTNavigationListItem::isLastVisibleItem() const
{
    Q_D(const QEXTNavigationListItem);
    if (!d->m_parent.isNull() && d->m_visiable)
    {
        return this == d->m_parent->visiableChildItems().last();
    }
    return false;
}

bool QEXTNavigationListItem::isChildItem() const
{
    Q_D(const QEXTNavigationListItem);
    return !d->m_parent.isNull();
}

bool QEXTNavigationListItem::isParentItem() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_parent.isNull();
}

QEXTNavigationListItem *QEXTNavigationListItem::parentItem() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_parent.data();
}

bool QEXTNavigationListItem::setParentItem(QEXTNavigationListItem *parent)
{
    Q_D(QEXTNavigationListItem);
    if (this == parent)
    {
        qWarning() << "QEXTNavigationListItem::setParentItem(): parent can not equal to item self";
        return false;
    }
    if (!d->m_childItems.isEmpty())
    {
        qWarning() << "QEXTNavigationListItem::setParentItem(): current item is parent item, can not set parent";
        return false;
    }
    if (d->m_parent.data() != parent)
    {
        QEXTNavigationListItem *oldParent = d->m_parent.data();
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
            connect(this, SIGNAL(itemAboutToDestroyed(QEXTNavigationListItem*)),
                    parent, SLOT(onChildItemAboutToBeDestroyed(QEXTNavigationListItem*)));
            emit parent->childItemInserted(this, parent);
        }

        return true;
    }
    return false;
}

int QEXTNavigationListItem::childItemsCount() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_childItems.count();
}

int QEXTNavigationListItem::visiableChildItemsCount() const
{
    return this->visiableChildItems().count();
}

QList<QEXTNavigationListItem *> QEXTNavigationListItem::childItems() const
{
    Q_D(const QEXTNavigationListItem);
    return d->m_childItems;
}

QList<QEXTNavigationListItem *> QEXTNavigationListItem::visiableChildItems() const
{
    Q_D(const QEXTNavigationListItem);
    QList<QEXTNavigationListItem *> result;
    QList<QEXTNavigationListItem *>::const_iterator iter;
    for (iter = d->m_childItems.begin(); iter != d->m_childItems.end(); ++iter)
    {
        if ((*iter)->isVisible())
        {
            result.append(*iter);
        }
    }
    return result;
}

void QEXTNavigationListItem::onChildItemAboutToBeDestroyed(QEXTNavigationListItem *item)
{
    Q_D(QEXTNavigationListItem);
    if (item && d->m_childItems.contains(item))
    {
        emit this->childItemAboutToBeRemoved(item, this);
        d->m_childItems.removeOne(item);
        emit this->childItemRemoved(item, this);
    }
}



QEXTNavListDelegate::QEXTNavListDelegate(QEXTNavigationListViewPrivate *navData)
    : QStyledItemDelegate()
{
    m_navData = navData;

    QFontDatabase fontDb;
    if (!fontDb.families().contains("FontAwesome"))
    {
        Q_INIT_RESOURCE(QEXTWidgets);
        int fontId = fontDb.addApplicationFont(":/QEXTWidgets/font/fontawesome-webfont.ttf");
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

QEXTNavListDelegate::~QEXTNavListDelegate() {}

QSize QEXTNavListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QEXTNavigationListItem *item = (QEXTNavigationListItem *)index.data(Qt::UserRole).toLongLong();

    QSize size(50, item->isParentItem() ? m_navData->m_parentHeight : m_navData->m_childHeight);
    return size;
}

void QEXTNavListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    QEXTNavigationListItem *item = (QEXTNavigationListItem *)index.data(Qt::UserRole).toLongLong();

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

    int fontSize = parent ? m_navData->m_parentFontSize : m_navData->m_childFontSize;
    QPixmap icon;
    QColor bgColor, textColor, tipBgColor, tipTextColor, iconColor;
    if (checked)
    {
        bgColor = parent ? m_navData->m_parentBackgroundCheckedColor : m_navData->m_childBackgroundCheckedColor;
        textColor = parent ? m_navData->m_parentTextCheckedColor : m_navData->m_childTextCheckedColor;
        tipBgColor = parent ? m_navData->m_parentTextCheckedColor : m_navData->m_childTextCheckedColor;
        tipTextColor = parent ? m_navData->m_parentBackgroundCheckedColor : m_navData->m_childBackgroundCheckedColor;
        iconColor = parent ? m_navData->m_parentTextCheckedColor : m_navData->m_childTextCheckedColor;
        icon = item->checkedIcon();
    }
    else if (option.state & QStyle::State_Selected && enabled && parentEnabled)
    {
        bgColor = parent ? m_navData->m_parentBackgroundSelectedColor : m_navData->m_childBackgroundSelectedColor;
        textColor = parent ? m_navData->m_parentTextSelectedColor : m_navData->m_childTextSelectedColor;
        tipBgColor = parent ? m_navData->m_parentTextSelectedColor : m_navData->m_childTextSelectedColor;
        tipTextColor = parent ? m_navData->m_parentBackgroundSelectedColor : m_navData->m_childBackgroundSelectedColor;
        iconColor = parent ? m_navData->m_parentTextSelectedColor : m_navData->m_childTextSelectedColor;
        icon = item->selectedIcon();
    }
    else if (option.state & QStyle::State_MouseOver && enabled && parentEnabled)
    {
        bgColor = parent ? m_navData->m_parentBackgroundHoverColor : m_navData->m_childBackgroundHoverColor;
        textColor = parent ? m_navData->m_parentTextHoverColor : m_navData->m_childTextHoverColor;
        tipBgColor = parent ? m_navData->m_parentTextCheckedColor : m_navData->m_childTextCheckedColor;
        tipTextColor = parent ? m_navData->m_parentBackgroundCheckedColor : m_navData->m_childBackgroundCheckedColor;
        iconColor = parent ? m_navData->m_parentTextHoverColor : m_navData->m_childTextHoverColor;
        icon = item->hoverIcon();
    }
    else
    {
        bgColor = parent ? m_navData->m_parentBackgroundNormalColor : m_navData->m_childBackgroundNormalColor;
        textColor = parent ? m_navData->m_parentTextNormalColor : m_navData->m_childTextNormalColor;
        tipBgColor = parent ? m_navData->m_parentBackgroundCheckedColor : m_navData->m_childBackgroundCheckedColor;
        tipTextColor = parent ? m_navData->m_parentTextCheckedColor : m_navData->m_childTextCheckedColor;
        iconColor = parent ? m_navData->m_parentTextNormalColor : m_navData->m_childTextNormalColor;
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

    int lineWidth = m_navData->m_lineWidth;
    if (!parent && m_navData->m_lineVisible && lineWidth > 0)
    {
        if (checked)
        {
            float offset = (float)lineWidth / 2;

            QPointF pointTop(x, y + offset);
            QPointF pointBottom(x, height + y - offset);
            if (!m_navData->m_lineLeft)
            {
                pointTop.setX(width);
                pointBottom.setX(width);
            }

            painter->setPen(QPen(m_navData->m_lineColor, lineWidth));
            painter->drawLine(pointTop, pointBottom);
        }
    }

    int triangleWidth = m_navData->m_triangleWidth;
    if (!parent && m_navData->m_triangleVisible && triangleWidth > 0)
    {
        if (checked)
        {
            QFont font = m_iconFont;
            font.setPixelSize(fontSize + triangleWidth);
            painter->setFont(font);
            painter->setPen(m_navData->m_triangleColor);

            if (m_navData->m_triangleLeft)
            {
                painter->drawText(optionRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf0da));
            }
            else
            {
                painter->drawText(optionRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf0d9));
            }
        }
    }

    if (m_navData->m_separateVisible)
    {
        if (item->isParentItem() || (item->isChildItem() && item->isLastVisibleItem()))
        {
            painter->setPen(QPen(m_navData->m_separateColor, m_navData->m_separateHeight));
            painter->drawLine(QPointF(x, y + height), QPointF(x + width, y + height));
        }
    }

    QString text = item->text();
    if (!text.isEmpty())
    {
        int margin = m_navData->m_parentMargin;
        if (item->isChildItem())
        {
            margin = m_navData->m_childMargin;
            fontSize = m_navData->m_childFontSize;
        }

        QRect textRect = optionRect;
        textRect.setWidth(width - margin);
        textRect.setX(x + margin);

        QFont font = m_navData->itemFont();
        font.setPixelSize(fontSize);
        painter->setFont(font);
        painter->setPen(textColor);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }

    QString tip = item->tip();
    if (m_navData->m_tipVisible && !tip.isEmpty())
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
        tipRect.setLeft(optionRect.right() - m_navData->m_tipWidth - 5);
        tipRect.setRight(optionRect.right() - 5);

        QFont font = m_navData->itemFont();
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
    iconRect.setLeft(parent ? m_navData->m_parentIconMargin : m_navData->m_childIconMargin);

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

    iconRect.setRight(optionRect.width() - 10);
    if (!(m_navData->m_tipVisible && !item->tip().isEmpty()) && m_navData->m_rightIconVisible && parent && hasChildItems)
    {
        if (!item->isExpand())
        {
            painter->drawText(iconRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf054));
        }
        else
        {
            painter->drawText(iconRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf078));
        }
    }
}



QEXTNavigationListModelPrivate::QEXTNavigationListModelPrivate(QEXTNavigationListModel *q)
    : q_ptr(q)
{

}

QEXTNavigationListModelPrivate::~QEXTNavigationListModelPrivate()
{
    this->deleteAllItems();
    m_parentItemList.clear();
    m_visiableItemList.clear();
}

void QEXTNavigationListModelPrivate::deleteAllItems()
{
    QSet<QEXTNavigationListItem *>::iterator iter;
    for (iter = m_allItemSet.begin(); iter != m_allItemSet.end(); ++iter)
    {
        (*iter)->disconnect();
        (*iter)->deleteLater();
    }
    m_allItemSet.clear();
}

void QEXTNavigationListModelPrivate::refreshVisibleList()
{
    m_visiableItemList.clear();
    QList<QEXTNavigationListItem *>::iterator iter;
    for (iter = m_parentItemList.begin(); iter != m_parentItemList.end(); ++iter)
    {
        if ((*iter)->isVisible())
        {
            m_visiableItemList.append(*iter);
            if ((*iter)->isExpand())
            {
                QList<QEXTNavigationListItem *> childItems = (*iter)->visiableChildItems();
                if (!childItems.isEmpty())
                {
                    m_visiableItemList.append(childItems);
                }
            }
        }
    }
}

void QEXTNavigationListModelPrivate::initAllItemsConnection()
{
    QSet<QEXTNavigationListItem *>::iterator iter;
    for (iter = m_allItemSet.begin(); iter != m_allItemSet.end(); ++iter)
    {
        QEXTNavigationListItem *item = *iter;
        this->initItemConnection(item);
    }
}

void QEXTNavigationListModelPrivate::initItemConnection(QEXTNavigationListItem *item)
{
    Q_Q(QEXTNavigationListModel);
    item->disconnect(q);
    QObject::connect(item, SIGNAL(itemAboutToDestroyed(QEXTNavigationListItem*)), q, SLOT(onItemAboutToDestroyed(QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(iconChanged(QEXTNavigationListItem*)), q, SLOT(onItemChanged(QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(fontIconChanged(QEXTNavigationListItem*)), q, SLOT(onItemChanged(QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(textChanged(QEXTNavigationListItem*)), q, SLOT(onItemChanged(QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(tipChanged(QEXTNavigationListItem*)), q, SLOT(onItemChanged(QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(enableChanged(QEXTNavigationListItem*)), q, SLOT(onItemChanged(QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(expandChanged(QEXTNavigationListItem*)), q, SLOT(onItemExpandChanged(QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(checkChanged(QEXTNavigationListItem*)), q, SLOT(onItemCheckChanged(QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(visiableAboutToBeChanged(QEXTNavigationListItem*)),
                     q, SLOT(onItemVisibleAboutToBeChanged(QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(visiableChanged(QEXTNavigationListItem*)),
                     q, SLOT(onItemVisibleChanged(QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(childItemAboutToBeInserted(QEXTNavigationListItem*,QEXTNavigationListItem*)),
                     q, SLOT(onChildItemAboutToBeInserted(QEXTNavigationListItem*,QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(childItemInserted(QEXTNavigationListItem*,QEXTNavigationListItem*)),
                     q, SLOT(onChildItemInserted(QEXTNavigationListItem*,QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(childItemAboutToBeRemoved(QEXTNavigationListItem*,QEXTNavigationListItem*)),
                     q, SLOT(onChildItemAboutToBeRemoved(QEXTNavigationListItem*,QEXTNavigationListItem*)));
    QObject::connect(item, SIGNAL(childItemRemoved(QEXTNavigationListItem*,QEXTNavigationListItem*)),
                     q, SLOT(onChildItemRemoved(QEXTNavigationListItem*,QEXTNavigationListItem*)));
}


QEXTNavigationListModel::QEXTNavigationListModel(QObject *parent)
    : QAbstractListModel(parent), dd_ptr(new QEXTNavigationListModelPrivate(this))
{

}

QEXTNavigationListModel::~QEXTNavigationListModel()
{

}

QEXTNavigationListItem *QEXTNavigationListModel::checkedItem() const
{
    Q_D(const QEXTNavigationListModel);
    return d->m_checkedItem.data();
}

QList<QEXTNavigationListItem *> QEXTNavigationListModel::allItems() const
{
    Q_D(const QEXTNavigationListModel);
    return d->m_allItemSet.toList();
}

QList<QEXTNavigationListItem *> QEXTNavigationListModel::parentItems() const
{
    Q_D(const QEXTNavigationListModel);
    return d->m_parentItemList;
}

QList<QEXTNavigationListItem *> QEXTNavigationListModel::visiableItems() const
{
    Q_D(const QEXTNavigationListModel);
    return d->m_visiableItemList;
}

int QEXTNavigationListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const QEXTNavigationListModel);
    return d->m_visiableItemList.size();
}

QVariant QEXTNavigationListModel::data(const QModelIndex &index, int role) const
{
    Q_D(const QEXTNavigationListModel);
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

Qt::ItemFlags QEXTNavigationListModel::flags(const QModelIndex &index) const
{
    Q_D(const QEXTNavigationListModel);
    if (index.isValid())
    {
        int row = index.row();
        if (row >= 0 && row < d->m_visiableItemList.size())
        {
            QEXTNavigationListItem *item = d->m_visiableItemList.at(row);
            QEXTNavigationListItem *parentItem = item->parentItem();
            if (!item->isEnabled() || (parentItem && !parentItem->isEnabled()))
            {
                return item->isParentItem() ? Qt::ItemIsEnabled : Qt::NoItemFlags;
            }
        }
    }
    return QAbstractListModel::flags(index);
}

void QEXTNavigationListModel::setItems(const QStringList &items)
{
    if (!items.isEmpty())
    {
        this->beginResetModel();

        bool ok;
        QStringList itemStringList = items;
        QList<QEXTNavigationListItem *> parentItemList;
        QMutableStringListIterator iter(itemStringList);
        while (iter.hasNext())
        {
            QString item = iter.next();
            QStringList list = item.split("|");
            if (list.count() < 5)
            {
                qWarning() << QString("QEXTNavigationListModel::setItems(): item string %1 invalid").arg(item);
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
                QEXTNavigationListItem *parentItem = new QEXTNavigationListItem;
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
                        qWarning() << QString("QEXTNavigationListModel::setItems(): item string %1 invalid").arg(item);
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
                        QEXTNavigationListItem *childItem = new QEXTNavigationListItem;
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
                qWarning() << QString("QEXTNavigationListModel::setItems(): item string %1 invalid").arg(item);
                checkIter.remove();
                continue;
            }
            QString text = list.at(0);
            QString parentText = list.at(1);
            QString expand = list.at(2);
            QString tip = list.at(3);
            QString icon = list.at(4);
            icon = icon.replace("0x", "");
            QEXTNavigationListItem *parentItem = new QEXTNavigationListItem;
            parentItemList.append(parentItem);
            parentItem->setExpand(expand.toInt());
            parentItem->setText(text);
            parentItem->setTip(tip);
            if (!icon.isEmpty())
            {
                parentItem->setFontIcon(QChar(icon.toInt(&ok, 16)));
            }
            checkIter.remove();
            qWarning() << QString("QEXTNavigationListModel::setItems(): item string %1 parent %2 not exist").arg(item).arg(parentText);
        }
        this->setItems(parentItemList);

        this->endResetModel();
    }
}


void QEXTNavigationListModel::setItems(const QList<QEXTNavigationListItem *> &items)
{
    Q_D(QEXTNavigationListModel);
    if (!items.isEmpty())
    {
        this->beginResetModel();

        QSet<QEXTNavigationListItem *> cacheItemSet;
        d->m_visiableItemList.clear();
        d->m_parentItemList.clear();

        QList<QEXTNavigationListItem *>::const_iterator iter;
        for (iter = items.begin(); iter != items.end(); ++iter)
        {
            QEXTNavigationListItem *item = *iter;
            if (item->isParentItem())
            {
                cacheItemSet.insert(item);
                d->m_parentItemList.append(item);
                if (d->m_allItemSet.contains(item))
                {
                    d->m_allItemSet.remove(item);
                }

                QList<QEXTNavigationListItem *> childItems = item->childItems();
                QList<QEXTNavigationListItem *>::iterator childIter;
                for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                {
                    QEXTNavigationListItem *childItem = *childIter;
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

void QEXTNavigationListModel::expandCollapseItem(const QModelIndex &index)
{
    Q_D(QEXTNavigationListModel);
    QEXTNavigationListItem *item = d->m_visiableItemList.at(index.row());
    if (0 != item->visiableChildItemsCount())
    {
        item->setExpand(!item->isExpand());
    }
}

void QEXTNavigationListModel::onItemAboutToDestroyed(QEXTNavigationListItem *item)
{
    Q_D(QEXTNavigationListModel);
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

            QList<QEXTNavigationListItem *>::iterator iter;
            QList<QEXTNavigationListItem *> childItems = item->childItems();
            for (iter = childItems.begin(); iter != childItems.end(); ++iter)
            {
                QEXTNavigationListItem *childItem = *iter;
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

void QEXTNavigationListModel::onItemChanged(QEXTNavigationListItem *item)
{
    Q_D(QEXTNavigationListModel);
    int row = d->m_visiableItemList.indexOf(item);
    QModelIndex index = this->index(row, 0);
    emit this->dataChanged(index, index);
}

void QEXTNavigationListModel::onItemEnableChanged(QEXTNavigationListItem *item)
{
    Q_D(QEXTNavigationListModel);
    if (item->isVisible())
    {
        int row = d->m_visiableItemList.indexOf(item);
        int count = item->isParentItem() ? item->visiableChildItemsCount() : 0;
        QModelIndex index1 = this->index(row, 0);
        QModelIndex index2 = this->index(row + count, 0);
        emit this->dataChanged(index1, index2);
    }
}

void QEXTNavigationListModel::onItemExpandChanged(QEXTNavigationListItem *item)
{
    Q_D(QEXTNavigationListModel);
    QList<QEXTNavigationListItem *> visiableItems = item->visiableChildItems();
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

void QEXTNavigationListModel::onItemCheckChanged(QEXTNavigationListItem *item)
{
    Q_D(QEXTNavigationListModel);
    int row = d->m_visiableItemList.indexOf(item);
    QModelIndex index = this->index(row, 0);
    emit this->dataChanged(index, index);

    if (item->isChecked())
    {
        if (item != d->m_checkedItem.data())
        {
            QEXTNavigationListItem *oldCheckedItem = d->m_checkedItem.data();
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
            emit this->checkedItemChanged((QEXTNavigationListItem *)QEXT_DECL_NULLPTR);
        }
    }
}

void QEXTNavigationListModel::onItemVisibleAboutToBeChanged(QEXTNavigationListItem *item)
{
    Q_D(QEXTNavigationListModel);
    if (item->isVisible())
    {
        int row = d->m_visiableItemList.indexOf(item);
        int count = item->isExpand() ? item->visiableChildItemsCount() : 0;
        this->beginRemoveRows(QModelIndex(), row, row + count);
    }
    else
    {
        QList<QEXTNavigationListItem *> visiableChildItems = item->visiableChildItems();
        int visiableChildcount = (item->isExpand() && item->isParentItem() && item->isVisible()) ? visiableChildItems.size() : 0;
        int row = 0;
        bool located = false;
        QList<QEXTNavigationListItem *>::iterator iter;
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
                    QList<QEXTNavigationListItem *>::iterator childIter;
                    QList<QEXTNavigationListItem *> childItems = (*iter)->childItems();
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

void QEXTNavigationListModel::onItemVisibleChanged(QEXTNavigationListItem *item)
{
    Q_D(QEXTNavigationListModel);
    if (item->isVisible())
    {
        int row = 0;
        bool located = false;
        QList<QEXTNavigationListItem *>::iterator iter;
        for (iter = d->m_parentItemList.begin(); iter != d->m_parentItemList.end(); ++iter)
        {
            if (located)
            {
                break;
            }
            if ((*iter)->isVisible())
            {
                QList<QEXTNavigationListItem *> childItems = (*iter)->childItems();
                if (item == *iter)
                {
                    d->m_visiableItemList.insert(row++, *iter);
                    if ((*iter)->isExpand())
                    {
                        QList<QEXTNavigationListItem *>::iterator childIter;
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
                    QList<QEXTNavigationListItem *>::iterator childIter;
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

void QEXTNavigationListModel::onChildItemAboutToBeInserted(QEXTNavigationListItem *item, QEXTNavigationListItem *parent)
{
    Q_D(QEXTNavigationListModel);
    if (item->isVisible() && parent->isVisible())
    {
        int index = d->m_visiableItemList.indexOf(parent);
        int row = parent->visiableChildItemsCount() + 1;
        this->beginInsertRows(QModelIndex(), index + row + 1, index + row + 1);
    }
}

void QEXTNavigationListModel::onChildItemInserted(QEXTNavigationListItem *item, QEXTNavigationListItem *parent)
{
    Q_D(QEXTNavigationListModel);
    if (item->isVisible() && parent->isVisible())
    {
        int index = d->m_visiableItemList.indexOf(parent);
        int row = parent->visiableChildItemsCount();
        d->m_visiableItemList.insert(index + row + 1, item);
        this->endInsertRows();
    }
}

void QEXTNavigationListModel::onChildItemAboutToBeRemoved(QEXTNavigationListItem *item, QEXTNavigationListItem *parent)
{
    Q_D(QEXTNavigationListModel);
    if (d->m_visiableItemList.contains(item))
    {
        int row = d->m_visiableItemList.indexOf(parent);
        this->beginRemoveRows(QModelIndex(), row, row);
    }
}

void QEXTNavigationListModel::onChildItemRemoved(QEXTNavigationListItem *item, QEXTNavigationListItem *parent)
{
    Q_D(QEXTNavigationListModel);
    d->m_allItemSet.remove(item);
    if (d->m_visiableItemList.contains(item))
    {
        d->m_visiableItemList.removeOne(item);
        this->endRemoveRows();
    }
}



QEXTNavigationListViewPrivate::QEXTNavigationListViewPrivate(QEXTNavigationListView *q)
    : q_ptr(q)
{
    m_rightIconVisible = true;
    m_tipVisible = true;
    m_tipWidth = 40;

    m_separateVisible = true;
    m_separateHeight = 1;
    m_separateColor = QColor(40, 43, 51);

    m_lineLeft = true;
    m_lineVisible = true;
    m_lineWidth = 6;
    m_lineColor = QColor(0, 187, 158);

    m_triangleLeft = false;
    m_triangleVisible = true;
    m_triangleWidth = 6;
    m_triangleColor = QColor(250, 250, 250);

    m_parentIconMargin = 10;
    m_parentMargin = 30;
    m_parentFontSize = 12;
    m_parentHeight = 35;
    m_parentBackgroundNormalColor = QColor(57, 61, 73);
    m_parentBackgroundCheckedColor = QColor(78, 83, 102);
    m_parentBackgroundSelectedColor = QColor(78, 83, 102);
    m_parentBackgroundHoverColor = QColor(78, 83, 102);
    m_parentTextNormalColor = QColor(250, 250, 250);
    m_parentTextCheckedColor = QColor(250, 250, 250);
    m_parentTextSelectedColor = QColor(250, 250, 250);
    m_parentTextHoverColor = QColor(250, 250, 250);
    m_childIconMargin = 15;
    m_childMargin = 35;
    m_childFontSize = 12;
    m_childHeight = 30;
    m_childBackgroundNormalColor = QColor(40, 43, 51);
    m_childBackgroundCheckedColor = QColor(20, 20, 20);
    m_childBackgroundSelectedColor = QColor(20, 20, 20);
    m_childBackgroundHoverColor = QColor(20, 20, 20);
    m_childTextNormalColor = QColor(180, 180, 180);
    m_childTextCheckedColor = QColor(250, 250, 250);
    m_childTextSelectedColor = QColor(250, 250, 250);
    m_childTextHoverColor = QColor(255, 255, 255);
    m_backgroundColor = m_parentBackgroundNormalColor;

    m_expendMode = QEXTNavigationListView::ExpendMode_SingleClick;
    m_delegate.reset(new QEXTNavListDelegate(this));
    m_listView.reset(new QEXTNavListView);
    m_listView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_listView->setMouseTracking(true);
    m_listView->setAutoFillBackground(true);
    m_listView->setItemDelegate(m_delegate.data());
}

QEXTNavigationListViewPrivate::~QEXTNavigationListViewPrivate()
{
    if (!m_model.isNull())
    {
        m_model->deleteLater();
    }
}

QFont QEXTNavigationListViewPrivate::itemFont() const
{
    Q_Q(const QEXTNavigationListView);
    return q->font();
}


QEXTNavigationListView::QEXTNavigationListView(QWidget *parent)
    : QWidget(parent), dd_ptr(new QEXTNavigationListViewPrivate(this))
{
    Q_D(QEXTNavigationListView);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(d->m_listView.data());
    this->setLayout(layout);
    this->setBackgroundColor(d->m_parentBackgroundNormalColor);
    this->setModel(new QEXTNavigationListModel);
    connect(d->m_listView.data(), SIGNAL(pressed(QModelIndex)), this, SLOT(onItemPressed(QModelIndex)));
}

QEXTNavigationListView::~QEXTNavigationListView()
{

}

QListView *QEXTNavigationListView::view() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_listView.data();
}

QEXTNavigationListModel *QEXTNavigationListView::model() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_model.data();
}

QEXTNavigationListItem *QEXTNavigationListView::selectedItem() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_selectedItem.data();
}

QEXTNavigationListItem *QEXTNavigationListView::checkedItem() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_model->checkedItem();
}

QList<QEXTNavigationListItem *> QEXTNavigationListView::allItems() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_model->allItems();
}

QList<QEXTNavigationListItem *> QEXTNavigationListView::parentItems() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_model->parentItems();
}

QList<QEXTNavigationListItem *> QEXTNavigationListView::visiableItems() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_model->visiableItems();
}

void QEXTNavigationListView::paintEvent(QPaintEvent *event)
{
    Q_D(QEXTNavigationListView);
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(d->m_parentBackgroundNormalColor);
    painter.drawRect(this->rect());
    QStyleOption opt;
    opt.init(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void QEXTNavigationListView::onItemPressed(const QModelIndex &index)
{
    QEXTNavigationListItem *item = (QEXTNavigationListItem *)index.data(Qt::UserRole).toLongLong();
    if (item)
    {
        if (item->isChildItem())
        {
            this->setSelectedItem(item);
        }
        emit this->itemPressed(item);
    }
}

bool QEXTNavigationListView::itemRightIconVisible() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_rightIconVisible;
}

bool QEXTNavigationListView::itemTipVisible() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_tipVisible;
}

int QEXTNavigationListView::itemTipWidth() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_tipWidth;
}

bool QEXTNavigationListView::itemSeparateVisible() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_separateVisible;
}

int QEXTNavigationListView::itemSeparateHeight() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_separateHeight;
}

QColor QEXTNavigationListView::itemSeparateColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_separateColor;
}

bool QEXTNavigationListView::itemLineLeft() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_lineLeft;
}

bool QEXTNavigationListView::itemLineVisible() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_lineVisible;
}

int QEXTNavigationListView::itemLineWidth() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_lineWidth;
}

QColor QEXTNavigationListView::itemLineColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_lineColor;
}

bool QEXTNavigationListView::itemTriangleLeft() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_triangleLeft;
}

bool QEXTNavigationListView::itemTriangleVisible() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_triangleVisible;
}

int QEXTNavigationListView::itemTriangleWidth() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_triangleWidth;
}

QColor QEXTNavigationListView::itemTriangleColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_triangleColor;
}

QColor QEXTNavigationListView::backgroundColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_backgroundColor;
}

int QEXTNavigationListView::parentItemIconMargin() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentIconMargin;
}

int QEXTNavigationListView::parentItemMargin() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentMargin;
}

int QEXTNavigationListView::parentItemFontSize() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentFontSize;
}

int QEXTNavigationListView::parentItemHeight() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentHeight;
}

QColor QEXTNavigationListView::parentItemNormalBackgroundColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentBackgroundNormalColor;
}

QColor QEXTNavigationListView::parentItemCheckedBackgroundColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentBackgroundCheckedColor;
}

QColor QEXTNavigationListView::parentItemSelectedBackgroundColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentBackgroundSelectedColor;
}

QColor QEXTNavigationListView::parentItemHoverBackgroundColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentBackgroundHoverColor;
}

QColor QEXTNavigationListView::parentItemNormalTextColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentTextNormalColor;
}

QColor QEXTNavigationListView::parentItemCheckedTextColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentTextCheckedColor;
}

QColor QEXTNavigationListView::parentItemSelectedTextColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentTextSelectedColor;
}

QColor QEXTNavigationListView::parentItemHoverTextColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_parentTextHoverColor;
}

int QEXTNavigationListView::childItemIconMargin() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childIconMargin;
}

int QEXTNavigationListView::childItemMargin() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childMargin;
}

int QEXTNavigationListView::childItemFontSize() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childFontSize;
}

int QEXTNavigationListView::childItemHeight() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childHeight;
}

QColor QEXTNavigationListView::childItemNormalBackgroundColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childBackgroundNormalColor;
}

QColor QEXTNavigationListView::childItemCheckedBackgroundColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childBackgroundCheckedColor;
}

QColor QEXTNavigationListView::childItemSelectedBackgroundColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childBackgroundSelectedColor;
}

QColor QEXTNavigationListView::childItemHoverBackgroundColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childBackgroundHoverColor;
}

QColor QEXTNavigationListView::childItemNormalTextColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childTextNormalColor;
}

QColor QEXTNavigationListView::childItemCheckedTextColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childTextCheckedColor;
}

QColor QEXTNavigationListView::childItemSelectedTextColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childTextSelectedColor;
}

QColor QEXTNavigationListView::childItemHoverTextColor() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_childTextHoverColor;
}

QEXTNavigationListView::ExpendMode QEXTNavigationListView::expendMode() const
{
    Q_D(const QEXTNavigationListView);
    return d->m_expendMode;
}

QSize QEXTNavigationListView::sizeHint() const
{
    return QSize(200, 300);
}

QSize QEXTNavigationListView::minimumSizeHint() const
{
    return QSize(20, 20);
}

void QEXTNavigationListView::setModel(QEXTNavigationListModel *model)
{
    Q_D(QEXTNavigationListView);
    if (d->m_model.data() != model)
    {
        if (!d->m_model.isNull())
        {
            disconnect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)), model, SLOT(expandCollapseItem(QModelIndex)));
            disconnect(d->m_model.data(), SIGNAL(checkedItemChanged(QEXTNavigationListItem*)), this, SIGNAL(checkedItemChanged(QEXTNavigationListItem*)));
            d->m_model->deleteLater();
            d->m_model = QEXT_DECL_NULLPTR;
            d->m_listView->setModel(d->m_model.data());
        }
        if (model)
        {
            d->m_model = model;
            d->m_listView->setModel(d->m_model.data());
            connect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)), model, SLOT(expandCollapseItem(QModelIndex)));
            connect(d->m_model.data(), SIGNAL(checkedItemChanged(QEXTNavigationListItem*)), this, SIGNAL(checkedItemChanged(QEXTNavigationListItem*)));
        }
    }
}

QList<QEXTNavigationListItem *> QEXTNavigationListView::setItems(const QString &items)
{
    Q_D(QEXTNavigationListView);
    QStringList item = items.split(",");
    if (d->m_stringItems != item)
    {
        d->m_stringItems = item;
        d->m_model->setItems(item);
    }
    return d->m_model->parentItems();
}

QList<QEXTNavigationListItem *> QEXTNavigationListView::setItems(const QStringList &items)
{
    Q_D(QEXTNavigationListView);
    if (d->m_stringItems != items)
    {
        d->m_stringItems = items;
        d->m_model->setItems(items);
    }
    return d->m_model->parentItems();
}

void QEXTNavigationListView::setItems(const QList<QEXTNavigationListItem *> &items)
{
    Q_D(QEXTNavigationListView);
    if (d->m_items != items)
    {
        d->m_items = items;
        d->m_model->setItems(items);
    }
}

bool QEXTNavigationListView::setCurrentRow(int row)
{
    Q_D(QEXTNavigationListView);
    QList<QEXTNavigationListItem *> visiableItems = d->m_model->visiableItems();
    if (row >= 0 && row < visiableItems.size())
    {
        QEXTNavigationListItem *item = visiableItems.at(row);
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
        qWarning() << "QEXTNavigationListView::setCurrentRow(): row out of range in visiableItems";
        return false;
    }
}

bool QEXTNavigationListView::setSelectedItem(QEXTNavigationListItem *item)
{
    Q_D(QEXTNavigationListView);
    QList<QEXTNavigationListItem *> visiableItems = d->m_model->visiableItems();
    if (visiableItems.contains(item))
    {
        QList<QEXTNavigationListItem *>::iterator iter;
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
        qWarning() << "QEXTNavigationListView::setSelectedItem(): item not visiable, can not set selected";
        return false;
    }
}

void QEXTNavigationListView::setItemRightIconVisible(bool visible)
{
    Q_D(QEXTNavigationListView);
    if (visible != d->m_rightIconVisible)
    {
        d->m_rightIconVisible = visible;
        this->update();
    }
}

void QEXTNavigationListView::setItemTipVisible(bool visible)
{
    Q_D(QEXTNavigationListView);
    if (visible != d->m_tipVisible)
    {
        d->m_tipVisible = visible;
        this->update();
    }
}

void QEXTNavigationListView::setItemTipWidth(int width)
{
    Q_D(QEXTNavigationListView);
    if (width != d->m_tipWidth)
    {
        d->m_tipWidth = width;
        this->update();
    }
}

void QEXTNavigationListView::setItemSeparateVisible(bool visible)
{
    Q_D(QEXTNavigationListView);
    if (visible != d->m_separateVisible)
    {
        d->m_separateVisible = visible;
        this->update();
    }
}

void QEXTNavigationListView::setItemSeparateHeight(int height)
{
    Q_D(QEXTNavigationListView);
    if (height != d->m_separateHeight)
    {
        d->m_separateHeight = height;
        this->update();
    }
}

void QEXTNavigationListView::setItemSeparateColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_separateColor)
    {
        d->m_separateColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setItemLineLeft(bool inLeft)
{
    Q_D(QEXTNavigationListView);
    if (inLeft != d->m_lineLeft)
    {
        d->m_lineLeft = inLeft;
        this->update();
    }
}

void QEXTNavigationListView::setItemLineVisible(bool visible)
{
    Q_D(QEXTNavigationListView);
    if (visible != d->m_lineVisible)
    {
        d->m_lineVisible = visible;
        this->update();
    }
}

void QEXTNavigationListView::setItemLineWidth(int width)
{
    Q_D(QEXTNavigationListView);
    if (width != d->m_lineWidth)
    {
        d->m_lineWidth = width;
        this->update();
    }
}

void QEXTNavigationListView::setItemLineColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_lineColor)
    {
        d->m_lineColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setItemTriangleLeft(bool inLeft)
{
    Q_D(QEXTNavigationListView);
    if (inLeft != d->m_triangleLeft)
    {
        d->m_triangleLeft = inLeft;
        this->update();
    }
}

void QEXTNavigationListView::setItemTriangleVisible(bool visible)
{
    Q_D(QEXTNavigationListView);
    if (visible != d->m_triangleVisible)
    {
        d->m_triangleVisible = visible;
        this->update();
    }
}

void QEXTNavigationListView::setItemTriangleWidth(int width)
{
    Q_D(QEXTNavigationListView);
    if (width != d->m_triangleWidth)
    {
        d->m_triangleWidth = width;
        this->update();
    }
}

void QEXTNavigationListView::setItemTriangleColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_triangleColor)
    {
        d->m_triangleColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    QString styleSheet = QString("background-color: rgba(%1, %2, %3, %4);")
            .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
    d->m_listView->setStyleSheet(styleSheet);
    if (color != d->m_backgroundColor)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemIconMargin(int margin)
{
    Q_D(QEXTNavigationListView);
    if (margin != d->m_parentIconMargin)
    {
        d->m_parentIconMargin = margin;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemMargin(int margin)
{
    Q_D(QEXTNavigationListView);
    if (margin != d->m_parentMargin)
    {
        d->m_parentMargin = margin;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemFontSize(int size)
{
    Q_D(QEXTNavigationListView);
    if (size != d->m_parentFontSize)
    {
        d->m_parentFontSize = size;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemHeight(int height)
{
    Q_D(QEXTNavigationListView);
    if (height != d->m_parentHeight)
    {
        d->m_parentHeight = height;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemNormalBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_parentBackgroundNormalColor)
    {
        d->m_parentBackgroundNormalColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemCheckedBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_parentBackgroundCheckedColor)
    {
        d->m_parentBackgroundCheckedColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemSelectedBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_parentBackgroundSelectedColor)
    {
        d->m_parentBackgroundSelectedColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemHoverBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_parentBackgroundHoverColor)
    {
        d->m_parentBackgroundHoverColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemNormalTextColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_parentTextNormalColor)
    {
        d->m_parentTextNormalColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemCheckedTextColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_parentTextCheckedColor)
    {
        d->m_parentTextCheckedColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemSelectedTextColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_parentTextSelectedColor)
    {
        d->m_parentTextSelectedColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setParentItemHoverTextColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_parentTextHoverColor)
    {
        d->m_parentTextHoverColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemIconMargin(int margin)
{
    Q_D(QEXTNavigationListView);
    if (margin != d->m_childIconMargin)
    {
        d->m_childIconMargin = margin;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemMargin(int margin)
{
    Q_D(QEXTNavigationListView);
    if (margin != d->m_childMargin)
    {
        d->m_childMargin = margin;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemFontSize(int size)
{
    Q_D(QEXTNavigationListView);
    if (size != d->m_childFontSize)
    {
        d->m_childFontSize = size;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemHeight(int height)
{
    Q_D(QEXTNavigationListView);
    if (height != d->m_childHeight)
    {
        d->m_childHeight = height;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemNormalBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_childBackgroundNormalColor)
    {
        d->m_childBackgroundNormalColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemBackgroundCheckedColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_childBackgroundCheckedColor)
    {
        d->m_childBackgroundCheckedColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemSelectedBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_childBackgroundSelectedColor)
    {
        d->m_childBackgroundSelectedColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemHoverBackgroundColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_childBackgroundHoverColor)
    {
        d->m_childBackgroundHoverColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemNormalTextColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_childTextNormalColor)
    {
        d->m_childTextNormalColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemCheckedTextColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_childTextCheckedColor)
    {
        d->m_childTextCheckedColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemSelectedTextColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_childTextSelectedColor)
    {
        d->m_childTextSelectedColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setChildItemHoverTextColor(const QColor &color)
{
    Q_D(QEXTNavigationListView);
    if (color != d->m_childTextHoverColor)
    {
        d->m_childTextHoverColor = color;
        this->update();
    }
}

void QEXTNavigationListView::setExpendMode(const QEXTNavigationListView::ExpendMode &mode)
{
    Q_D(QEXTNavigationListView);
    if (d->m_expendMode != mode)
    {
        d->m_expendMode = mode;
        if (mode == ExpendMode_SingleClick)
        {
            disconnect(d->m_listView.data(), SIGNAL(doubleClicked(QModelIndex)), d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
            connect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)), d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
        }
        else if (mode == ExpendMode_DoubleClick)
        {
            disconnect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)), d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
            connect(d->m_listView.data(), SIGNAL(doubleClicked(QModelIndex)), d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
        }
        else if (mode == ExpendMode_NoClick)
        {
            disconnect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)), d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
            disconnect(d->m_listView.data(), SIGNAL(doubleClicked(QModelIndex)), d->m_model.data(), SLOT(expandCollapseItem(QModelIndex)));
        }
    }
}
