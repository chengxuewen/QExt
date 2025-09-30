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

#include <qextQmlBackgroundInfo.h>

#include <QDebug>

class QExtQmlBackgroundInfoPrivate
{
    Q_DISABLE_COPY(QExtQmlBackgroundInfoPrivate)
    Q_DECLARE_PUBLIC(QExtQmlBackgroundInfo)
public:
    explicit QExtQmlBackgroundInfoPrivate(QExtQmlBackgroundInfo *q);
    virtual ~QExtQmlBackgroundInfoPrivate();

    QExtQmlBackgroundInfo * const q_ptr;

    qreal mRadius;
    qreal mOpacity;
    QColor mColor;
    bool mVisible;
};

QExtQmlBackgroundInfoPrivate::QExtQmlBackgroundInfoPrivate(QExtQmlBackgroundInfo *q)
    : q_ptr(q)
{
    mColor = QColor("#FFFFF");
    mRadius = 0;
    mOpacity = 1;
    mVisible = true;
}

QExtQmlBackgroundInfoPrivate::~QExtQmlBackgroundInfoPrivate()
{
}

QExtQmlBackgroundInfo::QExtQmlBackgroundInfo(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlBackgroundInfoPrivate(this))
{
}

QExtQmlBackgroundInfo::~QExtQmlBackgroundInfo()
{
}

qreal QExtQmlBackgroundInfo::opacity() const
{
    Q_D(const QExtQmlBackgroundInfo);
    return d->mOpacity;
}

qreal QExtQmlBackgroundInfo::radius() const
{
    Q_D(const QExtQmlBackgroundInfo);
    return d->mRadius;
}

QColor QExtQmlBackgroundInfo::color() const
{
    Q_D(const QExtQmlBackgroundInfo);
    return d->mColor;
}

bool QExtQmlBackgroundInfo::isVisible() const
{
    Q_D(const QExtQmlBackgroundInfo);
    return d->mVisible;
}

void QExtQmlBackgroundInfo::setOpacity(const qreal &opacity)
{
    Q_D(QExtQmlBackgroundInfo);
    if (!qFuzzyCompare(d->mOpacity, opacity))
    {
        d->mOpacity = opacity;
        emit this->opacityChanged();
    }
}

void QExtQmlBackgroundInfo::setRadius(const qreal &radius)
{
    Q_D(QExtQmlBackgroundInfo);
    if (radius != d->mRadius)
    {
        d->mRadius = radius;
        emit this->radiusChanged();
    }
}

void QExtQmlBackgroundInfo::setColor(const QColor &color)
{
    Q_D(QExtQmlBackgroundInfo);
    if (color != d->mColor)
    {
        d->mColor = color;
        emit this->colorChanged();
    }
}

void QExtQmlBackgroundInfo::setVisible(const bool &visible)
{
    Q_D(QExtQmlBackgroundInfo);
    if (visible != d->mVisible)
    {
        d->mVisible = visible;
        emit this->visibleChanged();
    }
}
