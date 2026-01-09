#include <qextQuickTriangleItem.h>

#include <QPainterPath>
#include <QPainter>
#include <QDebug>

class QExtQuickTrianglePrivate
{
public:
    explicit QExtQuickTrianglePrivate(QExtQuickTriangle *q);
    virtual ~QExtQuickTrianglePrivate();

    QExtQuickTriangle * q_ptr;

    QColor mColor;
    QColor mBorderColor;
    int mBorderWidth;

private:
    QEXT_DECLARE_PUBLIC(QExtQuickTriangle)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQuickTrianglePrivate)
};

QExtQuickTrianglePrivate::QExtQuickTrianglePrivate(QExtQuickTriangle *q)
    : q_ptr(q)
    , mColor(Qt::red)
    , mBorderColor(Qt::transparent)
    , mBorderWidth(1)
{
}

QExtQuickTrianglePrivate::~QExtQuickTrianglePrivate()
{

}

QExtQuickTriangle::QExtQuickTriangle(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , dd_ptr(new QExtQuickTrianglePrivate(this))
{

}

QExtQuickTriangle::~QExtQuickTriangle()
{

}

QColor QExtQuickTriangle::color() const
{
    Q_D(const QExtQuickTriangle);
    return d->mColor;
}

void QExtQuickTriangle::setColor(const QColor &color)
{
    Q_D(QExtQuickTriangle);
    if (color != d->mColor)
    {
        d->mColor = color;
        this->update();
        emit this->colorChanged(color);
    }
}

QColor QExtQuickTriangle::borderColor() const
{
    Q_D(const QExtQuickTriangle);
    return d->mBorderColor;
}

void QExtQuickTriangle::setBorderColor(const QColor &color)
{
    Q_D(QExtQuickTriangle);
    if (color != d->mBorderColor)
    {
        d->mBorderColor = color;
        this->update();
        emit this->borderColorChanged(color);
    }
}

int QExtQuickTriangle::borderWidth() const
{
    Q_D(const QExtQuickTriangle);
    return d->mBorderWidth;
}

void QExtQuickTriangle::setBorderWidth(int width)
{
    Q_D(QExtQuickTriangle);
    width = qMin<int>(qMax<int>(1, width), this->width() / 2);
    if (width != d->mBorderWidth)
    {
        d->mBorderWidth = width;
        this->update();
        emit this->borderWidthChanged(width);
    }
}

void QExtQuickTriangle::paint(QPainter *painter)
{
    Q_D(QExtQuickTriangle);
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

