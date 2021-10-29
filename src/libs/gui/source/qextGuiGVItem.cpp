#include <qextGuiGVItem.h>
#include <qextGuiGVItem_p.h>


QEXTGuiGVItemPrivate::QEXTGuiGVItemPrivate(QEXTGuiGVItem *q)
    : q_ptr(q)
{

}

QEXTGuiGVItemPrivate::~QEXTGuiGVItemPrivate()
{

}



QEXTGuiGVItem::QEXTGuiGVItem(QEXTGuiGVItem *parent)
    : QGraphicsObject(parent), d_ptr(new QEXTGuiGVItemPrivate(this))
{

}

QEXTGuiGVItem::~QEXTGuiGVItem()
{

}

QEXTGuiGVItem *QEXTGuiGVItem::parentItem() const
{
    return qobject_cast<QEXTGuiGVItem *>(QGraphicsObject::parentObject());
}

void QEXTGuiGVItem::setParentItem(QEXTGuiGVItem *parent)
{
    QGraphicsObject::setParentItem(parent);
}
