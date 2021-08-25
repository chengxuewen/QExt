#pragma execution_character_set("utf-8")

#include <qextNavTreeWidget.h>
#include <qextNavTreeWidget_p.h>

#include <QApplication>
#include <QFontDatabase>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>


QEXTNavTreeItemPrivate::QEXTNavTreeItemPrivate(QEXTNavTreeItem *qq)
    : QEXTObjectPrivate(qq)
{
    m_expand = false;
    m_level = 1;
}

QEXTNavTreeItemPrivate::~QEXTNavTreeItemPrivate()
{
    qDeleteAll(m_childItems);
    m_childItems.clear();
}

void QEXTNavTreeItemPrivate::updateLevel()
{
    int level = 1;
    QSet<QEXTNavTreeItem *> parentSet;
    QEXTNavTreeItem *parentItem = m_parent.data();
    while (parentItem && !parentSet.contains(parentItem))
    {
        level++;
        parentSet.insert(parentItem);
        parentItem = parentItem->parentItem();
    }
    m_level = level;
}


QEXTNavTreeItem::QEXTNavTreeItem(QEXTNavTreeItem *parent)
    : QObject(parent), QEXTObject(*(new QEXTNavTreeItemPrivate(this)))
{
    this->setParentItem(parent);
}

QEXTNavTreeItem::QEXTNavTreeItem(const QString &text, const QIcon &icon, QEXTNavTreeItem *parent)
    : QObject(parent), QEXTObject(*(new QEXTNavTreeItemPrivate(this)))
{
    QEXT_DECL_D(QEXTNavTreeItem);
    d->m_text = text;
    d->m_icon = icon;
    this->setParentItem(parent);
}

QEXTNavTreeItem::QEXTNavTreeItem(const QString &text, const QIcon &icon, bool expand, QEXTNavTreeItem *parent)
    : QObject(parent), QEXTObject(*(new QEXTNavTreeItemPrivate(this)))
{
    QEXT_DECL_D(QEXTNavTreeItem);
    d->m_text = text;
    d->m_icon = icon;
    d->m_expand = expand;
    this->setParentItem(parent);
}

QEXTNavTreeItem::QEXTNavTreeItem(const QString &text, const QString &tip, const QIcon &icon, QEXTNavTreeItem *parent)
    : QObject(parent), QEXTObject(*(new QEXTNavTreeItemPrivate(this)))
{
    QEXT_DECL_D(QEXTNavTreeItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_icon = icon;
    this->setParentItem(parent);
}

QEXTNavTreeItem::QEXTNavTreeItem(const QString &text, const QString &tip, const QIcon &icon, bool expand, QEXTNavTreeItem *parent)
    : QObject(parent), QEXTObject(*(new QEXTNavTreeItemPrivate(this)))
{
    QEXT_DECL_D(QEXTNavTreeItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_icon = icon;
    d->m_expand = expand;
    this->setParentItem(parent);
}

QEXTNavTreeItem::QEXTNavTreeItem(const QString &text, const QChar &fontChar, QEXTNavTreeItem *parent)
    : QObject(parent), QEXTObject(*(new QEXTNavTreeItemPrivate(this)))
{
    QEXT_DECL_D(QEXTNavTreeItem);
    d->m_text = text;
    d->m_fontIcon = fontChar;
    this->setParentItem(parent);
}

QEXTNavTreeItem::QEXTNavTreeItem(const QString &text, const QChar &fontChar, bool expand, QEXTNavTreeItem *parent)
    : QObject(parent), QEXTObject(*(new QEXTNavTreeItemPrivate(this)))
{
    QEXT_DECL_D(QEXTNavTreeItem);
    d->m_text = text;
    d->m_fontIcon = fontChar;
    d->m_expand = expand;
    this->setParentItem(parent);
}

QEXTNavTreeItem::QEXTNavTreeItem(const QString &text, const QString &tip, const QChar &fontChar, QEXTNavTreeItem *parent)
    : QObject(parent), QEXTObject(*(new QEXTNavTreeItemPrivate(this)))
{
    QEXT_DECL_D(QEXTNavTreeItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_fontIcon = fontChar;
    this->setParentItem(parent);
}

QEXTNavTreeItem::QEXTNavTreeItem(const QString &text, const QString &tip, const QChar &fontChar, bool expand, QEXTNavTreeItem *parent)
    : QObject(parent), QEXTObject(*(new QEXTNavTreeItemPrivate(this)))
{
    QEXT_DECL_D(QEXTNavTreeItem);
    d->m_text = text;
    d->m_tip = tip;
    d->m_fontIcon = fontChar;
    d->m_expand = expand;
    this->setParentItem(parent);
}

QEXTNavTreeItem::~QEXTNavTreeItem()
{

}

QIcon QEXTNavTreeItem::icon() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return d->m_icon;
}

void QEXTNavTreeItem::setIcon(const QIcon &icon)
{
    QEXT_DECL_D(QEXTNavTreeItem);
    d->m_icon = icon;
    emit this->iconChanged(this);
}

QChar QEXTNavTreeItem::fontChar() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return d->m_fontIcon;
}

void QEXTNavTreeItem::setFontIcon(const QChar &ch)
{
    QEXT_DECL_D(QEXTNavTreeItem);
    if (d->m_fontIcon != ch)
    {
        d->m_fontIcon = ch;
        emit this->fontIconChanged(this);
    }
}

QString QEXTNavTreeItem::text() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return d->m_text;
}

