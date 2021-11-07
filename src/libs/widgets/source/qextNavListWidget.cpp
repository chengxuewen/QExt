#pragma execution_character_set("utf-8")

#include <qextNavListWidget.h>
#include <qextNavListWidget_p.h>

#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include <QFontDatabase>
#include <QMutableStringListIterator>


QEXTNavListWidgetItemPrivate::QEXTNavListWidgetItemPrivate(QEXTNavListWidgetItem *q)
    : q_ptr(q)
{
    m_expand = false;
    m_visiable = true;
    m_enable = true;
    m_checkd = false;
}

QEXTNavListWidgetItemPrivate::~QEXTNavListWidgetItemPrivate()
{
    m_childItems.clear();
}

QEXTNavListWidgetItem::QEXTNavListWidgetItem(QEXTNavListWidgetItem *parent)
    : QObject(), d_ptr(new QEXTNavListWidgetItemPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    this->setParentItem(parent);
}

QEXTNavListWidgetItem::QEXTNavListWidgetItem(const QString &text, QEXTNavListWidgetItem *parent)
    : QObject(), d_ptr(new QEXTNavListWidgetItemPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_text = text;
    this->setParentItem(parent);
}

QEXTNavListWidgetItem::QEXTNavListWidgetItem(const QString &text, const QPixmap &icon,
                                             QEXTNavListWidgetItem *parent)
    : QObject(), d_ptr(new QEXTNavListWidgetItemPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_text = text;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QEXTNavListWidgetItem::QEXTNavListWidgetItem(const QString &text, const QPixmap &icon,
                                             bool expand, QEXTNavListWidgetItem *parent)
    : QObject(), d_ptr(new QEXTNavListWidgetItemPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_text = text;
    d->m_expand = expand;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QEXTNavListWidgetItem::QEXTNavListWidgetItem(const QString &text, const QString &tip,
                                             const QPixmap &icon, QEXTNavListWidgetItem *parent)
    : QObject(), d_ptr(new QEXTNavListWidgetItemPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_text = text;
    d->m_tip = tip;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QEXTNavListWidgetItem::QEXTNavListWidgetItem(const QString &text, const QString &tip,
                                             const QPixmap &icon, bool expand, QEXTNavListWidgetItem *parent)
    : QObject(), d_ptr(new QEXTNavListWidgetItemPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_expand = expand;
    this->setIcon(icon);
    this->setParentItem(parent);
}

QEXTNavListWidgetItem::QEXTNavListWidgetItem(const QString &text, const QChar &fontChar,
                                             QEXTNavListWidgetItem *parent)
    : QObject(), d_ptr(new QEXTNavListWidgetItemPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_text = text;
    d->m_fontIcon = fontChar;
    this->setParentItem(parent);
}

QEXTNavListWidgetItem::QEXTNavListWidgetItem(const QString &text, const QChar &fontChar,
                                             bool expand, QEXTNavListWidgetItem *parent)
    : QObject(), d_ptr(new QEXTNavListWidgetItemPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_text = text;
    d->m_fontIcon = fontChar;
    d->m_expand = expand;
    this->setParentItem(parent);
}

QEXTNavListWidgetItem::QEXTNavListWidgetItem(const QString &text, const QString &tip,
                                             const QChar &fontChar, QEXTNavListWidgetItem *parent)
    : QObject(), d_ptr(new QEXTNavListWidgetItemPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_fontIcon = fontChar;
    this->setParentItem(parent);
}

QEXTNavListWidgetItem::QEXTNavListWidgetItem(const QString &text, const QString &tip,
                                             const QChar &fontChar, bool expand, QEXTNavListWidgetItem *parent)
    : QObject(), d_ptr(new QEXTNavListWidgetItemPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_fontIcon = fontChar;
    d->m_expand = expand;
    this->setParentItem(parent);
}

QEXTNavListWidgetItem::~QEXTNavListWidgetItem()
{
    this->setChecked(false);
    emit this->itemAboutToDestroyed(this);
}

QPixmap QEXTNavListWidgetItem::normalIcon() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_normalIcon;
}

QPixmap QEXTNavListWidgetItem::hoverIcon() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_hoverIcon;
}

QPixmap QEXTNavListWidgetItem::checkedIcon() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_checkedIcon;
}

QPixmap QEXTNavListWidgetItem::selectedIcon() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_selectedIcon;
}

void QEXTNavListWidgetItem::setIcon(const QPixmap &icon)
{
    this->setNormalIcon(icon);
    this->setHoverIcon(icon);
    this->setCheckedIcon(icon);
    this->setSelectedIcon(icon);
}

void QEXTNavListWidgetItem::setNormalIcon(const QPixmap &icon)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_normalIcon = icon;
    emit this->iconChanged(this);
}

void QEXTNavListWidgetItem::setHoverIcon(const QPixmap &icon)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_hoverIcon = icon;
    emit this->iconChanged(this);
}

void QEXTNavListWidgetItem::setCheckedIcon(const QPixmap &icon)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_checkedIcon = icon;
    emit this->iconChanged(this);
}

void QEXTNavListWidgetItem::setSelectedIcon(const QPixmap &icon)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    d->m_selectedIcon = icon;
    emit this->iconChanged(this);
}

QChar QEXTNavListWidgetItem::fontIcon() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_fontIcon;
}

void QEXTNavListWidgetItem::setFontIcon(const QChar &ch)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    if (ch != d->m_fontIcon)
    {
        d->m_fontIcon = ch;
        emit this->fontIconChanged(this);
    }
}

QString QEXTNavListWidgetItem::text() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_text;
}

void QEXTNavListWidgetItem::setText(const QString &text)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    if (text != d->m_text)
    {
        d->m_text = text;
        emit this->textChanged(this);
    }
}

QString QEXTNavListWidgetItem::tip() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_tip;
}

