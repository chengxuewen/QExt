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

    QColor mColor;
    QColor mBorderColor;
    int mBorderWidth;

private:
    QEXT_DECLARE_PUBLIC(QExtQuickTriangleItem)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQuickTriangleItemPrivate)
};

QExtQuickTriangleItemPrivate::QExtQuickTriangleItemPrivate(QExtQuickTriangleItem *q)
    : q_ptr(q)
    , mColor(Qt::red)
    , mBorderColor(Qt::transparent)
    , mBorderWidth(1)
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
    return d->mColor;
}

void QExtQuickTriangleItem::setColor(const QColor &color)
{
    Q_D(QExtQuickTriangleItem);
    if (color != d->mColor)
    {
        d->mColor = color;
        this->update();
        emit this->colorChanged(color);
    }
}

QColor QExtQuickTriangleItem::borderColor() const
{
    Q_D(const QExtQuickTriangleItem);
    return d->mBorderColor;
}

void QExtQuickTriangleItem::setBorderColor(const QColor &color)
{
    Q_D(QExtQuickTriangleItem);
    if (color != d->mBorderColor)
    {
        d->mBorderColor = color;
        this->update();
        emit this->borderColorChanged(color);
    }
}

int QExtQuickTriangleItem::borderWidth() const
{
    Q_D(const QExtQuickTriangleItem);
    return d->mBorderWidth;
}

void QExtQuickTriangleItem::setBorderWidth(int width)
{
    Q_D(QExtQuickTriangleItem);
    width = qMin<int>(qMax<int>(1, width), this->width() / 2);
    if (width != d->mBorderWidth)
    {
        d->mBorderWidth = width;
        this->update();
        emit this->borderWidthChanged(width);
    }
}

void QExtQuickTriangleItem::paint(QPainter *painter)
{
    Q_D(QExtQuickTriangleItem);
    painter->save();
    painter->setBrush(d->mColor);
    painter->setPen(QPen(d->mBorderColor, d->mBorderWidth));
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    QPainterPath path(QPointF(this->width() / 2, 0));
    path.lineTo(QPointF(0, this->height()));
    path.lineTo(QPointF(this->width(), this->height()));
    path.lineTo(QPointF(this->width() / 2, 0));
    painter->drawPath(path);
    painter->restore();
}