void QEXTNavTreeItem::setText(const QString &text)
{
    QEXT_DECL_D(QEXTNavTreeItem);
    if (d->m_text != text)
    {
        d->m_text = text;
        emit this->textChanged(this);
    }
}

QString QEXTNavTreeItem::tip() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return d->m_tip;
}

void QEXTNavTreeItem::setTip(const QString &tip)
{
    QEXT_DECL_D(QEXTNavTreeItem);
    if (d->m_tip != tip)
    {
        d->m_tip = tip;
        emit this->tipChanged(this);
    }
}

bool QEXTNavTreeItem::isExpand() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return d->m_expand;
}

void QEXTNavTreeItem::setExpand(const bool &expand)
{
    QEXT_DECL_D(QEXTNavTreeItem);
    if (d->m_expand != expand)
    {
        d->m_expand = expand;
        emit this->expandChanged(this);
    }
}

int QEXTNavTreeItem::level() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return d->m_level;
}

bool QEXTNavTreeItem::isLastItem() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    if (!d->m_parent.isNull())
    {
        return d->m_parent->childItems().last() == this;
    }
    return false;
}

bool QEXTNavTreeItem::isChildItem() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return !d->m_parent.isNull();
}

bool QEXTNavTreeItem::isParentItem() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return !d->m_childItems.isEmpty();
}

QEXTNavTreeItem *QEXTNavTreeItem::parentItem() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return d->m_parent.data();
}

void QEXTNavTreeItem::setParentItem(QEXTNavTreeItem *parent)
{
    QEXT_DECL_D(QEXTNavTreeItem);
    if (d->m_parent.data() != parent)
    {
        QEXTNavTreeItem *oldParent = d->m_parent.data();
        emit this->parentItemAboutToBeChanged(oldParent, parent);
        if (!d->m_parent.isNull())
        {
            d->m_parent->removeChildItem(this);
        }
        d->m_parent = parent;
        d->m_parent->addChildItem(this);
        d->updateLevel();
        this->setParent(parent);
        emit this->parentItemChanged(oldParent, parent);
    }
}

int QEXTNavTreeItem::childItemsCount() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return d->m_childItems.size();
}

QList<QEXTNavTreeItem *> QEXTNavTreeItem::childItems() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    return d->m_childItems;
}

void QEXTNavTreeItem::addChildItems(const QList<QEXTNavTreeItem *> &items)
{
    QList<QEXTNavTreeItem *>::const_iterator iter;
    for (iter = items.begin(); iter != items.end(); ++iter)
    {
        this->addChildItem(*iter);
    }
}

void QEXTNavTreeItem::addChildItem(QEXTNavTreeItem *item)
{
    QEXT_DECL_D(QEXTNavTreeItem);
    if (d->m_childItems.contains(item))
    {
        qWarning() << "QEXTNavTreeItem::addChildItem(): child item alreay exist";
        return;
    }
    emit this->childItemAboutToBeInserted(item, this);
    d->m_childItems.append(item);
    emit this->childItemInserted(item, this);
}

void QEXTNavTreeItem::prependChildItem(QEXTNavTreeItem *item)
{
    QEXT_DECL_D(QEXTNavTreeItem);
    if (d->m_childItems.contains(item))
    {
        qWarning() << "QEXTNavTreeItem::prependChildItem(): child item alreay exist";
        return;
    }
    emit this->childItemAboutToBeInserted(item, this);
    d->m_childItems.prepend(item);
    emit this->childItemInserted(item, this);
}

void QEXTNavTreeItem::removeChildItem(QEXTNavTreeItem *item)
{
    QEXT_DECL_D(QEXTNavTreeItem);
    if (!d->m_childItems.contains(item))
    {
        qWarning() << "QEXTNavTreeItem::removeChildItem(): child item not exist";
        return;
    }
    emit this->childItemAboutToBeRemoved(item, this);
    d->m_childItems.removeOne(item);
    emit this->childItemRemoved(item, this);
}

void QEXTNavTreeItem::insertChildItem(QEXTNavTreeItem *preItem, QEXTNavTreeItem *item)
{
    QEXT_DECL_D(QEXTNavTreeItem);
    if (d->m_childItems.contains(preItem))
    {
        qWarning() << "QEXTNavTreeItem::removeChildItem(): child preItem not exist";
        return;
    }
    if (d->m_childItems.contains(item))
    {
        qWarning() << "QEXTNavTreeItem::removeChildItem(): child item alreay exist";
        return;
    }
    emit this->childItemAboutToBeInserted(item, this);
    d->m_childItems.insert(d->m_childItems.indexOf(preItem), item);
    emit this->childItemInserted(item, this);
}

int QEXTNavTreeItem::indexOfParentItem() const
{
    QEXT_DECL_DC(QEXTNavTreeItem);
    if (!d->m_parent.isNull())
    {
        return d->m_parent->childItems().indexOf(const_cast<QEXTNavTreeItem *>(this));
    }
    return -1;
}