void QEXTNavListWidgetItem::setTip(const QString &tip)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    if (tip != d->m_tip)
    {
        d->m_tip = tip;
        emit this->tipChanged(this);
    }
}

bool QEXTNavListWidgetItem::isExpand() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_expand;
}

void QEXTNavListWidgetItem::setExpand(const bool &expand)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    if (expand != d->m_expand)
    {
        d->m_expand = expand;
        emit this->expandChanged(this);
    }
}

bool QEXTNavListWidgetItem::isVisiable() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_visiable;
}

void QEXTNavListWidgetItem::setVisiable(const bool &visiable)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    if (visiable != d->m_visiable)
    {
        if (!visiable)
        {
            QList<QEXTNavListWidgetItem *>::const_iterator iter;
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

bool QEXTNavListWidgetItem::isEnabled() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_enable;
}

void QEXTNavListWidgetItem::setEnable(const bool &enable)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    if (enable != d->m_enable)
    {
        d->m_enable = enable;
        emit this->enableChanged(this);
    }
}

Qt::CheckState QEXTNavListWidgetItem::checkState() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    if (this->isParentItem())
    {
        QList<QEXTNavListWidgetItem *>::const_iterator iter;
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

bool QEXTNavListWidgetItem::isChecked() const
{
    return Qt::Checked == this->checkState();
}

bool QEXTNavListWidgetItem::setChecked(bool check)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    if (!this->isVisiable() && check)
    {
        qWarning() << "QEXTNavListWidgetItem::setChecked(): item not visiable, can not set check";
        return false;
    }
    if (!this->isEnabled() && check)
    {
        qWarning() << "QEXTNavListWidgetItem::setChecked(): item not enabled, can not set check";
        return false;
    }
    if (this->isParentItem())
    {
        qWarning() << "QEXTNavListWidgetItem::setChecked(): item is parent, can not set check";
        return false;
    }
    if (check != d->m_checkd)
    {
        d->m_checkd = check;
        emit this->checkChanged(this);
    }
    return true;
}

bool QEXTNavListWidgetItem::isLastVisiableItem() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    if (!d->m_parent.isNull() && d->m_visiable)
    {
        return this == d->m_parent->visiableChildItems().last();
    }
    return false;
}

bool QEXTNavListWidgetItem::isChildItem() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return !d->m_parent.isNull();
}

bool QEXTNavListWidgetItem::isParentItem() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_parent.isNull();
}

QEXTNavListWidgetItem *QEXTNavListWidgetItem::parentItem() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_parent.data();
}

bool QEXTNavListWidgetItem::setParentItem(QEXTNavListWidgetItem *parent)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    if (this == parent)
    {
        qWarning() << "QEXTNavListWidgetItem::setParentItem(): parent can not equal to item self";
        return false;
    }
    if (!d->m_childItems.isEmpty())
    {
        qWarning() << "QEXTNavListWidgetItem::setParentItem(): current item is parent item, can not set parent";
        return false;
    }
    if (d->m_parent.data() != parent)
    {
        QEXTNavListWidgetItem *oldParent = d->m_parent.data();
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
            connect(this, SIGNAL(itemAboutToDestroyed(QEXTNavListWidgetItem*)),
                    parent, SLOT(onChildItemAboutToBeDestroyed(QEXTNavListWidgetItem*)));
            emit parent->childItemInserted(this, parent);
        }

        return true;
    }
    return false;
}

int QEXTNavListWidgetItem::childItemsCount() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_childItems.count();
}

int QEXTNavListWidgetItem::visiableChildItemsCount() const
{
    return this->visiableChildItems().count();
}

QList<QEXTNavListWidgetItem *> QEXTNavListWidgetItem::childItems() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    return d->m_childItems;
}

QList<QEXTNavListWidgetItem *> QEXTNavListWidgetItem::visiableChildItems() const
{
    QEXT_DECL_DC(QEXTNavListWidgetItem);
    QList<QEXTNavListWidgetItem *> result;
    QList<QEXTNavListWidgetItem *>::const_iterator iter;
    for (iter = d->m_childItems.begin(); iter != d->m_childItems.end(); ++iter)
    {
        if ((*iter)->isVisiable())
        {
            result.append(*iter);
        }
    }
    return result;
}

void QEXTNavListWidgetItem::onChildItemAboutToBeDestroyed(QEXTNavListWidgetItem *item)
{
    QEXT_DECL_D(QEXTNavListWidgetItem);
    if (item && d->m_childItems.contains(item))
    {
        emit this->childItemAboutToBeRemoved(item, this);
        d->m_childItems.removeOne(item);
        emit this->childItemRemoved(item, this);
    }
}



QEXTNavListDelegate::QEXTNavListDelegate(QEXTNavListWidgetPrivate *navData)
    : QStyledItemDelegate()
{
    m_navData = navData;

    //判断图形字体是否存在,不存在则加入
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
    QEXTNavListWidgetItem *item = (QEXTNavListWidgetItem *)index.data(Qt::UserRole).toLongLong();

    //设置最小的宽高
    QSize size(50, item->isParentItem() ? m_navData->m_parentHeight : m_navData->m_childHeight);
    return size;
}

void QEXTNavListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    QEXTNavListWidgetItem *item = (QEXTNavListWidgetItem *)index.data(Qt::UserRole).toLongLong();

    //定义变量存储区域
    QRect optionRect = option.rect;
    int x = optionRect.x();
    int y = optionRect.y();
    int width = optionRect.width();
    int height = optionRect.height();


    //父节点和子节点颜色分开设置
    bool parent = item->isParentItem();
    bool hasChildItems = (0 != item->visiableChildItemsCount());
    bool checked = item->isChecked();
    bool enabled = item->isEnabled();
    bool parentEnabled = item->parentItem() ? item->parentItem()->isEnabled() : enabled;

    int fontSize = parent ? m_navData->m_parentFontSize : m_navData->m_childFontSize;
    QPixmap icon;
    //根据不同的状态设置不同的颜色 bgColor-主背景色 textColor-主文字颜色 tipBgColor-提示信息背景颜色 tipTextColor-提示信息文字颜色
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

    //绘制背景
    painter->fillRect(optionRect, bgColor);

    //绘制线条,目前限定子节点绘制,如果需要父节点也绘制则取消parent判断即可
    int lineWidth = m_navData->m_lineWidth;
    if (!parent && m_navData->m_lineVisible && lineWidth > 0)
    {
        if (checked)
        {
            //设置偏移量,不然上下部分会有点偏移
            float offset = (float)lineWidth / 2;

            //计算上下两个坐标点
            QPointF pointTop(x, y + offset);
            QPointF pointBottom(x, height + y - offset);
            if (!m_navData->m_lineLeft)
            {
                pointTop.setX(width);
                pointBottom.setX(width);
            }

            //设置线条颜色和宽度
            painter->setPen(QPen(m_navData->m_lineColor, lineWidth));
            painter->drawLine(pointTop, pointBottom);
        }
    }

    //绘制三角形,目前限定子节点绘制,如果需要父节点也绘制则取消parent判断即可
    int triangleWidth = m_navData->m_triangleWidth;
    if (!parent && m_navData->m_triangleVisible && triangleWidth > 0)
    {
        if (checked)
        {
            QFont font = m_iconFont;
            font.setPixelSize(fontSize + triangleWidth);
            painter->setFont(font);
            painter->setPen(m_navData->m_triangleColor);

            //采用图形字体中的三角形绘制
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

    //绘制行分隔符
    if (m_navData->m_separateVisible)
    {
        if (item->isParentItem() || (item->isChildItem() && item->isLastVisiableItem()))
        {
            painter->setPen(QPen(m_navData->m_separateColor, m_navData->m_separateHeight));
            painter->drawLine(QPointF(x, y + height), QPointF(x + width, y + height));
        }
    }

    //绘制文字,如果文字为空则不绘制
    QString text = item->text();
    if (!text.isEmpty())
    {
        //文字离左边的距离+字体大小
        int margin = m_navData->m_parentMargin;
        if (item->isChildItem())
        {
            margin = m_navData->m_childMargin;
            fontSize = m_navData->m_childFontSize;
        }

        //计算文字区域
        QRect textRect = optionRect;
        textRect.setWidth(width - margin);
        textRect.setX(x + margin);

        QFont font = m_navData->itemFont();
        font.setPixelSize(fontSize);
        painter->setFont(font);
        painter->setPen(textColor);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }

    //绘制提示信息,如果不需要显示提示信息或者提示信息为空则不绘制
    QString tip = item->tip();
    if (m_navData->m_tipVisible && !tip.isEmpty())
    {
        //如果是数字则将超过999的数字显示成 999+
        //如果显示的提示信息长度过长则将多余显示成省略号 .
        if (tip.toInt() > 0)
        {
            tip = tip.toInt() > 999 ? "999+" : tip;
        }
        else if (tip.length() > 2)
        {
            tip = tip.left(2) + " .";
        }

        //计算绘制区域,半径取高度的四分之一
        int radius = height / 4;
        QRect tipRect = optionRect;
        tipRect.setHeight(radius * 2);
        tipRect.moveCenter(optionRect.center());
        tipRect.setLeft(optionRect.right() - m_navData->m_tipWidth - 5);
        tipRect.setRight(optionRect.right() - 5);

        //设置字体大小
        QFont font = m_navData->itemFont();
        font.setPixelSize(fontSize - 2);
        painter->setFont(font);

        //绘制提示文字的背景
        painter->setPen(Qt::NoPen);
        painter->setBrush(tipBgColor);
        painter->drawRoundedRect(tipRect, radius, radius);

        //绘制提示文字
        painter->setPen(tipTextColor);
        painter->setBrush(Qt::NoBrush);
        painter->drawText(tipRect, Qt::AlignCenter, tip);
    }

    //计算绘制图标区域
    QRect iconRect = optionRect;
    iconRect.setLeft(parent ? m_navData->m_parentIconMargin : m_navData->m_childIconMargin);

    //设置图形字体和画笔颜色
    QFont font = m_iconFont;
    font.setPixelSize(fontSize);
    painter->setFont(font);
    painter->setPen(textColor);

    //绘制左侧图标,有图标则绘制图标,没有的话父窗体取 + -
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

    //绘制父节点右侧图标
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



QEXTNavListModelPrivate::QEXTNavListModelPrivate(QEXTNavListModel *q)
    : q_ptr(q)
{

}

QEXTNavListModelPrivate::~QEXTNavListModelPrivate()
{
    this->deleteAllItems();
    m_parentItemList.clear();
    m_visiableItemList.clear();
}

void QEXTNavListModelPrivate::deleteAllItems()
{
    QSet<QEXTNavListWidgetItem *>::iterator iter;
    for (iter = m_allItemSet.begin(); iter != m_allItemSet.end(); ++iter)
    {
        (*iter)->disconnect();
        (*iter)->deleteLater();
    }
    m_allItemSet.clear();
}

void QEXTNavListModelPrivate::refreshVisiableList()
{
    m_visiableItemList.clear();
    QList<QEXTNavListWidgetItem *>::iterator iter;
    for (iter = m_parentItemList.begin(); iter != m_parentItemList.end(); ++iter)
    {
        if ((*iter)->isVisiable())
        {
            m_visiableItemList.append(*iter);
            if ((*iter)->isExpand())
            {
                QList<QEXTNavListWidgetItem *> childItems = (*iter)->visiableChildItems();
                if (!childItems.isEmpty())
                {
                    m_visiableItemList.append(childItems);
                }
            }
        }
    }
}

void QEXTNavListModelPrivate::initAllItemsConnection()
{
    QSet<QEXTNavListWidgetItem *>::iterator iter;
    for (iter = m_allItemSet.begin(); iter != m_allItemSet.end(); ++iter)
    {
        QEXTNavListWidgetItem *item = *iter;
        this->initItemConnection(item);
    }
}

void QEXTNavListModelPrivate::initItemConnection(QEXTNavListWidgetItem *item)
{
    QEXT_DECL_Q(QEXTNavListModel);
    item->disconnect(q);
    QObject::connect(item, SIGNAL(itemAboutToDestroyed(QEXTNavListWidgetItem*)), q, SLOT(onItemAboutToDestroyed(QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(iconChanged(QEXTNavListWidgetItem*)), q, SLOT(onItemChanged(QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(fontIconChanged(QEXTNavListWidgetItem*)), q, SLOT(onItemChanged(QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(textChanged(QEXTNavListWidgetItem*)), q, SLOT(onItemChanged(QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(tipChanged(QEXTNavListWidgetItem*)), q, SLOT(onItemChanged(QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(enableChanged(QEXTNavListWidgetItem*)), q, SLOT(onItemChanged(QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(expandChanged(QEXTNavListWidgetItem*)), q, SLOT(onItemExpandChanged(QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(checkChanged(QEXTNavListWidgetItem*)), q, SLOT(onItemCheckChanged(QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(visiableAboutToBeChanged(QEXTNavListWidgetItem*)),
                     q, SLOT(onItemVisiableAboutToBeChanged(QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(visiableChanged(QEXTNavListWidgetItem*)),
                     q, SLOT(onItemVisiableChanged(QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(childItemAboutToBeInserted(QEXTNavListWidgetItem*,QEXTNavListWidgetItem*)),
                     q, SLOT(onChildItemAboutToBeInserted(QEXTNavListWidgetItem*,QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(childItemInserted(QEXTNavListWidgetItem*,QEXTNavListWidgetItem*)),
                     q, SLOT(onChildItemInserted(QEXTNavListWidgetItem*,QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(childItemAboutToBeRemoved(QEXTNavListWidgetItem*,QEXTNavListWidgetItem*)),
                     q, SLOT(onChildItemAboutToBeRemoved(QEXTNavListWidgetItem*,QEXTNavListWidgetItem*)));
    QObject::connect(item, SIGNAL(childItemRemoved(QEXTNavListWidgetItem*,QEXTNavListWidgetItem*)),
                     q, SLOT(onChildItemRemoved(QEXTNavListWidgetItem*,QEXTNavListWidgetItem*)));
}


QEXTNavListModel::QEXTNavListModel(QObject *parent)
    : QAbstractListModel(parent), d_ptr(new QEXTNavListModelPrivate(this))
{

}

QEXTNavListModel::~QEXTNavListModel()
{

}

QEXTNavListWidgetItem *QEXTNavListModel::checkedItem() const
{
    QEXT_DECL_DC(QEXTNavListModel);
    return d->m_checkedItem.data();
}

QList<QEXTNavListWidgetItem *> QEXTNavListModel::allItems() const
{
    QEXT_DECL_DC(QEXTNavListModel);
    return d->m_allItemSet.toList();
}

QList<QEXTNavListWidgetItem *> QEXTNavListModel::parentItems() const
{
    QEXT_DECL_DC(QEXTNavListModel);
    return d->m_parentItemList;
}

QList<QEXTNavListWidgetItem *> QEXTNavListModel::visiableItems() const
{
    QEXT_DECL_DC(QEXTNavListModel);
    return d->m_visiableItemList;
}

int QEXTNavListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    QEXT_DECL_DC(QEXTNavListModel);
    return d->m_visiableItemList.size();
}

QVariant QEXTNavListModel::data(const QModelIndex &index, int role) const
{
    QEXT_DECL_DC(QEXTNavListModel);
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

Qt::ItemFlags QEXTNavListModel::flags(const QModelIndex &index) const
{
    QEXT_DECL_DC(QEXTNavListModel);
    if (index.isValid())
    {
        int row = index.row();
        if (row >= 0 && row < d->m_visiableItemList.size())
        {
            QEXTNavListWidgetItem *item = d->m_visiableItemList.at(row);
            QEXTNavListWidgetItem *parentItem = item->parentItem();
            if (!item->isEnabled() || (parentItem && !parentItem->isEnabled()))
            {
                return item->isParentItem() ? Qt::ItemIsEnabled : Qt::NoItemFlags;
            }
        }
    }
    return QAbstractListModel::flags(index);
}

void QEXTNavListModel::setItems(const QStringList &items)
{
    if (!items.isEmpty())
    {
        this->beginResetModel();

        bool ok;
        QStringList itemStringList = items;
        QList<QEXTNavListWidgetItem *> parentItemList;
        QMutableStringListIterator iter(itemStringList);
        while (iter.hasNext())
        {
            QString item = iter.next();
            QStringList list = item.split("|");
            if (list.count() < 5)
            {
                qWarning() << QString("QEXTNavListModel::setItems(): item string %1 invalid").arg(item);
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
                QEXTNavListWidgetItem *parentItem = new QEXTNavListWidgetItem;
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
                        qWarning() << QString("QEXTNavListModel::setItems(): item string %1 invalid").arg(item);
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
                        QEXTNavListWidgetItem *childItem = new QEXTNavListWidgetItem;
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
                qWarning() << QString("QEXTNavListModel::setItems(): item string %1 invalid").arg(item);
                checkIter.remove();
                continue;
            }
            QString text = list.at(0);
            QString parentText = list.at(1);
            QString expand = list.at(2);
            QString tip = list.at(3);
            QString icon = list.at(4);
            icon = icon.replace("0x", "");
            QEXTNavListWidgetItem *parentItem = new QEXTNavListWidgetItem;
            parentItemList.append(parentItem);
            parentItem->setExpand(expand.toInt());
            parentItem->setText(text);
            parentItem->setTip(tip);
            if (!icon.isEmpty())
            {
                parentItem->setFontIcon(QChar(icon.toInt(&ok, 16)));
            }
            checkIter.remove();
            qWarning() << QString("QEXTNavListModel::setItems(): item string %1 parent %2 not exist").arg(item).arg(parentText);
        }
        this->setItems(parentItemList);

        this->endResetModel();
    }
}

//TODO
void QEXTNavListModel::setItems(const QList<QEXTNavListWidgetItem *> &items)
{
    QEXT_DECL_D(QEXTNavListModel);
    if (!items.isEmpty())
    {
        this->beginResetModel();

        QSet<QEXTNavListWidgetItem *> cacheItemSet;
        d->m_visiableItemList.clear();
        d->m_parentItemList.clear();

        QList<QEXTNavListWidgetItem *>::const_iterator iter;
        for (iter = items.begin(); iter != items.end(); ++iter)
        {
            QEXTNavListWidgetItem *item = *iter;
            if (item->isParentItem())
            {
                cacheItemSet.insert(item);
                d->m_parentItemList.append(item);
                if (d->m_allItemSet.contains(item))
                {
                    d->m_allItemSet.remove(item);
                }

                QList<QEXTNavListWidgetItem *> childItems = item->childItems();
                QList<QEXTNavListWidgetItem *>::iterator childIter;
                for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                {
                    QEXTNavListWidgetItem *childItem = *childIter;
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
        d->refreshVisiableList();
        d->initAllItemsConnection();

        this->endResetModel();
    }
}

void QEXTNavListModel::expandCollapseItem(const QModelIndex &index)
{
    QEXT_DECL_D(QEXTNavListModel);
    QEXTNavListWidgetItem *item = d->m_visiableItemList.at(index.row());
    if (0 != item->visiableChildItemsCount())
    {
        item->setExpand(!item->isExpand());
    }
}

void QEXTNavListModel::onItemAboutToDestroyed(QEXTNavListWidgetItem *item)
{
    QEXT_DECL_D(QEXTNavListModel);
    if (item->isParentItem())
    {
        d->m_allItemSet.remove(item);
        d->m_parentItemList.removeOne(item);
        if (item->isVisiable())
        {
            int row = d->m_visiableItemList.indexOf(item);
            int count = item->visiableChildItemsCount();
            this->beginRemoveRows(QModelIndex(), row, row + count);
            d->m_visiableItemList.removeOne(item);

            QList<QEXTNavListWidgetItem *>::iterator iter;
            QList<QEXTNavListWidgetItem *> childItems = item->childItems();
            for (iter = childItems.begin(); iter != childItems.end(); ++iter)
            {
                QEXTNavListWidgetItem *childItem = *iter;
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

void QEXTNavListModel::onItemChanged(QEXTNavListWidgetItem *item)
{
    QEXT_DECL_D(QEXTNavListModel);
    int row = d->m_visiableItemList.indexOf(item);
    QModelIndex index = this->index(row, 0);
    emit this->dataChanged(index, index);
}

void QEXTNavListModel::onItemEnableChanged(QEXTNavListWidgetItem *item)
{
    QEXT_DECL_D(QEXTNavListModel);
    if (item->isVisiable())
    {
        int row = d->m_visiableItemList.indexOf(item);
        int count = item->isParentItem() ? item->visiableChildItemsCount() : 0;
        QModelIndex index1 = this->index(row, 0);
        QModelIndex index2 = this->index(row + count, 0);
        emit this->dataChanged(index1, index2);
    }
}

void QEXTNavListModel::onItemExpandChanged(QEXTNavListWidgetItem *item)
{
    QEXT_DECL_D(QEXTNavListModel);
    QList<QEXTNavListWidgetItem *> visiableItems = item->visiableChildItems();
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

void QEXTNavListModel::onItemCheckChanged(QEXTNavListWidgetItem *item)
{
    QEXT_DECL_D(QEXTNavListModel);
    int row = d->m_visiableItemList.indexOf(item);
    QModelIndex index = this->index(row, 0);
    emit this->dataChanged(index, index);

    if (item->isChecked())
    {
        if (item != d->m_checkedItem.data())
        {
            QEXTNavListWidgetItem *oldCheckedItem = d->m_checkedItem.data();
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
            emit this->checkedItemChanged((QEXTNavListWidgetItem *)QEXT_DECL_NULLPTR);
        }
    }
}

void QEXTNavListModel::onItemVisiableAboutToBeChanged(QEXTNavListWidgetItem *item)
{
    QEXT_DECL_D(QEXTNavListModel);
    if (item->isVisiable())
    {
        int row = d->m_visiableItemList.indexOf(item);
        int count = item->isExpand() ? item->visiableChildItemsCount() : 0;
        this->beginRemoveRows(QModelIndex(), row, row + count);
    }
    else
    {
        QList<QEXTNavListWidgetItem *> visiableChildItems = item->visiableChildItems();
        int visiableChildcount = (item->isExpand() && item->isParentItem() && item->isVisiable()) ? visiableChildItems.size() : 0;
        int row = 0;
        bool located = false;
        QList<QEXTNavListWidgetItem *>::iterator iter;
        for (iter = d->m_parentItemList.begin(); iter != d->m_parentItemList.end(); ++iter)
        {
            if (located)
            {
                break;
            }
            if ((*iter)->isVisiable())
            {
                if (item == *iter)
                {
                    break;
                }
                row++;
                if ((*iter)->isExpand())
                {
                    QList<QEXTNavListWidgetItem *>::iterator childIter;
                    QList<QEXTNavListWidgetItem *> childItems = (*iter)->childItems();
                    for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                    {
                        if (item == *childIter && (*iter)->isVisiable())
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

void QEXTNavListModel::onItemVisiableChanged(QEXTNavListWidgetItem *item)
{
    QEXT_DECL_D(QEXTNavListModel);
    if (item->isVisiable())
    {
        int row = 0;
        bool located = false;
        QList<QEXTNavListWidgetItem *>::iterator iter;
        for (iter = d->m_parentItemList.begin(); iter != d->m_parentItemList.end(); ++iter)
        {
            if (located)
            {
                break;
            }
            if ((*iter)->isVisiable())
            {
                QList<QEXTNavListWidgetItem *> childItems = (*iter)->childItems();
                if (item == *iter)
                {
                    d->m_visiableItemList.insert(row++, *iter);
                    if ((*iter)->isExpand())
                    {
                        QList<QEXTNavListWidgetItem *>::iterator childIter;
                        for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                        {
                            if ((*childIter)->isVisiable())
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
                    QList<QEXTNavListWidgetItem *>::iterator childIter;
                    for (childIter = childItems.begin(); childIter != childItems.end(); ++childIter)
                    {
                        if (item == *childIter && (*childIter)->isVisiable())
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

void QEXTNavListModel::onChildItemAboutToBeInserted(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent)
{
    QEXT_DECL_D(QEXTNavListModel);
    if (item->isVisiable() && parent->isVisiable())
    {
        int index = d->m_visiableItemList.indexOf(parent);
        int row = parent->visiableChildItemsCount() + 1;
        this->beginInsertRows(QModelIndex(), index + row + 1, index + row + 1);
    }
}

void QEXTNavListModel::onChildItemInserted(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent)
{
    QEXT_DECL_D(QEXTNavListModel);
    if (item->isVisiable() && parent->isVisiable())
    {
        int index = d->m_visiableItemList.indexOf(parent);
        int row = parent->visiableChildItemsCount();
        d->m_visiableItemList.insert(index + row + 1, item);
        this->endInsertRows();
    }
}

void QEXTNavListModel::onChildItemAboutToBeRemoved(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent)
{
    QEXT_DECL_D(QEXTNavListModel);
    if (d->m_visiableItemList.contains(item))
    {
        int row = d->m_visiableItemList.indexOf(parent);
        this->beginRemoveRows(QModelIndex(), row, row);
    }
}

void QEXTNavListModel::onChildItemRemoved(QEXTNavListWidgetItem *item, QEXTNavListWidgetItem *parent)
{
    QEXT_DECL_D(QEXTNavListModel);
    d->m_allItemSet.remove(item);
    if (d->m_visiableItemList.contains(item))
    {
        d->m_visiableItemList.removeOne(item);
        this->endRemoveRows();
    }
}



QEXTNavListWidgetPrivate::QEXTNavListWidgetPrivate(QEXTNavListWidget *q)
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

    m_expendMode = QEXTNavListWidget::ExpendMode_SingleClick;
    m_delegate.reset(new QEXTNavListDelegate(this));
    m_listView.reset(new QEXTNavListView);
    m_listView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_listView->setMouseTracking(true);
    m_listView->setAutoFillBackground(true);
    m_listView->setItemDelegate(m_delegate.data());
}

QEXTNavListWidgetPrivate::~QEXTNavListWidgetPrivate()
{
    if (!m_model.isNull())
    {
        m_model->deleteLater();
    }
}

QFont QEXTNavListWidgetPrivate::itemFont() const
{
    QEXT_DECL_QC(QEXTNavListWidget);
    return q->font();
}


QEXTNavListWidget::QEXTNavListWidget(QWidget *parent)
    : QWidget(parent), d_ptr(new QEXTNavListWidgetPrivate(this))
{
    QEXT_DECL_D(QEXTNavListWidget);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(d->m_listView.data());
    this->setLayout(layout);
    this->setBackgroundColor(d->m_parentBackgroundNormalColor);
    this->setModel(new QEXTNavListModel);
    connect(d->m_listView.data(), SIGNAL(pressed(QModelIndex)), this, SLOT(onItemPressed(QModelIndex)));
}

QEXTNavListWidget::~QEXTNavListWidget()
{

}

QListView *QEXTNavListWidget::view() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_listView.data();
}

QEXTNavListModel *QEXTNavListWidget::model() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_model.data();
}

QEXTNavListWidgetItem *QEXTNavListWidget::selectedItem() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_selectedItem.data();
}

QEXTNavListWidgetItem *QEXTNavListWidget::checkedItem() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_model->checkedItem();
}

QList<QEXTNavListWidgetItem *> QEXTNavListWidget::allItems() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_model->allItems();
}

QList<QEXTNavListWidgetItem *> QEXTNavListWidget::parentItems() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_model->parentItems();
}

QList<QEXTNavListWidgetItem *> QEXTNavListWidget::visiableItems() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_model->visiableItems();
}

void QEXTNavListWidget::paintEvent(QPaintEvent *event)
{
    QEXT_DECL_D(QEXTNavListWidget);
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(d->m_parentBackgroundNormalColor);
    painter.drawRect(this->rect());
    QStyleOption opt;
    opt.init(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void QEXTNavListWidget::onItemPressed(const QModelIndex &index)
{
    QEXT_DECL_D(QEXTNavListWidget);
    QEXTNavListWidgetItem *item = (QEXTNavListWidgetItem *)index.data(Qt::UserRole).toLongLong();
    if (item)
    {
        if (item->isChildItem())
        {
            this->setSelectedItem(item);
        }
        emit this->itemPressed(item);
    }
}

bool QEXTNavListWidget::itemRightIconVisible() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_rightIconVisible;
}

bool QEXTNavListWidget::itemTipVisible() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_tipVisible;
}

int QEXTNavListWidget::itemTipWidth() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_tipWidth;
}

bool QEXTNavListWidget::itemSeparateVisible() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_separateVisible;
}

int QEXTNavListWidget::itemSeparateHeight() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_separateHeight;
}

QColor QEXTNavListWidget::itemSeparateColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_separateColor;
}

bool QEXTNavListWidget::itemLineLeft() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_lineLeft;
}

bool QEXTNavListWidget::itemLineVisible() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_lineVisible;
}

int QEXTNavListWidget::itemLineWidth() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_lineWidth;
}

QColor QEXTNavListWidget::itemLineColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_lineColor;
}

bool QEXTNavListWidget::itemTriangleLeft() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_triangleLeft;
}

bool QEXTNavListWidget::itemTriangleVisible() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_triangleVisible;
}

int QEXTNavListWidget::itemTriangleWidth() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_triangleWidth;
}

QColor QEXTNavListWidget::itemTriangleColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_triangleColor;
}

QColor QEXTNavListWidget::backgroundColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_backgroundColor;
}

int QEXTNavListWidget::parentItemIconMargin() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentIconMargin;
}

int QEXTNavListWidget::parentItemMargin() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentMargin;
}

int QEXTNavListWidget::parentItemFontSize() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentFontSize;
}

int QEXTNavListWidget::parentItemHeight() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentHeight;
}

QColor QEXTNavListWidget::parentItemNormalBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentBackgroundNormalColor;
}

QColor QEXTNavListWidget::parentItemCheckedBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentBackgroundCheckedColor;
}

QColor QEXTNavListWidget::parentItemSelectedBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentBackgroundSelectedColor;
}

QColor QEXTNavListWidget::parentItemHoverBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentBackgroundHoverColor;
}

QColor QEXTNavListWidget::parentItemNormalTextColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentTextNormalColor;
}

QColor QEXTNavListWidget::parentItemCheckedTextColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentTextCheckedColor;
}

QColor QEXTNavListWidget::parentItemSelectedTextColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentTextSelectedColor;
}

QColor QEXTNavListWidget::parentItemHoverTextColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_parentTextHoverColor;
}

int QEXTNavListWidget::childItemIconMargin() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childIconMargin;
}

int QEXTNavListWidget::childItemMargin() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childMargin;
}

int QEXTNavListWidget::childItemFontSize() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childFontSize;
}

int QEXTNavListWidget::childItemHeight() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childHeight;
}

QColor QEXTNavListWidget::childItemNormalBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childBackgroundNormalColor;
}

QColor QEXTNavListWidget::childItemCheckedBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childBackgroundCheckedColor;
}

QColor QEXTNavListWidget::childItemSelectedBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childBackgroundSelectedColor;
}

QColor QEXTNavListWidget::childItemHoverBackgroundColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childBackgroundHoverColor;
}

QColor QEXTNavListWidget::childItemNormalTextColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childTextNormalColor;
}

QColor QEXTNavListWidget::childItemCheckedTextColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childTextCheckedColor;
}

QColor QEXTNavListWidget::childItemSelectedTextColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childTextSelectedColor;
}

QColor QEXTNavListWidget::childItemHoverTextColor() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_childTextHoverColor;
}

QEXTNavListWidget::ExpendMode QEXTNavListWidget::expendMode() const
{
    QEXT_DECL_DC(QEXTNavListWidget);
    return d->m_expendMode;
}

QSize QEXTNavListWidget::sizeHint() const
{
    return QSize(200, 300);
}

QSize QEXTNavListWidget::minimumSizeHint() const
{
    return QSize(20, 20);
}

void QEXTNavListWidget::setModel(QEXTNavListModel *model)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (d->m_model.data() != model)
    {
        if (!d->m_model.isNull())
        {
            disconnect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)), model, SLOT(expandCollapseItem(QModelIndex)));
            disconnect(d->m_model.data(), SIGNAL(checkedItemChanged(QEXTNavListWidgetItem*)), this, SIGNAL(checkedItemChanged(QEXTNavListWidgetItem*)));
            d->m_model->deleteLater();
            d->m_model = QEXT_DECL_NULLPTR;
            d->m_listView->setModel(d->m_model.data());
        }
        if (model)
        {
            d->m_model = model;
            d->m_listView->setModel(d->m_model.data());
            connect(d->m_listView.data(), SIGNAL(clicked(QModelIndex)), model, SLOT(expandCollapseItem(QModelIndex)));
            connect(d->m_model.data(), SIGNAL(checkedItemChanged(QEXTNavListWidgetItem*)), this, SIGNAL(checkedItemChanged(QEXTNavListWidgetItem*)));
        }
    }
}

