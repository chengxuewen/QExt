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

#include <qextQmlRectangleInfo.h>

#include <QDebug>

class QExtQmlRectangleInfoPrivate
{
    Q_DISABLE_COPY(QExtQmlRectangleInfoPrivate)
    Q_DECLARE_PUBLIC(QExtQmlRectangleInfo)
public:
    explicit QExtQmlRectangleInfoPrivate(QExtQmlRectangleInfo *q);
    virtual ~QExtQmlRectangleInfoPrivate();

    QExtQmlRectangleInfo * const q_ptr;

    QColor mColor;
    qreal mRadius;
    qreal mWidth;
    qreal mHeight;
    qreal mOpacity;
    qreal mScale;
    bool mVisible;
};

QExtQmlRectangleInfoPrivate::QExtQmlRectangleInfoPrivate(QExtQmlRectangleInfo *q)
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

QExtQmlRectangleInfoPrivate::~QExtQmlRectangleInfoPrivate()
{
}

QExtQmlRectangleInfo::QExtQmlRectangleInfo(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlRectangleInfoPrivate(this))
{

}

QExtQmlRectangleInfo::~QExtQmlRectangleInfo()
{

}

qreal QExtQmlRectangleInfo::scale() const
{
    Q_D(const QExtQmlRectangleInfo);
    return d->mScale;
}

qreal QExtQmlRectangleInfo::opacity() const
{
    Q_D(const QExtQmlRectangleInfo);
    return d->mOpacity;
}

qreal QExtQmlRectangleInfo::radius() const
{
    Q_D(const QExtQmlRectangleInfo);
    return d->mRadius;
}

QColor QExtQmlRectangleInfo::color() const
{
    Q_D(const QExtQmlRectangleInfo);
    return d->mColor;
}

bool QExtQmlRectangleInfo::isVisible() const
{
    Q_D(const QExtQmlRectangleInfo);
    return d->mVisible;
}

qreal QExtQmlRectangleInfo::width() const
{
    Q_D(const QExtQmlRectangleInfo);
    return d->mWidth;
}

qreal QExtQmlRectangleInfo::height() const
{
    Q_D(const QExtQmlRectangleInfo);
    return d->mHeight;
}

void QExtQmlRectangleInfo::setWidth(const qreal &width)
{
    Q_D(QExtQmlRectangleInfo);
    if (width != d->mWidth)
    {
        d->mWidth = width;
        emit this->widthChanged();
    }
}

void QExtQmlRectangleInfo::setHeight(const qreal &height)
{
    Q_D(QExtQmlRectangleInfo);
    if (height != d->mHeight)
    {
        d->mHeight = height;
        emit this->heightChanged();
    }
}

void QExtQmlRectangleInfo::setOpacity(const qreal &opacity)
{
    Q_D(QExtQmlRectangleInfo);
    if (!qFuzzyCompare(d->mOpacity, opacity))
    {
        d->mOpacity = opacity;
        emit this->opacityChanged();
    }
}

void QExtQmlRectangleInfo::setScale(const qreal &scale)
{
    Q_D(QExtQmlRectangleInfo);
    if (!qFuzzyCompare(d->mScale, scale))
    {
        d->mScale = scale;
        emit this->scaleChanged();
    }
}

void QExtQmlRectangleInfo::setRadius(const qreal &radius)
{
    Q_D(QExtQmlRectangleInfo);
    if (radius != d->mRadius)
    {
        d->mRadius = radius;
        emit this->radiusChanged();
    }
}

void QExtQmlRectangleInfo::setColor(const QColor &color)
{
    Q_D(QExtQmlRectangleInfo);
    if (color != d->mColor)
    {
        d->mColor = color;
        emit this->colorChanged();
    }
}

void QExtQmlRectangleInfo::setVisible(const bool &visible)
{
    Q_D(QExtQmlRectangleInfo);
    if (visible != d->mVisible)
    {
        d->mVisible = visible;
        emit this->visibleChanged();
    }
}