QEXTNavTreeDelegate::QEXTNavTreeDelegate(QEXTNavTreeWidget *parent) : QStyledItemDelegate(parent)
{
    m_navListView = parent;

    //判断图形字体是否存在,不存在则加入
    QFontDatabase fontDb;
    if (!fontDb.families().contains("FontAwesome"))
    {
        int fontId = fontDb.addApplicationFont(":/font/fontawesome-webfont.ttf");
        QStringList fontName = fontDb.applicationFontFamilies(fontId);
        if (fontName.count() == 0)
        {
            qWarning() << "load fontawesome-webfont.ttf error";
        }
    }

    if (fontDb.families().contains("FontAwesome"))
    {
        m_iconFont = QFont("FontAwesome");
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
        m_iconFont.setHintingPreference(QFont::PreferNoHinting);
#endif
    }
}

QEXTNavTreeDelegate::~QEXTNavTreeDelegate()
{

}

QSize QEXTNavTreeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QEXTNavTreeItem *item = (QEXTNavTreeItem *)index.data(Qt::UserRole).toLongLong();

    //设置最小的宽高
    bool parent = item->isParentItem();
    QSize size(50, parent ? m_navListView->rootItemHeight() : m_navListView->childItemHeight());
    return size;
}

void QEXTNavTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    QEXTNavTreeItem *item = (QEXTNavTreeItem *)index.data(Qt::UserRole).toLongLong();

    //定义变量存储区域
    QRect optionRect = option.rect;
    optionRect.setX(0);
    int x = optionRect.x();
    int y = optionRect.y();
    int width = optionRect.width();
    int height = optionRect.height();

    int fontSize = m_navListView->rootItemFontSize();

    //父节点和子节点颜色分开设置
    bool parent = item->isParentItem();

    //根据不同的状态设置不同的颜色 bgColor-主背景色 textColor-主文字颜色 tipBgColor-提示信息背景颜色 tipTextColor-提示信息文字颜色
    QColor bgColor, textColor, tipBgColor, tipTextColor, iconColor;
    if (option.state & QStyle::State_Selected)
    {
        bgColor = parent ? m_navListView->rootItemBackgroundSelectedColor() : m_navListView->childItemBackgroundSelectedColor();
        textColor = parent ? m_navListView->rootItemTextSelectedColor() : m_navListView->childItemTextSelectedColor();
        tipBgColor = parent ? m_navListView->rootItemTextSelectedColor() : m_navListView->childItemTextSelectedColor();
        tipTextColor = parent ? m_navListView->rootItemBackgroundSelectedColor() : m_navListView->childItemBackgroundSelectedColor();
        iconColor = parent ? m_navListView->rootItemTextSelectedColor() : m_navListView->childItemTextSelectedColor();
    }
    else if (option.state & QStyle::State_MouseOver)
    {
        bgColor = parent ? m_navListView->rootItemBackgroundHoverColor() : m_navListView->childItemBackgroundHoverColor();
        textColor = parent ? m_navListView->rootItemTextHoverColor() : m_navListView->childItemTextHoverColor();
        tipBgColor = parent ? m_navListView->rootItemTextSelectedColor() : m_navListView->childItemTextSelectedColor();
        tipTextColor = parent ? m_navListView->rootItemBackgroundSelectedColor() : m_navListView->childItemBackgroundSelectedColor();
        iconColor = parent ? m_navListView->rootItemTextHoverColor() : m_navListView->childItemTextHoverColor();
    }
    else
    {
        bgColor = parent ? m_navListView->rootItemBackgroundNormalColor() : m_navListView->childItemBackgroundNormalColor();
        textColor = parent ? m_navListView->rootItemTextNormalColor() : m_navListView->childItemTextNormalColor();
        tipBgColor = parent ? m_navListView->rootItemBackgroundSelectedColor() : m_navListView->childItemBackgroundSelectedColor();
        tipTextColor = parent ? m_navListView->rootItemTextSelectedColor() : m_navListView->childItemTextSelectedColor();
        iconColor = parent ? m_navListView->rootItemTextNormalColor() : m_navListView->childItemTextNormalColor();
    }

    //绘制背景
    painter->fillRect(optionRect, bgColor);

    //绘制线条,目前限定子节点绘制,如果需要父节点也绘制则取消parent判断即可
    int lineWidth = m_navListView->itemIineWidth();
    if (!parent && m_navListView->isItemLineVisible() && lineWidth > 0)
    {
        if ((option.state & QStyle::State_Selected) || (option.state & QStyle::State_MouseOver))
        {
            //设置偏移量,不然上下部分会有点偏移
            float offset = (float)lineWidth / 2;

            //计算上下两个坐标点
            QPointF pointTop(x, y + offset);
            QPointF pointBottom(x, height + y - offset);
            if (!m_navListView->isItemLineInLeft())
            {
                pointTop.setX(width);
                pointBottom.setX(width);
            }

            //设置线条颜色和宽度
            painter->setPen(QPen(m_navListView->itemLineColor(), lineWidth));
            painter->drawLine(pointTop, pointBottom);
        }
    }

    //绘制三角形,目前限定子节点绘制,如果需要父节点也绘制则取消parent判断即可
    int triangleWidth = m_navListView->itemTriangleWidth();
    if (!parent && m_navListView->ItemTriangleVisible() && triangleWidth > 0)
    {
        if ((option.state & QStyle::State_Selected) || (option.state & QStyle::State_MouseOver))
        {
            QFont font = m_iconFont;
            font.setPixelSize(fontSize + triangleWidth);
            painter->setFont(font);
            painter->setPen(m_navListView->itemTriangleColor());

            //采用图形字体中的三角形绘制
            if (m_navListView->isItemTriangleInLeft())
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
    if (m_navListView->isITemSeparateVisible())
    {
        if (item->isParentItem() || (item->isChildItem() && item->isLastItem()))
        {
            painter->setPen(QPen(m_navListView->itemSeparateColor(), m_navListView->itemSeparateHeight()));
            painter->drawLine(QPointF(x, y + height), QPointF(x + width, y + height));
        }
    }

    //绘制文字,如果文字为空则不绘制
    QString text = item->text();
    if (!text.isEmpty())
    {
        //文字离左边的距离+字体大小
        int margin = m_navListView->indentation() * item->level();
        if (item->isChildItem())
        {
            margin = m_navListView->childItemMargin();
            fontSize = m_navListView->childItemFontSize();
        }

        //计算文字区域
        QRect textRect = optionRect;
        textRect.setWidth(width - margin);
        textRect.setX(x + margin);

        QFont font;
        font.setPixelSize(fontSize);
        painter->setFont(font);
        painter->setPen(textColor);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
    }

    //绘制提示信息,如果不需要显示提示信息或者提示信息为空则不绘制
    QString tip = item->tip();
    if (m_navListView->isItemTipVisible() && !tip.isEmpty())
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
        tipRect.setLeft(optionRect.right() - m_navListView->itemTipWidth() - 5);
        tipRect.setRight(optionRect.right() - 5);

        //设置字体大小
        QFont font;
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
    iconRect.setLeft(parent ? m_navListView->rootItemIconMargin() : m_navListView->childItemIconMargin());

    //设置图形字体和画笔颜色
    QFont font = m_iconFont;
    font.setPixelSize(fontSize);
    painter->setFont(font);
    painter->setPen(textColor);

    //绘制左侧图标,有图标则绘制图标,没有的话父窗体取 + -
    QChar icon = item->fontChar();
    if (!icon.isNull())
    {
        painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, icon);
    }
    else if (parent)
    {
        if (item->isExpand())
        {
            painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf068));
        }
        else
        {
            painter->drawText(iconRect, Qt::AlignLeft | Qt::AlignVCenter, QChar(0xf067));
        }
    }

    //绘制父节点右侧图标
    iconRect.setRight(optionRect.width() - 10);
    if (!(m_navListView->isItemTipVisible() && !item->tip().isEmpty()) && m_navListView->isItemRightIconVisible() && parent)
    {
        if (item->isExpand())
        {
            painter->drawText(iconRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf054));
        }
        else
        {
            painter->drawText(iconRect, Qt::AlignRight | Qt::AlignVCenter, QChar(0xf078));
        }
    }
}