QList<QEXTNavListWidgetItem *> QEXTNavListWidget::setItems(const QString &items)
{
    QEXT_DECL_D(QEXTNavListWidget);
    QStringList item = items.split(",");
    if (d->m_stringItems != item)
    {
        d->m_stringItems = item;
        d->m_model->setItems(item);
    }
    return d->m_model->parentItems();
}

QList<QEXTNavListWidgetItem *> QEXTNavListWidget::setItems(const QStringList &items)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (d->m_stringItems != items)
    {
        d->m_stringItems = items;
        d->m_model->setItems(items);
    }
    return d->m_model->parentItems();
}

void QEXTNavListWidget::setItems(const QList<QEXTNavListWidgetItem *> &items)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (d->m_items != items)
    {
        d->m_items = items;
        d->m_model->setItems(items);
    }
}

bool QEXTNavListWidget::setCurrentRow(int row)
{
    QEXT_DECL_D(QEXTNavListWidget);
    QList<QEXTNavListWidgetItem *> visiableItems = d->m_model->visiableItems();
    if (row >= 0 && row < visiableItems.size())
    {
        QEXTNavListWidgetItem *item = visiableItems.at(row);
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
        qWarning() << "QEXTNavListWidget::setCurrentRow(): row out of range in visiableItems";
        return false;
    }
}

