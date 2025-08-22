#include <qextQuickTriangleItem.h>

#include <QPainterPath>
#include <QPainter>
#include <QDebug>

class QExtQuickTriangleItemPrivate
{
public:
    explicit QExtQuickTriangleItemPrivate(QExtQuickTriangleItem *q);
    virtual ~QExtQuickTriangleItemPrivate();

    QExtQuickTriangleItem * q_ptr;

    QColor m_color;
    QColor m_borderColor;
    int m_borderWidth;

private:
    QEXT_DECLARE_PUBLIC(QExtQuickTriangleItem)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQuickTriangleItemPrivate)
};

QExtQuickTriangleItemPrivate::QExtQuickTriangleItemPrivate(QExtQuickTriangleItem *q)
    : q_ptr(q)
    , m_color(Qt::red)
    , m_borderColor(Qt::transparent)
    , m_borderWidth(1)
{
}

QExtQuickTriangleItemPrivate::~QExtQuickTriangleItemPrivate()
{

}

QExtQuickTriangleItem::QExtQuickTriangleItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , dd_ptr(new QExtQuickTriangleItemPrivate(this))
{

}

QExtQuickTriangleItem::~QExtQuickTriangleItem()
{

}

QColor QExtQuickTriangleItem::color() const
{
    Q_D(const QExtQuickTriangleItem);
    return d->m_color;
}

void QExtQuickTriangleItem::setColor(const QColor &color)
{
    Q_D(QExtQuickTriangleItem);
    if (color != d->m_color)
    {
        d->m_color = color;
        this->update();
        emit this->colorChanged(color);
    }
}

QColor QExtQuickTriangleItem::borderColor() const
{
    Q_D(const QExtQuickTriangleItem);
    return d->m_borderColor;
}

void QExtQuickTriangleItem::setBorderColor(const QColor &color)
{
    Q_D(QExtQuickTriangleItem);
    if (color != d->m_borderColor)
    {
        d->m_borderColor = color;
        this->update();
        emit this->borderColorChanged(color);
    }
}

int QExtQuickTriangleItem::borderWidth() const
{
    Q_D(const QExtQuickTriangleItem);
    return d->m_borderWidth;
}

void QExtQuickTriangleItem::setBorderWidth(int width)
{
    Q_D(QExtQuickTriangleItem);
    width = qMin<int>(qMax<int>(1, width), this->width() / 2);
    if (width != d->m_borderWidth)
    {
        d->m_borderWidth = width;
        this->update();
        emit this->borderWidthChanged(width);
    }
}

void QExtQuickTriangleItem::paint(QPainter *painter)
{
    Q_D(QExtQuickTriangleItem);
    painter->save();
    painter->setBrush(d->m_color);
    painter->setPen(QPen(d->m_borderColor, d->m_borderWidth));
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    QPainterPath path(QPointF(this->width() / 2, 0));
    path.lineTo(QPointF(0, this->height()));
    path.lineTo(QPointF(this->width(), this->height()));
    path.lineTo(QPointF(this->width() / 2, 0));
    painter->drawPath(path);
    painter->restore();
}

