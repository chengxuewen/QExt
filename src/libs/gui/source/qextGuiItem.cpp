#include <qextGuiItem.h>
#include <qextGuiItem_p.h>


QEXTGuiItemPrivate::QEXTGuiItemPrivate(QEXTGuiItem *q)
    : q_ptr(q)
{

}

QEXTGuiItemPrivate::~QEXTGuiItemPrivate()
{

}



QEXTGuiItem::QEXTGuiItem(QEXTGuiItem *parent)
    : QObject(parent), d_ptr(new QEXTGuiItemPrivate(this))
{

}

QEXTGuiItem::~QEXTGuiItem()
{

}

QEXTGuiItem *QEXTGuiItem::parentItem() const
{

}

void QEXTGuiItem::setParentItem(QEXTGuiItem *parent)
{

}

bool QEXTGuiItem::enabled() const
{

}

void QEXTGuiItem::setEnabled(bool enabled)
{

}

qreal QEXTGuiItem::opacity() const
{

}

void QEXTGuiItem::setOpacity(qreal opacity)
{

}

qreal QEXTGuiItem::rotation() const
{

}

void QEXTGuiItem::setRotation(qreal rotation)
{

}

qreal QEXTGuiItem::scale() const
{

}

void QEXTGuiItem::setScale(qreal scale)
{

}

bool QEXTGuiItem::visiable() const
{

}

void QEXTGuiItem::setVisiable(bool visiable)
{

}

bool QEXTGuiItem::clip() const
{

}

void QEXTGuiItem::setClip(bool clip)
{

}

bool QEXTGuiItem::smooth() const
{

}

void QEXTGuiItem::setSmooth(bool smooth)
{

}

bool QEXTGuiItem::antialiasing() const
{

}

void QEXTGuiItem::setAntialiasing(bool antialiasing)
{

}

void QEXTGuiItem::resetAntialiasing()
{

}

QSizeF QEXTGuiItem::size() const
{

}

void QEXTGuiItem::setSize(const QSizeF &size)
{

}

QPointF QEXTGuiItem::pos() const
{

}

void QEXTGuiItem::setPos(const QPointF &pos)
{

}

qreal QEXTGuiItem::width() const
{

}

void QEXTGuiItem::setWidth(qreal width)
{

}

void QEXTGuiItem::resetWidth()
{

}

qreal QEXTGuiItem::implicitWidth() const
{

}

void QEXTGuiItem::setImplicitWidth(qreal width)
{

}

qreal QEXTGuiItem::height() const
{

}

void QEXTGuiItem::setHeight(qreal height)
{

}

void QEXTGuiItem::resetHeight()
{

}

qreal QEXTGuiItem::implicitHeight() const
{

}

void QEXTGuiItem::setImplicitHeight(qreal height)
{

}

qreal QEXTGuiItem::x() const
{

}

void QEXTGuiItem::setX(qreal x)
{

}

qreal QEXTGuiItem::y() const
{

}

void QEXTGuiItem::setY(qreal y)
{

}

qreal QEXTGuiItem::z() const
{

}

void QEXTGuiItem::setZ(qreal z)
{

}

bool QEXTGuiItem::hasFocus() const
{

}

void QEXTGuiItem::setFocus(bool focus)
{

}

bool QEXTGuiItem::hasActiveFocus() const
{

}

void QEXTGuiItem::setActiveFocus(bool focus)
{

}

bool QEXTGuiItem::hasActiveFocusOnTab() const
{

}

void QEXTGuiItem::setActiveFocusOnTab(bool focus)
{

}


QEXTGuiItem::QEXTGuiItem(QEXTGuiItemPrivate *d, QEXTGuiItem *parent)
    : QObject(parent), d_ptr(d)
{

}