bool QEXTNavListWidget::setSelectedItem(QEXTNavListWidgetItem *item)
{
    QEXT_DECL_D(QEXTNavListWidget);
    QList<QEXTNavListWidgetItem *> visiableItems = d->m_model->visiableItems();
    if (visiableItems.contains(item))
    {
        QList<QEXTNavListWidgetItem *>::iterator iter;
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
        qWarning() << "QEXTNavListWidget::setSelectedItem(): item not visiable, can not set selected";
        return false;
    }
}

void QEXTNavListWidget::setItemRightIconVisible(bool visible)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (visible != d->m_rightIconVisible)
    {
        d->m_rightIconVisible = visible;
        this->update();
    }
}

void QEXTNavListWidget::setItemTipVisible(bool visible)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (visible != d->m_tipVisible)
    {
        d->m_tipVisible = visible;
        this->update();
    }
}

void QEXTNavListWidget::setItemTipWidth(int width)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (width != d->m_tipWidth)
    {
        d->m_tipWidth = width;
        this->update();
    }
}

void QEXTNavListWidget::setItemSeparateVisible(bool visible)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (visible != d->m_separateVisible)
    {
        d->m_separateVisible = visible;
        this->update();
    }
}

void QEXTNavListWidget::setItemSeparateHeight(int height)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (height != d->m_separateHeight)
    {
        d->m_separateHeight = height;
        this->update();
    }
}