QEXTNavTreeModel::QEXTNavTreeModel(QEXTNavTreeWidget *parent)	: QAbstractItemModel(parent)
{
    m_navListView = parent;
}

QEXTNavTreeModel::~QEXTNavTreeModel()
{
    qDeleteAll(m_rootItemList);
    m_rootItemList.clear();
    m_itemSet.clear();
}

QModelIndex QEXTNavTreeModel::indexFromItem(QEXTNavTreeItem *item) const
{
    if (m_itemSet.contains(item))
    {
        if (item->parentItem())
        {
            QList<QEXTNavTreeItem *> childItems = item->parentItem()->childItems();
            return this->createIndex(childItems.indexOf(item), 1, item);
        }
        else
        {
            return this->createIndex(m_rootItemList.indexOf(item), 1, item);
        }
    }
    return QModelIndex();
}

QEXTNavTreeItem *QEXTNavTreeModel::itemFromIndex(const QModelIndex &index) const
{
    return index.isValid() ? static_cast<QEXTNavTreeItem *>(index.internalPointer()) : QEXT_DECL_NULLPTR;
}

QEXTNavTreeItem *QEXTNavTreeModel::itemFromText(const QString &text) const
{
    return m_textItemMap.value(text);
}

QList<QEXTNavTreeItem *> QEXTNavTreeModel::rootItems() const
{
    return m_rootItemList;
}

QList<QEXTNavTreeItem *> QEXTNavTreeModel::allItems() const
{
    return m_itemSet.toList();
}

