/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024 ChengXueWen.
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

#include <qextQmlBackground.h>

#include <QDebug>

class QExtQmlBackgroundPrivate
{
    Q_DISABLE_COPY(QExtQmlBackgroundPrivate)
    Q_DECLARE_PUBLIC(QExtQmlBackground)
public:
    explicit QExtQmlBackgroundPrivate(QExtQmlBackground *q);
    virtual ~QExtQmlBackgroundPrivate();

    QExtQmlBackground * const q_ptr;

    QColor mColor;
    qreal mRadius;
    qreal mWidth;
    qreal mHeight;
    qreal mOpacity;
    qreal mScale;
    bool mVisible;
};

QExtQmlBackgroundPrivate::QExtQmlBackgroundPrivate(QExtQmlBackground *q)
    : q_ptr(q)
{
    mColor = QColor("#FFFFF");
    mRadius = 0;
    mWidth = 0;
    mHeight = 0;
    mOpacity = 1;
    mScale = 1;
    mVisible = true;
}

QExtQmlBackgroundPrivate::~QExtQmlBackgroundPrivate()
{
}

QExtQmlBackground::QExtQmlBackground(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlBackgroundPrivate(this))
{

}

QExtQmlBackground::~QExtQmlBackground()
{

}

qreal QExtQmlBackground::scale() const
{
    Q_D(const QExtQmlBackground);
    return d->mScale;
}

qreal QExtQmlBackground::opacity() const
{
    Q_D(const QExtQmlBackground);
    return d->mOpacity;
}

qreal QExtQmlBackground::radius() const
{
    Q_D(const QExtQmlBackground);
    return d->mRadius;
}

QColor QExtQmlBackground::color() const
{
    Q_D(const QExtQmlBackground);
    return d->mColor;
}

bool QExtQmlBackground::isVisible() const
{
    Q_D(const QExtQmlBackground);
    return d->mVisible;
}

qreal QExtQmlBackground::width() const
{
    Q_D(const QExtQmlBackground);
    return d->mWidth;
}

qreal QExtQmlBackground::height() const
{
    Q_D(const QExtQmlBackground);
    return d->mHeight;
}

void QExtQmlBackground::setWidth(const qreal &width)
{
    Q_D(QExtQmlBackground);
    if (width != d->mWidth)
    {
        d->mWidth = width;
        emit this->widthChanged();
    }
}

void QExtQmlBackground::setHeight(const qreal &height)
{
    Q_D(QExtQmlBackground);
    if (height != d->mHeight)
    {
        d->mHeight = height;
        emit this->heightChanged();
    }
}

void QExtQmlBackground::setOpacity(const qreal &opacity)
{
    Q_D(QExtQmlBackground);
    if (!qFuzzyCompare(d->mOpacity, opacity))
    {
        d->mOpacity = opacity;
        emit this->opacityChanged();
    }
}

void QExtQmlBackground::setScale(const qreal &scale)
{
    Q_D(QExtQmlBackground);
    if (!qFuzzyCompare(d->mScale, scale))
    {
        d->mScale = scale;
        emit this->scaleChanged();
    }
}

void QExtQmlBackground::setRadius(const qreal &radius)
{
    Q_D(QExtQmlBackground);
    if (radius != d->mRadius)
    {
        d->mRadius = radius;
        emit this->radiusChanged();
    }
}

void QExtQmlBackground::setColor(const QColor &color)
{
    Q_D(QExtQmlBackground);
    if (color != d->mColor)
    {
        d->mColor = color;
        emit this->colorChanged();
    }
}

void QExtQmlBackground::setVisible(const bool &visible)
{
    Q_D(QExtQmlBackground);
    if (visible != d->mVisible)
    {
        d->mVisible = visible;
        emit this->visibleChanged();
    }
}