void QEXTNavListWidget::setItemSeparateColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_separateColor)
    {
        d->m_separateColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setItemLineLeft(bool inLeft)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (inLeft != d->m_lineLeft)
    {
        d->m_lineLeft = inLeft;
        this->update();
    }
}

void QEXTNavListWidget::setItemLineVisible(bool visible)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (visible != d->m_lineVisible)
    {
        d->m_lineVisible = visible;
        this->update();
    }
}

void QEXTNavListWidget::setItemLineWidth(int width)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (width != d->m_lineWidth)
    {
        d->m_lineWidth = width;
        this->update();
    }
}

void QEXTNavListWidget::setItemLineColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_lineColor)
    {
        d->m_lineColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setItemTriangleLeft(bool inLeft)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (inLeft != d->m_triangleLeft)
    {
        d->m_triangleLeft = inLeft;
        this->update();
    }
}

void QEXTNavListWidget::setItemTriangleVisible(bool visible)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (visible != d->m_triangleVisible)
    {
        d->m_triangleVisible = visible;
        this->update();
    }
}

void QEXTNavListWidget::setItemTriangleWidth(int width)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (width != d->m_triangleWidth)
    {
        d->m_triangleWidth = width;
        this->update();
    }
}

void QEXTNavListWidget::setItemTriangleColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_triangleColor)
    {
        d->m_triangleColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    QString styleSheet = QString("background-color: rgba(%1, %2, %3, %4);")
            .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
    d->m_listView->setStyleSheet(styleSheet);
    if (color != d->m_backgroundColor)
    {
        d->m_backgroundColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemIconMargin(int margin)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (margin != d->m_parentIconMargin)
    {
        d->m_parentIconMargin = margin;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemMargin(int margin)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (margin != d->m_parentMargin)
    {
        d->m_parentMargin = margin;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemFontSize(int size)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (size != d->m_parentFontSize)
    {
        d->m_parentFontSize = size;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemHeight(int height)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (height != d->m_parentHeight)
    {
        d->m_parentHeight = height;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemNormalBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_parentBackgroundNormalColor)
    {
        d->m_parentBackgroundNormalColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemCheckedBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_parentBackgroundCheckedColor)
    {
        d->m_parentBackgroundCheckedColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemSelectedBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_parentBackgroundSelectedColor)
    {
        d->m_parentBackgroundSelectedColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemHoverBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_parentBackgroundHoverColor)
    {
        d->m_parentBackgroundHoverColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemNormalTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_parentTextNormalColor)
    {
        d->m_parentTextNormalColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemCheckedTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_parentTextCheckedColor)
    {
        d->m_parentTextCheckedColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemSelectedTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_parentTextSelectedColor)
    {
        d->m_parentTextSelectedColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setParentItemHoverTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_parentTextHoverColor)
    {
        d->m_parentTextHoverColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemIconMargin(int margin)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (margin != d->m_childIconMargin)
    {
        d->m_childIconMargin = margin;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemMargin(int margin)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (margin != d->m_childMargin)
    {
        d->m_childMargin = margin;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemFontSize(int size)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (size != d->m_childFontSize)
    {
        d->m_childFontSize = size;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemHeight(int height)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (height != d->m_childHeight)
    {
        d->m_childHeight = height;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemNormalBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_childBackgroundNormalColor)
    {
        d->m_childBackgroundNormalColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemBackgroundCheckedColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_childBackgroundCheckedColor)
    {
        d->m_childBackgroundCheckedColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemSelectedBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_childBackgroundSelectedColor)
    {
        d->m_childBackgroundSelectedColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemHoverBackgroundColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_childBackgroundHoverColor)
    {
        d->m_childBackgroundHoverColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemNormalTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_childTextNormalColor)
    {
        d->m_childTextNormalColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemCheckedTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_childTextCheckedColor)
    {
        d->m_childTextCheckedColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemSelectedTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_childTextSelectedColor)
    {
        d->m_childTextSelectedColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setChildItemHoverTextColor(const QColor &color)
{
    QEXT_DECL_D(QEXTNavListWidget);
    if (color != d->m_childTextHoverColor)
    {
        d->m_childTextHoverColor = color;
        this->update();
    }
}

void QEXTNavListWidget::setExpendMode(const QEXTNavListWidget::ExpendMode &mode)
{
    QEXT_DECL_D(QEXTNavListWidget);
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