void QEXTNavTreeModel::iterateItems(const QList<QEXTNavTreeItem *> &items)
{
    QList<QEXTNavTreeItem *>::const_iterator iter;
    for (iter = items.begin(); iter != items.end(); ++iter)
    {
        QList<QEXTNavTreeItem *> childItemsList = (*iter)->childItems();
        if (!childItemsList.isEmpty())
        {
            this->iterateItems(childItemsList);
        }
        m_itemSet.insert(*iter);
        m_textItemMap.insert((*iter)->text(), *iter);
    }
}
//Signature is not normalized. instead of expandChanged(QEXTNavTreeItem *) [clazy-connect-not-normalized]
void QEXTNavTreeModel::initItems()
{
    QSet<QEXTNavTreeItem *>::iterator iter;
    for (iter = m_itemSet.begin(); iter != m_itemSet.end(); ++iter)
    {
        connect(*iter, SIGNAL(expandChanged(QEXTNavTreeItem *)),
                this, SLOT(onItemExpandeChanged(QEXTNavTreeItem *)));
        connect(*iter, SIGNAL(childItemAboutToBeInserted(QEXTNavTreeItem *, QEXTNavTreeItem *)),
                this, SLOT(onChildItemAboutToBeInserted(QEXTNavTreeItem *, QEXTNavTreeItem *)));
        connect(*iter, SIGNAL(childItemInserted(QEXTNavTreeItem *, QEXTNavTreeItem *)),
                this, SLOT(onChildItemInserted(QEXTNavTreeItem *, QEXTNavTreeItem *)));
        connect(*iter, SIGNAL(childItemAboutToBeRemoved(QEXTNavTreeItem *, QEXTNavTreeItem *)),
                this, SLOT(onChildItemAboutToBeRemoved(QEXTNavTreeItem *, QEXTNavTreeItem *)));
        connect(*iter, SIGNAL(childItemRemoved(QEXTNavTreeItem *, QEXTNavTreeItem *)),
                this, SLOT(onChildItemRemoved(QEXTNavTreeItem *, QEXTNavTreeItem *)));
    }
}

void QEXTNavTreeModel::onItemExpandeChanged(QEXTNavTreeItem *item)
{
    QModelIndex index = this->indexFromItem(item);
    if (item->isExpand())
    {
        m_navListView->expand(index);
    }
    else
    {
        m_navListView->collapse(index);
    }
}

void QEXTNavTreeModel::onParentItemAboutToBeChanged(QEXTNavTreeItem *oldParent, QEXTNavTreeItem *newParent)
{
    QModelIndex index = this->indexFromItem(oldParent);
    emit this->dataChanged(index, index);
    index = this->indexFromItem(newParent);
    emit this->dataChanged(index, index);
}

void QEXTNavTreeModel::onParentItemChanged(QEXTNavTreeItem *oldParent, QEXTNavTreeItem *newParent)
{

}

void QEXTNavTreeModel::onChildItemAboutToBeInserted(QEXTNavTreeItem *item, QEXTNavTreeItem *parent)
{
    QModelIndex index = this->indexFromItem(parent);
    int row = parent->childItems().indexOf(item);
    this->beginInsertRows(index, row, row);
}

void QEXTNavTreeModel::onChildItemInserted(QEXTNavTreeItem *item, QEXTNavTreeItem *parent)
{
    Q_UNUSED(item);
    Q_UNUSED(parent);
    this->endInsertRows();
}

void QEXTNavTreeModel::onChildItemAboutToBeRemoved(QEXTNavTreeItem *item, QEXTNavTreeItem *parent)
{
    QModelIndex index = this->indexFromItem(parent);
    int row = parent->childItems().indexOf(item);
    this->beginRemoveRows(index, row, row);
}

void QEXTNavTreeModel::onChildItemRemoved(QEXTNavTreeItem *item, QEXTNavTreeItem *parent)
{
    Q_UNUSED(item);
    Q_UNUSED(parent);
    this->endRemoveRows();
}


void QEXTNavTreeModel::setItems(const QStringList &items)
{
    if (!items.isEmpty())
    {
        this->beginResetModel();

        qDeleteAll(m_rootItemList);
        m_rootItemList.clear();
        m_itemSet.clear();

        bool ok = true;
        //listItem格式: 标题|父节点标题(父节点为空)|是否展开|提示信息|左侧图标
        QHash<QEXTNavTreeItem *, QString> itemParentTextMap;
        for (int i = 0; i < items.count(); i++)
        {
            QString itemString = items.at(i);
            QStringList list = itemString.split("|");
            QString text = list.at(0);
            QString parentText = list.at(1);
            QString expand = list.at(2);
            QString tip = list.at(3);
            QString icon = list.at(4);
            icon = icon.replace("0x", "");

            QEXTNavTreeItem *item = new QEXTNavTreeItem;
            item->setText(text);
            item->setExpand(expand.toInt());
            item->setTip(tip);
            if (!icon.isEmpty())
            {
                item->setFontIcon(QChar(icon.toInt(&ok, 16)));
            }
            if (parentText.isEmpty())
            {
                m_rootItemList.append(item);
            }
            else
            {
                m_childItemList.append(item);
                itemParentTextMap.insert(item, parentText);
            }
            m_textItemMap.insert(text, item);
            m_itemSet.insert(item);
        }

        for (int i = 0; i < m_childItemList.count(); i++)
        {
            QEXTNavTreeItem *item = m_childItemList.at(i);
            QString parentText = itemParentTextMap.value(item);
            QEXTNavTreeItem *parentItem = m_textItemMap.value(parentText);
            if (parentItem)
            {
                item->setParentItem(parentItem);
            }
            else
            {
                m_rootItemList.append(item);
            }
        }
    }
    this->initItems();

    this->endResetModel();
}

void QEXTNavTreeModel::setItems(const QList<QEXTNavTreeItem *> &items)
{
    this->beginResetModel();

    qDeleteAll(m_rootItemList);
    m_rootItemList.clear();
    m_itemSet.clear();

    this->iterateItems(items);
    this->initItems();

    this->endResetModel();
}

void QEXTNavTreeModel::expandItem(const QModelIndex &index)
{
    QEXTNavTreeItem *item = this->itemFromIndex(index);
    if (item)
    {
        item->setExpand(!item->isExpand());
    }
}

QModelIndex QEXTNavTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    QEXTNavTreeItem *parentItem = this->itemFromIndex(parent);
    if (parentItem)
    {
        const bool isValidRow = row >= 0 && row < this->rowCount(parent);
        const bool isValidColumn = column >= 0 && column < this->columnCount(parent);
        if (isValidRow && isValidColumn)
        {
            QList<QEXTNavTreeItem *> childItems = parentItem->childItems();
            return this->createIndex(row, 0, childItems.at(row));
        }
    }
    else
    {
        return this->createIndex(row, 0, m_rootItemList.at(row));
    }
    return QModelIndex();
}

QModelIndex QEXTNavTreeModel::parent(const QModelIndex &child) const
{
    QEXTNavTreeItem *childItem = this->itemFromIndex(child);
    if (childItem)
    {
        QEXTNavTreeItem *parentItem = childItem->parentItem();
        if (parentItem)
        {
            QEXTNavTreeItem *grandParentItem = parentItem->parentItem();
            if (grandParentItem)
            {
                QList<QEXTNavTreeItem *> childItems = grandParentItem->childItems();
                return this->createIndex(childItems.indexOf(parentItem), 0, parentItem);
            }
            else
            {
                return this->createIndex(m_rootItemList.indexOf(parentItem), 0, parentItem);
            }
        }
    }
    return QModelIndex();
}

bool QEXTNavTreeModel::hasChildren(const QModelIndex &parent) const
{
    QEXTNavTreeItem *parentItem = this->itemFromIndex(parent);
    if (parentItem)
    {
        return 0 != parentItem->childItemsCount();
    }
    return true;
}

QVariant QEXTNavTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    QEXTNavTreeItem *item = this->itemFromIndex(index);
    if (item)
    {
        if (role == Qt::DisplayRole)
        {
            return item->text();
        }
        else if (role == Qt::UserRole)
        {
            return (quint64)(item);
        }
    }

    return QVariant();
}

int QEXTNavTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        QEXTNavTreeItem *item = this->itemFromIndex(parent);
        if (item)
        {
            return item->childItemsCount();
        }
    }
    return m_rootItemList.size();
}

int QEXTNavTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}



QEXTNavTreeWidget::QEXTNavTreeWidget(QWidget *parent) : QTreeView(parent)
{
    m_activeItem = QEXT_DECL_NULLPTR;

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
    m_parentBkgNormalColor = QColor(57, 61, 73);
    m_parentBkgSelectedColor = QColor(78, 83, 102);
    m_parentBkgHoverColor = QColor(78, 83, 102);
    m_parentTextNormalColor = QColor(250, 250, 250);
    m_parentTextSelectedColor = QColor(250, 250, 250);
    m_parentTextHoverColor = QColor(250, 250, 250);

    m_childIconMargin = 15;
    m_childMargin = 35;
    m_childFontSize = 12;
    m_childHeight = 30;
    m_childBkgNormalColor = QColor(40, 43, 51);
    m_childBkgSelectedColor = QColor(20, 20, 20);
    m_childBkgHoverColor = QColor(20, 20, 20);
    m_childTextNormalColor = QColor(180, 180, 180);
    m_childTextSelectedColor = QColor(250, 250, 250);
    m_childTextHoverColor = QColor(255, 255, 255);

    m_expendMode = ExpendMode_SingleClick;

    this->setIndentation(20);
//    this->setMouseTracking(true);
    this->setHeaderHidden(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    m_model = new QEXTNavTreeModel(this);
    m_delegate = new QEXTNavTreeDelegate(this);
    this->setModel(m_model);
    this->setItemDelegate(m_delegate);
    connect(this, SIGNAL(pressed(QModelIndex)), this, SLOT(onItemPressed(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)), m_model, SLOT(expandItem(QModelIndex)));
}

QEXTNavTreeWidget::~QEXTNavTreeWidget()
{
    delete m_model;
    delete m_delegate;
}

QList<QEXTNavTreeItem *> QEXTNavTreeWidget::allItems() const
{
    return m_model->allItems();
}

QList<QEXTNavTreeItem *> QEXTNavTreeWidget::rootItems() const
{
    return m_model->rootItems();
}

QEXTNavTreeItem *QEXTNavTreeWidget::activeItem() const
{
    return m_activeItem;
}

void QEXTNavTreeWidget::onItemPressed(const QModelIndex &index)
{
    QEXTNavTreeItem *item = reinterpret_cast<QEXTNavTreeItem *>(index.data(Qt::UserRole).toULongLong());
    if (item)
    {
        this->setCurrentIndex(index);
        emit this->itemPressed(item);
    }
}

bool QEXTNavTreeWidget::isItemRightIconVisible() const
{
    return m_rightIconVisible;
}

bool QEXTNavTreeWidget::isItemTipVisible() const
{
    return m_tipVisible;
}

int QEXTNavTreeWidget::itemTipWidth() const
{
    return m_tipWidth;
}

bool QEXTNavTreeWidget::isITemSeparateVisible() const
{
    return m_separateVisible;
}

int QEXTNavTreeWidget::itemSeparateHeight() const
{
    return m_separateHeight;
}

QColor QEXTNavTreeWidget::itemSeparateColor() const
{
    return m_separateColor;
}

bool QEXTNavTreeWidget::isItemLineInLeft() const
{
    return m_lineLeft;
}

bool QEXTNavTreeWidget::isItemLineVisible() const
{
    return m_lineVisible;
}

int QEXTNavTreeWidget::itemIineWidth() const
{
    return m_lineWidth;
}

QColor QEXTNavTreeWidget::itemLineColor() const
{
    return m_lineColor;
}

bool QEXTNavTreeWidget::isItemTriangleInLeft() const
{
    return m_triangleLeft;
}

bool QEXTNavTreeWidget::ItemTriangleVisible() const
{
    return m_triangleVisible;
}

int QEXTNavTreeWidget::itemTriangleWidth() const
{
    return m_triangleWidth;
}

QColor QEXTNavTreeWidget::itemTriangleColor() const
{
    return m_triangleColor;
}

int QEXTNavTreeWidget::rootItemIconMargin() const
{
    return m_parentIconMargin;
}

int QEXTNavTreeWidget::rootItemMargin() const
{
    return m_parentMargin;
}

int QEXTNavTreeWidget::rootItemFontSize() const
{
    return m_parentFontSize;
}

int QEXTNavTreeWidget::rootItemHeight() const
{
    return m_parentHeight;
}

QColor QEXTNavTreeWidget::rootItemBackgroundNormalColor() const
{
    return m_parentBkgNormalColor;
}

QColor QEXTNavTreeWidget::rootItemBackgroundSelectedColor() const
{
    return m_parentBkgSelectedColor;
}

QColor QEXTNavTreeWidget::rootItemBackgroundHoverColor() const
{
    return m_parentBkgHoverColor;
}

QColor QEXTNavTreeWidget::rootItemTextNormalColor() const
{
    return m_parentTextNormalColor;
}

QColor QEXTNavTreeWidget::rootItemTextSelectedColor() const
{
    return m_parentTextSelectedColor;
}

QColor QEXTNavTreeWidget::rootItemTextHoverColor() const
{
    return m_parentTextHoverColor;
}

int QEXTNavTreeWidget::childItemIconMargin() const
{
    return m_childIconMargin;
}

int QEXTNavTreeWidget::childItemMargin() const
{
    return m_childMargin;
}

int QEXTNavTreeWidget::childItemFontSize() const
{
    return m_childFontSize;
}

int QEXTNavTreeWidget::childItemHeight() const
{
    return m_childHeight;
}

QColor QEXTNavTreeWidget::childItemBackgroundNormalColor() const
{
    return m_childBkgNormalColor;
}

QColor QEXTNavTreeWidget::childItemBackgroundSelectedColor() const
{
    return m_childBkgSelectedColor;
}

QColor QEXTNavTreeWidget::childItemBackgroundHoverColor() const
{
    return m_childBkgHoverColor;
}

QColor QEXTNavTreeWidget::childItemTextNormalColor() const
{
    return m_childTextNormalColor;
}

QColor QEXTNavTreeWidget::childItemTextSelectedColor() const
{
    return m_childTextSelectedColor;
}

QColor QEXTNavTreeWidget::childItemTextHoverColor() const
{
    return m_childTextHoverColor;
}

QEXTNavTreeWidget::ExpendModeType QEXTNavTreeWidget::expendMode() const
{
    return m_expendMode;
}

QSize QEXTNavTreeWidget::sizeHint() const
{
    return QSize(200, 300);
}

QSize QEXTNavTreeWidget::minimumSizeHint() const
{
    return QSize(20, 20);
}

void QEXTNavTreeWidget::setItems(const QList<QEXTNavTreeItem *> &items)
{
    if (items != m_itemsList)
    {
        m_itemsList.clear();
        m_itemsString.clear();
        m_itemsList = items;

        m_model->setItems(items);
    }
}

void QEXTNavTreeWidget::setItems(const QString &items)
{
    if (m_itemsString != items)
    {
        m_itemsList.clear();
        m_itemsString.clear();
        m_itemsString = items;

        QStringList listItems = items.split(",");
        m_model->setItems(listItems);
    }
}

void QEXTNavTreeWidget::setCurrentItem(QEXTNavTreeItem *item)
{
    QModelIndex index = m_model->indexFromItem(item);
    this->setCurrentIndex(index);
}

void QEXTNavTreeWidget::setCurrentItem(const QString &text)
{
    QEXTNavTreeItem *item = m_model->itemFromText(text);
    QModelIndex index = m_model->indexFromItem(item);
    this->setCurrentIndex(index);
}

void QEXTNavTreeWidget::setRightIconVisible(bool rightIconVisible)
{
    m_rightIconVisible = rightIconVisible;
}

void QEXTNavTreeWidget::setTipVisible(bool tipVisible)
{
    m_tipVisible = tipVisible;
}

void QEXTNavTreeWidget::setTipWidth(int tipWidth)
{
    m_tipWidth = tipWidth;
}

void QEXTNavTreeWidget::setSeparateVisible(bool separateVisible)
{
    m_separateVisible = separateVisible;
}

void QEXTNavTreeWidget::setSeparateHeight(int separateHeight)
{
    m_separateHeight = separateHeight;
}

void QEXTNavTreeWidget::setSeparateColor(const QColor &separateColor)
{
    m_separateColor = separateColor;
}

void QEXTNavTreeWidget::setLineLeft(bool lineLeft)
{
    m_lineLeft = lineLeft;
}

void QEXTNavTreeWidget::setLineVisible(bool lineVisible)
{
    m_lineVisible = lineVisible;
}

void QEXTNavTreeWidget::setLineWidth(int lineWidth)
{
    m_lineWidth = lineWidth;
}

void QEXTNavTreeWidget::setLineColor(const QColor &lineColor)
{
    m_lineColor = lineColor;
}

void QEXTNavTreeWidget::setTriangleLeft(bool triangleLeft)
{
    m_triangleLeft = triangleLeft;
}

void QEXTNavTreeWidget::setTriangleVisible(bool triangleVisible)
{
    m_triangleVisible = triangleVisible;
}

void QEXTNavTreeWidget::setTriangleWidth(int triangleWidth)
{
    m_triangleWidth = triangleWidth;
}

void QEXTNavTreeWidget::setTriangleColor(const QColor &triangleColor)
{
    m_triangleColor = triangleColor;
}

void QEXTNavTreeWidget::setParentIconMargin(int parentIconMargin)
{
    m_parentIconMargin = parentIconMargin;
}

void QEXTNavTreeWidget::setParentMargin(int parentMargin)
{
    m_parentMargin = parentMargin;
}

void QEXTNavTreeWidget::setParentFontSize(int parentFontSize)
{
    m_parentFontSize = parentFontSize;
}

void QEXTNavTreeWidget::setParentHeight(int parentHeight)
{
    m_parentHeight = parentHeight;
}

void QEXTNavTreeWidget::setParentBgNormalColor(const QColor &parentBgNormalColor)
{
    m_parentBkgNormalColor = parentBgNormalColor;
}

void QEXTNavTreeWidget::setParentBgSelectedColor(const QColor &parentBgSelectedColor)
{
    m_parentBkgSelectedColor = parentBgSelectedColor;
}

void QEXTNavTreeWidget::setParentBgHoverColor(const QColor &parentBgHoverColor)
{
    m_parentBkgHoverColor = parentBgHoverColor;
}

void QEXTNavTreeWidget::setParentTextNormalColor(const QColor &parentTextNormalColor)
{
    m_parentTextNormalColor = parentTextNormalColor;
}

void QEXTNavTreeWidget::setParentTextSelectedColor(const QColor &parentTextSelectedColor)
{
    m_parentTextSelectedColor = parentTextSelectedColor;
}

void QEXTNavTreeWidget::setParentTextHoverColor(const QColor &parentTextHoverColor)
{
    m_parentTextHoverColor = parentTextHoverColor;
}

void QEXTNavTreeWidget::setChildIconMargin(int childIconMargin)
{
    m_childIconMargin = childIconMargin;
}

void QEXTNavTreeWidget::setChildMargin(int childMargin)
{
    m_childMargin = childMargin;
}

void QEXTNavTreeWidget::setChildFontSize(int childFontSize)
{
    m_childFontSize = childFontSize;
}

void QEXTNavTreeWidget::setChildHeight(int childHeight)
{
    m_childHeight = childHeight;
}

void QEXTNavTreeWidget::setChildBgNormalColor(const QColor &childBgNormalColor)
{
    m_childBkgNormalColor = childBgNormalColor;
}

void QEXTNavTreeWidget::setChildBgSelectedColor(const QColor &childBgSelectedColor)
{
    m_childBkgSelectedColor = childBgSelectedColor;
}

void QEXTNavTreeWidget::setChildBgHoverColor(const QColor &childBgHoverColor)
{
    m_childBkgHoverColor = childBgHoverColor;
}

void QEXTNavTreeWidget::setChildTextNormalColor(const QColor &childTextNormalColor)
{
    m_childTextNormalColor = childTextNormalColor;
}

void QEXTNavTreeWidget::setChildTextSelectedColor(const QColor &childTextSelectedColor)
{
    m_childTextSelectedColor = childTextSelectedColor;
}

void QEXTNavTreeWidget::setChildTextHoverColor(const QColor &childTextHoverColor)
{
    m_childTextHoverColor = childTextHoverColor;
}

void QEXTNavTreeWidget::setExpendMode(const QEXTNavTreeWidget::ExpendModeType &expendMode)
{
    if(expendMode != m_expendMode)
    {
        m_expendMode = expendMode;
        if(expendMode == ExpendMode_SingleClick)
        {
            disconnect(this, SIGNAL(doubleClicked(QModelIndex)), m_model, SLOT(expandItem(QModelIndex)));
            connect(this, SIGNAL(clicked(QModelIndex)), m_model, SLOT(expandItem(QModelIndex)));
        }
        else if(expendMode == ExpendMode_DoubleClick)
        {
            disconnect(this, SIGNAL(clicked(QModelIndex)), m_model, SLOT(expandItem(QModelIndex)));
            connect(this, SIGNAL(doubleClicked(QModelIndex)), m_model, SLOT(expandItem(QModelIndex)));
        }
        else if(expendMode == ExpendMode_NoClick)
        {
            disconnect(this, SIGNAL(clicked(QModelIndex)), m_model, SLOT(expandItem(QModelIndex)));
            disconnect(this, SIGNAL(doubleClicked(QModelIndex)), m_model, SLOT(expandItem(QModelIndex)));
        }
    }
}
